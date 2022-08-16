;-----------------------------------------------------------------------------------------------------------------------
;   FILE DESCRIPTION
;-----------------------------------------------------------------------------------------------------------------------
; Project Name: Flash Bootloader
;    File Name: fbl_startup_vle.asm
;
; Description:  This file contains the startup code for the Freescale/STM
;               xPC57xx MCU (VLE)
;
;-----------------------------------------------------------------------------------------------------------------------
;   COPYRIGHT
;-----------------------------------------------------------------------------------------------------------------------
;   Copyright (c) 2016 by Vector Informatik GmbH.                                                  All rights reserved.
; 
;                 This software is copyright protected and proprietary to Vector Informatik GmbH.
;                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
;                 All other rights remain with Vector Informatik GmbH.
;
; Please note, that this file contains a startup code to be used with the Flash Bootloader. These functions may
; influence the behaviour of the bootloader in principle. Therefore, great care must be taken to verify the correctness
; of the implementation.
;
; The contents of the originally delivered files are only examples resp. implementation proposals. With regard to
; the fact that these functions are meant for demonstration purposes only, Vector Informatik's liability shall be
; expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
;
;-----------------------------------------------------------------------------------------------------------------------
;   AUTHOR IDENTITY
;-----------------------------------------------------------------------------------------------------------------------
;   Name                          Initials      Company
;-----------------------------------------------------------------------------------------------------------------------
;   Achim Strobelt                Ach           Vector Informatik GmbH
;-----------------------------------------------------------------------------------------------------------------------
;   REVISION HISTORY
;-----------------------------------------------------------------------------------------------------------------------
;   Version    Date        Author  Change Id          Description
;-----------------------------------------------------------------------------------------------------------------------
;   01.00.01  2013-07-20   Ach     -                  Initial version
;   01.01.00  2015-04-17   Ach     -                  Reworked exception table handling
;   01.02.00  2015-06-01   Ach     -                  Adapted NMI handling for GHS
;   01.03.00  2015-07-20   Ach     -                  Adapted filter rules
;   01.03.01  2015-09-10   Ach     -                  Change RAM copy target address handling for Diab compiler
;   01.03.02  2016-01-27   Ach     -                  Corrected GHS configuration
;-----------------------------------------------------------------------------------------------------------------------

; Configuration
; RAM initialization
;
; Please note that this RAM initialization is adapted to work with the
; dummy EEPROM driver. If you don't use the dummy EEPROM any more you
; have to remove the initialized flag handling make sure that all
; RAM is initialized on every startup of your ECU which affect RAM
; contents. Please check if the reset detection can be removed as well.
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Configure RAM parameters here
   ramStart = 0x40000000                  ; RAM start address
   ramSize = 0x9000                       ; RAM size - System RAM only (384K)
   ramCount =  ramSize/128                ; calculate count variable

; Configure reset module (RGM)
   rgmBase = 0xFFFA8000                   ; Address of RGM module
   rgmDesOffset = 0x00                    ; Offset of RGM_DES compared to RGM base address
   desCompare = 0x01000001                ; Low voltage and power on reset
   rgmFesOffset = 0x300                   ; Offset of RGM_FES compared to RGM base address
   fesCompare = 0x01000000                ; Low voltage reset
                                          ; for debugging it may be useful in use with several
                                          ; debuggers (e.g. Trace32) to set the external reset
                                          ; flag in this mask to avoid issues with RAM initialization
                                          ; External reset uses BIT 0 in fesCompare


; Configure reset configuration halfword
; Please select correct configuration
; Please use for MPC574xB/C/G and other derivatives with a multi-core RCHW
;   RCHW_VALUE = 0x005A0002               ; MPC57xx derivatives - VLE always enabled, use CPU0
; Default RCHW
;    RCHW_VALUE = 0x015A0000               ; MPC57xx derivatives - VLE always enabled
    RCHW_VALUE = 0x005A0000               ; MPC57xx derivatives - VLE always enabled

   .file   "crt0_57xx_vle.ppc"

# define StackOff       8
# define StackOffLog2   3

   .extern __ghsbinfo_copy
   .extern __ghseinfo_copy

; RCHW/ Boot header placement
   .vle
   .global _start
   .global _nmibase
   .section ".rchw","vax"          ; RCHW location
   .long       RCHW_VALUE
   .long       _start              ; CPU2 entry point

; Extended boot header - needed for certain derivatives
; Please use for MPC574xB/C/G and other derivatives with a multi-core RCHW
;  .long 0
;  .long 0
;  .long       _start              ; CPU0 entry point
;  .long       _start              ; CPU1 entry point
;  .long 0

; Startup code
_start:
   nop                                                   ; nop statements included to allow debugging with iSystem debugger
   nop                                                   ; jump to the second nop statement to test resets

   e_lis       r7, _nmibase@ha                           ; r7 = _nmibase
   e_add16i    r7, r7, _nmibase@l
   mtspr       63, r7                                    ; IVPR = r7 (upper Vector Base Register)

   e_lis       r7, rgmBase@ha
   e_add16i    r7, r7, rgmBase@l                         ; Load r7 with RGM base address
   e_lwz       r2, rgmDesOffset(r7)                      ; Determine reset cause (desctructive)
   e_lis       r6, desCompare@ha                         ; Load reset compare value (destructive)
   e_add16i    r6, r6, desCompare@l
   se_and      r2,r6                                     ; Store comparison result in r2

   e_lwz       r3, rgmFesOffset(r7)                      ; Determine reset cause (functional)
   e_lis       r6, fesCompare@ha                         ; Load reset compare value (functional)
   e_add16i    r6, r6, fesCompare@l
   se_and      r3, r6                                    ; Store comparison result in r3

   se_or       r2, r3                                    ; Combine comparison results
   se_cmpi     r2,0                                      ; Check combined comparison results
   se_bc       1,2,_no_init_l2ram                        ; No reset defined in reset compare mask detected - do not initialize RAM

_init_l2ram:
   e_lis       r2, ramCount@ha                           ; Loop counter to get all of L2SRAM
   e_add16i    r2, r2, ramCount@l
   se_mtctr    r2                                        ; Store in count register
   e_lis       r1, ramStart@ha                           ; r1 holds base address of the L2SRAM, 64-bit word aligned
   e_add16i    r1, r1, ramStart@l                        ; Add low address

_init_l2ram_loop:
   e_stmw      r0,0(r1)                                  ; Write values of all 32 GPR at once
   e_addi      r1,r1,128                                 ; Increment write address
   e_bdnz      _init_l2ram_loop                          ; Decrement count register and jump

   e_lis       r6, desCompare@ha                         ; Load reset compare value (destructive)
   e_add16i    r6, r6, desCompare@l
   e_stw       r6, rgmDesOffset(r7)                      ; Remove reset indication flags from RGM_DES
   e_lis       r6, fesCompare@ha                         ; Load reset compare value (functional)
   e_add16i    r6, r6, fesCompare@l
   e_stw       r6, rgmFesOffset(r7)                      ; Remove reset indication flags from RGM_FES

; Initialize memory pointer registers
_no_init_l2ram:
   e_lis       sp,%hiadj(__ghsend_stack-StackOff)        ; Set SP
   e_add16i    sp,sp,%lo(__ghsend_stack-StackOff)
   e_lis       r13,%hiadj(__ghsbegin_sdabase + 0x8000)   ; SDA base register
   e_add16i    r13,r13,%lo(__ghsbegin_sdabase + 0x8000)
   e_lis       r2,%hiadj(__ghsbegin_sdata2 + 0x8000)     ; SDA2 base register
   e_add16i    r2,r2,%lo(__ghsbegin_sdata2 + 0x8000)

;***********************************************************************************************************************
;   _romcopy
;**********************************************************************************************************************
; PURPOSE      : This function copies initialized data from Flash to SRAM    
;                 for the ".data" and ".sdata" sections.                     
;                                                                            
; INPUT NOTES  : _ghsbinfo_copy - defined by the linker                      
;                _ghseinfo_copy - defined by the linker                      
;                                                                            
; RETURN NOTES : None                                                        
; WARNING      : Registers used: R4, R5 : store begin and end of the copy    
;                                         table                              
;                                R28    : temporary register                 
;                                R29-R31: addresses and size of current      
;                                         section                            
;                                R0     : hold the copy data                 
;*********************************************************************************************************************

_romcopy:
   e_lis       r4, %hiadj(__ghsbinfo_copy)               ; Load upper copy table begin address into R4
   e_add16i    r4, r4, %lo(__ghsbinfo_copy)              ; Load lower copy table begin address into R4
   e_lis       r5, %hiadj(__ghseinfo_copy)               ; Load upper copy table end address into R5
   e_add16i    r5, r5, %lo(__ghseinfo_copy)              ; Load lower copy table end address into R5

_romcopy_tableloop:
   se_cmp      r4, r5                                    ; Check if end of copy table is reached
   se_bc       0, 0, _romcopy_end                        ; End of copy table is reached, copy finished

   e_lmw       r29, 0(r4)                                ; Read 3 words from copy table (target address, source address and size)
   e_addi      r4, r4, 12                                ; Prepare address for next section

   se_cmpi     r31,0                                     ; Check size of section
   se_bc       1,2,_romcopy_tableloop                    ; Omit empty sections

   e_andi      r28, r31, 0x03                            ; Mask length which is not word aligned
   se_srwi     r31, 2                                    ; Divide length by 4

   e_add16i    r29, r29, -4                              ; Prepare target address
   e_add16i    r30, r30, -4                              ; Prepare source address

   se_cmpi     r31,0                                     ; Check if size of section is < 4
   se_bc       1,2,_romcopy_checkbytes                   ; Jump to byte copy loop

   se_mtctr    r31                                       ; Set count register (wordcount of current section)

_romcopy_wordloop:
   e_lwzu      r0, 4(r30)                                ; Increment read address and read word
   e_stwu      r0, 4(r29)                                ; Increment write address and write word
   e_bdnz      _romcopy_wordloop

_romcopy_checkbytes:
   e_cmpwi     r28,0                                     ; Check if any bytes are left
   se_bc       1,2,_romcopy_tableloop                    ; Next table entry

   se_mtctr    r28                                       ; Prepare byte copy

   e_add16i    r29, r29, 3                               ; Prepare target address
   e_add16i    r30, r30, 3                               ; Prepare source address

_romcopy_byteloop:
   e_lbzu      r0, 1(r30)                                ; Increment source address and read byte
   e_stbu      r0, 1(r29)                                ; Increment target address and write byte
   e_bdnz      _romcopy_byteloop

   e_b         _romcopy_tableloop                        ; Current section finished, jump to next section
_romcopy_end:

   e_b         main                                      ; go to c language code

# if defined(__ELF)
    .fsize  StackOff
    .scall  __dotsyscall
    .scall  __ghs_ind_crt0
    .type   _start,@function
    .size   _start,$-_start
# endif /* ELF */

/* This section directive is NEEDED.  It causes secinfo to be a
 * readonly section which ind_crt0.c may require for proper operation */
# if defined(__ELF)
    .section ".secinfo","a"
# else
    .section ".secinfo",.text
# endif /* ELF */

; Exception table configuration - no fbl_vect.c used in MPC57xx Bootloaders
; Offset 0x00 is not used - reserved for system reset, but system reset
; is defined by boot header
   .vle
   .global _start
   .section ".nmi","vax"          ; NMI location. Please check alignment requirements

_nmibase:
   .long       0                   ; Start address of startup code (BAM jumps to it)
   .align 4                        ; NMI vector #1    (Machine check)
   e_b        _start
   .align 4                        ; NMI vector #2    (Data storage)
   e_b        _start
   .align 4                        ; NMI vector #3    (Instruction storage)
   e_b        _start
   .align 4                        ; NMI vector #4    (External Input)
   e_b        _start
   .align 4                        ; NMI vector #5    (Alignment)
   e_b        _start
   .align 4                        ; NMI vector #6    (Program)
   e_b        _start
   .align 4                        ; NMI vector #7    (Performance Monitor)
   e_b        _start
   .align 4                        ; NMI vector #8    (System call)
   e_b        _start
   .align 4                        ; NMI vector #9    (Debug)
   e_b        _start
   .align 4                        ; NMI vector #10   (EFPU Data Exception)
   e_b        _start
   .align 4                        ; NMI vector #11   (EFPU Round Exception)
   e_b        _start
   .align 4                        ; NMI vector #12   (Reserved)
   e_b        _start
   .align 4                        ; NMI vector #13   (Reserved)
   e_b        _start
   .align 4                        ; NMI vector #14   (Reserved)
   e_b        _start
   .align 4                        ; NMI vector #15   (Reserved)
   e_b        _start

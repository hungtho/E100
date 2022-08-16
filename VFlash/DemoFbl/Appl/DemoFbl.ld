/* ----------------------------------------------------------------------
 *  Vector BRS linker file for platform MPC57XX and compiler GHS
 * ---------------------------------------------------------------------- */
DEFAULTS {

    stack_reserve = 0x00000300
    heap_reserve  = 0x00000800

}
MEMORY {
//  Internal Flash
    flash_rsvd1 : ORIGIN = 0x00FC0000,    LENGTH = 0x0
    fbl_startup : ORIGIN = .,             LENGTH = 0x300
    nmi_memory  : ORIGIN = 0x00FC0300,    LENGTH = 0x100
    fbl_memory  : ORIGIN = 0x00FC0400,    LENGTH = 0x7C00
    appl_memory : ORIGIN = 0x00FC8000,    LENGTH = 0x100
    flash_rsvd2 : ORIGIN = .,             LENGTH = 0x0


//  32KB of internal SRAM starting at 0x40000000
    dram_rsvd1          : ORIGIN = 0x40000000, LENGTH = 0x0
    dram_flashdrv  : ORIGIN = 0x40000000, LENGTH = 0x800
    dram_flashdrvxd1:ORIGIN = 0x40000800, LENGTH = 0x800
    dram_memory         : ORIGIN = 0x40001000, LENGTH = 0x7800
    dram_rsvd2          : ORIGIN = .,          LENGTH = 0x0
    stack_memory        : ORIGIN = 0x40008800, LENGTH = 0x300
    dram_eeprom         : ORIGIN = 0x40008B00, LENGTH = 0x2000


}

SECTIONS
{

//
// RAM SECTIONS
//
    FLASHDRV                          ABS : > dram_flashdrv
    .PPC.EMB.sdata0                   ABS : > .
    .PPC.EMB.sbss0              CLEAR ABS : > .
    .sdabase                     ALIGN(16): > dram_memory 
    .FBLMAGIC                         ABS : > .

    .sdata                       align(4) : > .
    .sbss                        align(4) : > .
    .data                        align(4) : > .
    .mcal_data                   align(4) : > .
    .bss                         align(4) : > .
    .RAMCODE                     align(4) : > .
    .ramcopy                     align(4) : 
    { 
       fbl_hw.o(.vletext) 
       fbl_cw.o(.vletext) 
       fbl_tp.o(.vletext) 
    } >. 

    .heap    ALIGN(16) PAD(heap_reserve)  : > .
    .EEPDATA                           ABS : > dram_eeprom
    .stack   ALIGN(16) PAD(stack_reserve) : > stack_memory

// ROM SECTIONS

    .rchw          NOCHECKSUM             : > fbl_startup
    .nmi           NOCHECKSUM             : > nmi_memory
    .FBLHEADER                            : > fbl_memory
    .vletext                     align(8) : > .
    .text                        align(8) : > .
    .ROM.RAMCODE            ROM(.RAMCODE) : > .
    .ROM.ramcopy            ROM(.ramcopy) : > .
    .syscall                     align(8) : > .

    .rodata                      align(8) : > .
    .sdata2                      align(8) : > .
    .mcal_const_cfg              align(8) : > .
    .mcal_text                   align(8) : > .
    .acfls_code_rom              align(8) : > .
    .mcal_const                  align(8) : > .

    .secinfo                     align(8) : > .
    .fixaddr                     align(8) : > .
    .fixtype                     align(8) : > .

    .APPLVECT                             : > appl_memory

//

// These special symbols mark the bounds of RAM and ROM memory.
_RAM_START_ADDR = 0x40000000;
// They are used by the MULTI debugger.
    __ghs_ramstart  = MEMADDR(dram_rsvd1);
    __ghs_ramend    = MEMENDADDR(dram_memory);
    __ghs_romstart  = MEMADDR(flash_rsvd1);
    __ghs_romend    = MEMENDADDR(flash_rsvd2);

//
// These special symbols mark the bounds of RAM and ROM images of boot code.
// They are used by the GHS startup code (_start and __ghs_ind_crt0).
//
    __ghs_rambootcodestart  = 0;
    __ghs_rambootcodeend    = 0;
    __ghs_rombootcodestart  = ADDR(.text);
    __ghs_rombootcodeend    = ENDADDR(.fixtype);
}

-sda

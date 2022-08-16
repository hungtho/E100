#######################################################################################################################
# File Name  : Makefile.MPC57XX.GHS.ALL.LinkerScriptDefault.make                                                      #
# Description: Linker/Symbol Preprocessor command file generation                                                     #
# Project    : Vector Basic Runtime System                                                                            #
# Module     : BrsHw for platform Freescale/ST MPC57xx                                                                #
#              and Compiler GreenHills                                                                                #
#                                                                                                                     #
#---------------------------------------------------------------------------------------------------------------------#
# COPYRIGHT                                                                                                           #
#---------------------------------------------------------------------------------------------------------------------#
# Copyright (c) 2018 by Vector Informatik GmbH.                                                  All rights reserved. #
#                                                                                                                     #
#---------------------------------------------------------------------------------------------------------------------#
# AUTHOR IDENTITY                                                                                                     #
#---------------------------------------------------------------------------------------------------------------------#
# Name                          Initials      Company                                                                 #
# ----------------------------  ------------  ------------------------------------------------------------------------#
# Johannes Rebmann              visjre        Vector Informatik GmbH                                                  #
# Alexander Gronbach            visagh        Vector Informatik GmbH                                                  #
# Matthias Patz                 vismpz        Vector Informatik GmbH                                                  #
# David Feuerstein              visdfe        Vector Informatik GmbH                                                  #
# Benjamin Walter               visbwa        Vector Informatik GmbH                                                  #
# Sascha Mauser                 vismaa        Vector Informatik GmbH                                                  #
#---------------------------------------------------------------------------------------------------------------------#
# REVISION HISTORY                                                                                                    #
#---------------------------------------------------------------------------------------------------------------------#
# Version   Date        Author  Description                                                                           #
# --------  ----------  ------  --------------------------------------------------------------------------------------#
# 01.00.00  2010-07-22  visjre  initial version                                                                       #
# 01.00.01  2010-12-17  visagh  Support MPC5602D                                                                      #
# 01.01.00  2011-02-10  visagh  moved memory map to separate file                                                     #
# 01.01.01  2011-04-01  vismpz  added support for BrsHwInitRam                                                        #
# 02.00.00  2012-02-02  visagh  started to harmonize linker files                                                     #
# 02.00.01  2012-02-10  visagh  cleanup and added stack pointer symbol                                                #
# 02.00.02  2012-02-14  visagh  added support of initialized RAM                                                      #
# 02.00.03  2012-03-14  visdfe  added support for AUTOSAR OS                                                          #
# 02.01.00  2013-02-15  visagh  Moved memory definition to another file, changed section placement (same as DiabData) #
# 02.01.01  2013-08-01  visagh  added support of software interrupt mode                                              #
# 02.02.00  2016-07-01  visbwa  Renamed file from Makefile.MPC57XX.GHS.ALL.make (to separate from SafeCtx UseCase),   #
#                               adapted complete file header structure for zBrs_Template@root[2.00.02]                #
# 02.03.00  2016-07-12  visbwa  Introduced RAM_FLEXRAY_ETH, added _RAM_START_ADDR                                     #
# 02.04.00  2017-02-08  visbwa  Renamed file, added additional information output                                     #
# 02.04.01  2017-05-12  visbwa  Added LinkerScriptDefault.make to include list                                        #
# 02.04.02  2017-07-18  visbwa  Review according to Brs_Template 2.01.04                                              #
# 02.04.10  2017-12-12  vismaa  Added _VECTORTABLE_START_ADDR for IVPR initialisation                                 #
# 02.04.11  2018-03-20  vismaa  Replaced section ivortable with intvect_CoreExceptions,                               #
#                               replaced section intvecttable with intvect_ExtExceptions,                             #
#                               deleted os* sections for OSGEN6                                                       #
#######################################################################################################################

#------------------------------------------------------------------------------
# rule to generate linker command file
#------------------------------------------------------------------------------
$(PROJECT_NAME).$(LNK_SUFFIX): Makefile \
                               Makefile.config \
                               Makefile.Project.Part.Defines \
                               Makefile.$(PLATFORM).$(COMPILER_MANUFACTURER).$(EMULATOR).make \
                               Makefile.$(PLATFORM).$(COMPILER_MANUFACTURER).$(EMULATOR).LinkerScriptDefault.make

#---------------------------------------------------------------------------------
# _NEVER_ delete the leading "Tab" in the first ECHO-line below!!!
# The Linker-Command-File which will be generated:
#---------------------------------------------------------------------------------
	@$(ECHO) "Vector BRS for platform $(PLATFORM) and compiler $(COMPILER_MANUFACTURER)";                        \
  $(ECHO) "/* ----------------------------------------------------------------------"                    > $@; \
  $(ECHO) " *  Vector BRS linker file for platform $(PLATFORM) and compiler $(COMPILER_MANUFACTURER)"   >> $@; \
  $(ECHO) " * ---------------------------------------------------------------------- */"                >> $@; \
  $(ECHO) "DEFAULTS {"                                                                   >> $@; \
  $(ECHO) ""                                                                             >> $@; \
  $(ECHO) "    stack_reserve = 0x00000300"                                               >> $@; \
  $(ECHO) "    heap_reserve  = 0x00000800"                                               >> $@; \
  $(ECHO) ""                                                                             >> $@; \
  $(ECHO) "}"                                                                            >> $@; \
  $(ECHO) "MEMORY {"                                                                     >> $@; \
  $(ECHO) "//  Internal Flash"                                                           >> $@; \
  $(ECHO) "    flash_rsvd1 : ORIGIN = 0x00FC0000,    LENGTH = 0x0"                       >> $@; \
  $(ECHO) "    fbl_startup : ORIGIN = .,             LENGTH = 0x300"                     >> $@; \
  $(ECHO) "    nmi_memory  : ORIGIN = 0x00FC0300,    LENGTH = 0x100"                     >> $@; \
  $(ECHO) "    fbl_memory  : ORIGIN = 0x00FC0400,    LENGTH = 0x7C00"                    >> $@; \
  $(ECHO) "    appl_memory : ORIGIN = 0x00FC8000,    LENGTH = 0x100"                     >> $@; \
  $(ECHO) "    flash_rsvd2 : ORIGIN = .,             LENGTH = 0x0"                       >> $@; \
  $(ECHO) ""                                                                             >> $@; \
  $(ECHO) ""                                                                             >> $@; \
  $(ECHO) "//  32KB of internal SRAM starting at 0x40000000"                             >> $@; \
  $(ECHO) "    dram_rsvd1          : ORIGIN = 0x40000000, LENGTH = 0x0"                  >> $@; \
  $(ECHO) "    dram_flashdrv  : ORIGIN = 0x40000000, LENGTH = 0x800"                     >> $@; \
  $(ECHO) "    dram_flashdrvxd1:ORIGIN = 0x40000800, LENGTH = 0x800"                     >> $@; \
  $(ECHO) "    dram_memory         : ORIGIN = 0x40001000, LENGTH = 0x7800"               >> $@; \
  $(ECHO) "    dram_rsvd2          : ORIGIN = .,          LENGTH = 0x0"                  >> $@; \
  $(ECHO) "    stack_memory        : ORIGIN = 0x40008800, LENGTH = 0x300"                >> $@; \
  $(ECHO) "    dram_eeprom         : ORIGIN = 0x40008B00, LENGTH = 0x2000"               >> $@; \
  $(ECHO) ""                                                                             >> $@; \
  $(ECHO) ""                                                                             >> $@; \
  $(ECHO) "}"                                                                            >> $@; \
  $(ECHO) ""                                                                             >> $@; \
  $(ECHO) "SECTIONS"                                                                     >> $@; \
  $(ECHO) "{"                                                                            >> $@; \
  $(ECHO) ""                                                                             >> $@; \
  $(ECHO) "//"                                                                           >> $@; \
  $(ECHO) "// RAM SECTIONS"                                                              >> $@; \
  $(ECHO) "//"                                                                           >> $@; \
  $(ECHO) "    FLASHDRV                          ABS : > dram_flashdrv"                  >> $@; \
  $(ECHO) "    .PPC.EMB.sdata0                   ABS : > ."                              >> $@; \
  $(ECHO) "    .PPC.EMB.sbss0              CLEAR ABS : > ."                              >> $@; \
  $(ECHO) "    .sdabase                     ALIGN(16): > dram_memory "                   >> $@; \
  $(ECHO) "    .FBLMAGIC                         ABS : > ."                              >> $@; \
  $(ECHO) ""                                                                             >> $@; \
  $(ECHO) "    .sdata                       align(4) : > ."                              >> $@; \
  $(ECHO) "    .sbss                        align(4) : > ."                              >> $@; \
  $(ECHO) "    .data                        align(4) : > ."                              >> $@; \
  $(ECHO) "    .mcal_data                   align(4) : > ."                              >> $@; \
  $(ECHO) "    .bss                         align(4) : > ."                              >> $@; \
  $(ECHO) "    .RAMCODE                     align(4) : > ."                              >> $@; \
  $(ECHO) "    .ramcopy                     align(4) : "                                 >> $@; \
  $(ECHO) "    { "                                                                       >> $@; \
  $(ECHO) "       fbl_hw.o(.vletext) "                                                   >> $@; \
  $(ECHO) "       fbl_cw.o(.vletext) "                                                   >> $@; \
  $(ECHO) "       fbl_tp.o(.vletext) "                                                   >> $@; \
  $(ECHO) "    } >. "                                                                    >> $@; \
  $(ECHO) ""                                                                             >> $@; \
  $(ECHO) "    .heap    ALIGN(16) PAD(heap_reserve)  : > ."                              >> $@; \
  $(ECHO) "    .EEPDATA                           ABS : > dram_eeprom"                   >> $@; \
  $(ECHO) "    .stack   ALIGN(16) PAD(stack_reserve) : > stack_memory"                   >> $@; \
  $(ECHO) ""                                                                             >> $@; \
  $(ECHO) "// ROM SECTIONS"                                                              >> $@; \
  $(ECHO) ""                                                                             >> $@; \
  $(ECHO) "    .rchw          NOCHECKSUM             : > fbl_startup"                    >> $@; \
  $(ECHO) "    .nmi           NOCHECKSUM             : > nmi_memory"                     >> $@; \
  $(ECHO) "    .FBLHEADER                            : > fbl_memory"                     >> $@; \
  $(ECHO) "    .vletext                     align(8) : > ."                              >> $@; \
  $(ECHO) "    .text                        align(8) : > ."                              >> $@; \
  $(ECHO) "    .ROM.RAMCODE            ROM(.RAMCODE) : > ."                        >> $@; \
  $(ECHO) "    .ROM.ramcopy            ROM(.ramcopy) : > ."                        >> $@; \
  $(ECHO) "    .syscall                     align(8) : > ."                              >> $@; \
  $(ECHO) ""                                                                             >> $@; \
  $(ECHO) "    .rodata                      align(8) : > ."                              >> $@; \
  $(ECHO) "    .sdata2                      align(8) : > ."                              >> $@; \
  $(ECHO) "    .mcal_const_cfg              align(8) : > ."                              >> $@; \
  $(ECHO) "    .mcal_text                   align(8) : > ."                              >> $@; \
  $(ECHO) "    .acfls_code_rom              align(8) : > ."                              >> $@; \
  $(ECHO) "    .mcal_const                  align(8) : > ."                              >> $@; \
  $(ECHO) ""                                                                             >> $@; \
  $(ECHO) "    .secinfo                     align(8) : > ."                              >> $@; \
  $(ECHO) "    .fixaddr                     align(8) : > ."                              >> $@; \
  $(ECHO) "    .fixtype                     align(8) : > ."                              >> $@; \
  $(ECHO) ""                                                                             >> $@; \
  $(ECHO) "    .APPLVECT                             : > appl_memory"                    >> $@; \
  $(ECHO) ""                                                                             >> $@; \
  $(ECHO) "//"                                                                           >> $@; \
  $(ECHO) ""                                                                             >> $@; \
  $(ECHO) "// These special symbols mark the bounds of RAM and ROM memory."              >> $@; \
  $(ECHO) "_RAM_START_ADDR = $(CPU_RAM_START_ADDR);"                                     >> $@; \
  $(ECHO) "// They are used by the MULTI debugger."                                      >> $@; \
  $(ECHO) "    __ghs_ramstart  = MEMADDR(dram_rsvd1);"                                   >> $@; \
  $(ECHO) "    __ghs_ramend    = MEMENDADDR(dram_memory);"                               >> $@; \
  $(ECHO) "    __ghs_romstart  = MEMADDR(flash_rsvd1);"                                  >> $@; \
  $(ECHO) "    __ghs_romend    = MEMENDADDR(flash_rsvd2);"                               >> $@; \
  $(ECHO) ""                                                                             >> $@; \
  $(ECHO) "//"                                                                           >> $@; \
  $(ECHO) "// These special symbols mark the bounds of RAM and ROM images of boot code." >> $@; \
  $(ECHO) "// They are used by the GHS startup code (_start and __ghs_ind_crt0)."        >> $@; \
  $(ECHO) "//"                                                                           >> $@; \
  $(ECHO) "    __ghs_rambootcodestart  = 0;"                                             >> $@; \
  $(ECHO) "    __ghs_rambootcodeend    = 0;"                                             >> $@; \
  $(ECHO) "    __ghs_rombootcodestart  = ADDR(.text);"                                   >> $@; \
  $(ECHO) "    __ghs_rombootcodeend    = ENDADDR(.fixtype);"                             >> $@; \
  $(ECHO) "}"                                                                            >> $@; \
  $(ECHO) ""                                                                             >> $@; \
  $(ECHO) "-sda"                                                                         >> $@;

#End of Makefile.MPC57XX.GHS.ALL.LinkerScriptDefault.make

#######################################################################################################################
# File Name  : Makefile                                                                                               #
# Description: local main project Makefile                                                                            #
# Project    : Vector Basic Runtime System                                                                            #
# Module     : BrsHw for platform Freescale/ST MPC57xx                                                                #
#              and Compiler GreenHills,                                                                               #
#              using Vector PES Makesupport 3.13                                                                      #
# Template   : This Makefile is reviewed according to zBrs_Template@root[2.02.01]                                     #
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
# Benjamin Walter               visbwa        Vector Informatik GmbH                                                  #
# Stefan Schorer                vissns        Vector Informatik GmbH                                                  #
# Daniel Kuhnle                 viskdl        Vector Informatik GmbH                                                  #
# Ivo Georgiev                  visivg        Vector Informatik GmbH                                                  #
#---------------------------------------------------------------------------------------------------------------------#
# REVISION HISTORY                                                                                                    #
#---------------------------------------------------------------------------------------------------------------------#
# Version   Date        Author  Description                                                                           #
# --------  ----------  ------  --------------------------------------------------------------------------------------#
# 01.00.00  2015-05-05  vissns  New creation, based on zBrs_Mpc@root[3.09.04], according to BrsHw Codestyle 2.0       #
#           2015-07-17  visbwa  Review                                                                                #
# 01.00.01  2015-09-18  visbwa  Added HEX target (input from visthm)                                                  #
# 01.00.02  2015-10-12  visbwa  fixed BRS_CPU_STARTUP_ID defines                                                      #
# 02.00.00  2015-12-21  visbwa  Reworked Makefile, according to template 2.00.00 and Makesupport 3.13                 #
# 02.00.01  2016-03-23  viskdl  Reworked default library switches                                                     #
# 02.01.00  2016-07-01  visbwa  Added SafeContext support, switched linkage to ccppc,                                 #
#                               optimized linker and assembler options (harmonized with Brs_Spc58xx),                 #
#                               adapted complete file header structure for zBrs_Template@root[2.00.02]                #
# 02.01.01  2016-07-06  visbwa  Removed odd dependency defines parameter                                              #
# 02.01.02  2016-07-13  visbwa  Added hex build target                                                                #
# 02.01.03  2016-10-14  visbwa  Changed assembly from asppc.exe to ccppc.exe, modified default assembly options       #
# 02.01.04  2017-03-14  visbwa  Added $(COMPILER_BASE)\include\ppc as default include path                            #
# 03.00.00  2017-06-28  visivg  Splitted platform/compiler static settings into separate file Makefile.static         #
#                               (acording to Brs_Template 2.01.02)                                                    #
# 03.00.01  2017-07-18  visbwa  Review according to Brs_Template 2.01.04                                              #
# 03.00.02  2017-10-09  visbwa  Changed AS_ENV to proper CC_ENV, increased AS_LC                                      #
# 03.00.03  2017-10-18  visbwa  Update to Brs_Template 2.01.06                                                        #
# 03.00.04  2018-03-28  visbwa  Review according to Brs_Template 2.02.01                                              #
#######################################################################################################################

#------------------------------------------------------------------------------
# Name of this project (dir under which the appl dir resides)
# E.g.: TestSuit
#------------------------------------------------------------------------------
PROJECT_NAME = DemoFbl

#------------------------------------------------------------------------------
# More static settings placed inside separate file
#------------------------------------------------------------------------------
include Makefile.static

#------------------------------------------------------------------------------
# Define Compiler path
# E.g.: COMPILER_BASE = D:\uti\%vendor%\%platform%\%version%
#       COMPILER_BIN  = $(COMPILER_BASE)\bin
#       COMPILER_INC  = $(COMPILER_BASE)\inc
#       COMPILER_LIB  = $(COMPILER_BASE)\lib
#------------------------------------------------------------------------------
COMPILER_BASE = C:\ghs\comp_201754
COMPILER_BIN  = $(COMPILER_BASE)
COMPILER_INC  = $(COMPILER_BASE)\ansi $(COMPILER_BASE)\include\ppc
COMPILER_LIB  = $(COMPILER_LIB_$(LENGTH_ENCODING))

# Absolute path must be used here because of cygwin environment
ELFCONVERTER_BIN = D:\usr\usage\Delivery\CBD15x\CBD1500...\D00\external\Misc\OsElfConverter\ElfConverter.exe

COMPILER_LIB_VLE = $(COMPILER_BASE)\lib\ppcvle
COMPILER_LIB_BOOKE = $(COMPILER_BASE)\lib\ppc

#------------------------------------------------------------------------------
# Build Options Selection: VECTOR / CUSTOMER
#------------------------------------------------------------------------------
ASFLAGS_SELECTOR = VECTOR
CFLAGS_SELECTOR  = VECTOR
LDFLAGS_SELECTOR = VECTOR

#------------------------------------------------------------------------------
# Default License server and port
#------------------------------------------------------------------------------
LICENSE_SERVER = vistrlic1

#------------------------------------------------------------------------------
# Define Emulator path
# E.g.: EMU_PATH = C:\UTI\HITOPWIN\P6811
#------------------------------------------------------------------------------
EMU_PATH = $(COMPILER_BASE)

#------------------------------------------------------------------------------
# Set NANT_USED to '1', to enable the usage of NAnt support within
# Global Makefile. If this is enabled, the Makesupport will include the
# NAnt support from a intranel link and the NAnt build-targets can be used.
#------------------------------------------------------------------------------
#NANT_USED=1

#------------------------------------------------------------------------------
# Set MKVERBOSE to a various value, to enable enhanced debug output from 
# Makesupport. To disable this afterwards, set MKVERBOSE to nothing
# (comment out this line and type "set MKVERBOSE=" in command window)
#------------------------------------------------------------------------------
#MKVERBOSE=1

#------------------------------------------------------------------------------
# Set BRSVINFO_USED to '1', to enable the generation of BrsVInfo.h within the
# GenData folder by the Makesupport.
# The BrsVInfo.h will contain e.g. kBrsCompilerVersion, to use this 
# information within the embedded code.
#------------------------------------------------------------------------------
#BRSVINFO_USED=1

#------------------------------------------------------------------------------
# Turn off strict c setting for dependency generation
#------------------------------------------------------------------------------
#STRICT_C_OFF=1

#------------------------------------------------------------------------------
# Set DELETE_DLD to '1', to enable the deleting of previously 
# generated/outdated Linker-script file, before every new linkage request.
#------------------------------------------------------------------------------
#DELETE_DLD=1

#------------------------------------------------------------------------------
# Set NEW_DEPENDENCY_FORMAT to '1' to enable parallel creation of dependencies.
# You have to ensure that you call m.bat with -jX to use this feature.
#------------------------------------------------------------------------------
#NEW_DEPENDENCY_FORMAT=1

#------------------------------------------------------------------------------
# If you want to use code analysis tools like PC-Lint or QAC,
# configure them within Makefile.analysis (part of global-make-package)
# and include this file here
#------------------------------------------------------------------------------
#include Makefile.analysis

#------------------------------------------------------------------------------
# Dependency defines
# These defines are used for the GNU-Preprocessor,
# e.g.: BRS_TIMEBASE_CLOCK=$(TIMEBASE_CLOCK)
#------------------------------------------------------------------------------
DEP_DEFINES = BRS_DERIVATIVE_$(DERIVATIVE)         \
              BRS_OSC_CLK=$(MAIN_OSC_CLK)          \
              BRS_TIMEBASE_CLOCK=$(TIMEBASE_CLOCK) \
              BRS_OS_USECASE_$(OS_USECASE)         \
              BRS_CPU_STARTUP_ID=$(CPU_STARTUP_ID) \
              BRS_EVA_BOARD_$(EVA_BOARD)           \
              BRS_PLATFORM_$(PLATFORM)             \
              BRS_COMP_$(COMPILER_MANUFACTURER)    \
              BRSHW_INSTRUCTION_SET_$(LENGTH_ENCODING)

#------------------------------------------------------------------------------
# $(AS_ENV) is the environment necessary to run the assembler
# $(AS) defines the path to the assembler
# $(ASFLAGS_VECTOR_MAKESUPPORT) defines all assembler switches, mandatory for
#                               the Vector build environment (Makesupport/BrsHw)
# $(ASFLAGS_VECTOR_OPTIONS) defines the Vector default assembler switches
# $(ASFLAGS_CUSTOMER_OPTIONS) defines the customer requested assembler switches
# Depending of ASFLAGS_SELECTOR, ASFLAGS_VECTOR_OPTIONS or ASFLAGS_CUSTOMER_OPTIONS
# are used together with ASFLAGS_VECTOR_MAKESUPPORT for Build.
#------------------------------------------------------------------------------
AS_ENV  = $(CC_ENV)
AS      = $(COMPILER_BIN)\ccppc.exe

#Please add only absolutely mandatory options below
ASFLAGS_VECTOR_MAKESUPPORT = -object_dir=$(OBJ_PATH)              \
                             -list=$(LST_PATH)/$*.lst             \
                             -stderr=$(ERR_PATH)\$*.$(ERR_SUFFIX) \
                             -c

# Length encoding specific flags
ASFLAGS_BOOKE =
ASFLAGS_VLE   = -vle

#Please add any other option below (vector default options)
ASFLAGS_VECTOR_OPTIONS = -cpu=$(GHS_PROC_$(DERIVATIVE)) \
                         $(ASFLAGS_$(LENGTH_ENCODING))  \
                         -preprocess_assembly_files

#Please enter all customer options below
ASFLAGS_CUSTOMER_OPTIONS =

#------------------------------------------------------------------------------
# $(ASVERSION) defines the assembler switch for version report
# E.g.: ASVERSION = -V
#------------------------------------------------------------------------------
ASVERSION = -V

#------------------------------------------------------------------------------
# $(AS_LC) defines the number of lines used for assembler version information
# in BrsVinfo.h and Deliverydescription (default is 5)
#------------------------------------------------------------------------------
AS_LC = 2

#------------------------------------------------------------------------------
#------------------------- MUST be filled out ---------------------------------
# $(CC_ENV) is the environment necessary to run the compiler
# $(CC) defines the path to the C-Compiler
# $(CFLAGS_VECTOR_MAKESUPPORT) defines all compiler switches, mandatory for
#                               the Vector build environment (Makesupport/BrsHw)
# $(CFLAGS_VECTOR_OPTIONS) defines the Vector default compiler switches
# $(CFLAGS_CUSTOMER_OPTIONS) defines the customer requested compiler switches
# Depending of CFLAGS_SELECTOR, CFLAGS_VECTOR_OPTIONS or CFLAGS_CUSTOMER_OPTIONS
# are used together with CFLAGS_VECTOR_MAKESUPPORT for Build.
#------------------------------------------------------------------------------
#  -a            Compile for code coverage analysis by Multi.
#  -archive      Create a library archive for use with linker.
#  -asm=<args>   Pass <args> directly to the assembler.
#  -bigendian    Use big endian byte order.
#  -[no]bigswitch        Allow large switch statements.
#  -bsp=<bsp_name> See also -cpu and -layout
#  -c            Produce object files, but do not link.
#  -check=none,all,[no]bound,[no]nilderef,[no]switch,[no]assignbound,[no]zerodivide.
#         The compiler generates runtime checks for the items requested.
#  -cpu=<cpu_name> Use ? for a list of choices. Or use -bsp
#  -D<name>[=<val>] In C, C++: define <name> with value <val>.
#  -E            In C, C++: preprocess file and send result to stdout.
#  -entry=symbol Set the entry point in the linker output.
#  -fsoft        Use software floating point.
#  -fnone        In C, C++: Give syntax errors for floating point usage
#  -G            Generate information for MULTI debugger.
#  -H            Print names of included headers to stderr.
#  -I<dir>       Passed to compiler to add <dir> to include search path.
#  -L<dir>       Passed to linker to add <dir> to library search path.
#  -l<name>      Passed to linker to look for library lib<name>.a.
#  -layout=<name> Use ? for a list of choices. Requires -bsp
#  -lnk=<arg>    Pass <arg> directly to linker.
#  -list[=name]  Assembler will produce a listing file.
#  -list/<type>  For Ada95, generate the requested listing.
#  -littleendian Use little endian byte order.
#  -map[=name]   Linker will produce a map file.
#  -nofloatio    Use printf, scanf without %e %f %g in libansi.
#  -noobj        Turn off direct object file creation.
#  -nostartfiles Do not add start-up files to link
#  -nostdlib     Do not add start-up files or libraries to link
#  -obj          Turn on direct object file creation.
#  -o name       Name final output file.
#  -Ospeed       Optimize for speed, even if code is larger.
#  -Ospace       Optimize for smaller code, even if it is slower.
#  -O            Turn on general optimizations
#  -OI           Expand routines inline rather than generating calls.
#  -OI=name,...  Inline only the named routines.
#  -OL           Optimize loops, including loop unrolling.
#  -P            In C, C++: preprocess into file.i and stop.
#  -p            Compile for call count profiling.
#  -pg           Compile for call count and call graph profiling.
#  -passsource   Pass compiler source lines into assembly file.
#  -S            Produce assembly files, and stop. (implies -noobj)
#  -sda=val      Put objects <= val bytes into Small Data Area
#  -zda=val      Put objects <= val bytes into Zero Data Area
#  -syntax       Compilers will check syntax but not generate code.
#  -U<name>      In C, C++: undefine the macro <name>.
#  -v            Print all commands before they are executed.
#  -w            Suppress compiler, assembler, and linker warning messages.
#  -#            Print all commands INSTEAD of executing them.
#------------------------------------------------------------------------------
CC_ENV  = export GHS_LMHOST=@$(LICENSE_SERVER);
CC      = $(COMPILER_BIN)\ccppc.exe

#Please add only absolutely mandatory options below
CFLAGS_VECTOR_MAKESUPPORT = -DBRS_DERIVATIVE_$(DERIVATIVE)             \
                            -DBRS_OSC_CLK=$(MAIN_OSC_CLK)              \
                            -DBRS_TIMEBASE_CLOCK=$(TIMEBASE_CLOCK)     \
                            -DBRS_OS_USECASE_$(OS_USECASE)             \
                            -DBRS_EVA_BOARD_$(EVA_BOARD)               \
                            -DBRS_PLATFORM_$(PLATFORM)                 \
                            -DBRS_COMP_$(COMPILER_MANUFACTURER)        \
                            -DBRSHW_INSTRUCTION_SET_$(LENGTH_ENCODING) \
                            -DBRS_CPU_STARTUP_ID=$(CPU_STARTUP_ID)     \
                            -object_dir=$(OBJ_PATH)                    \
                            -list=$(LST_PATH)/$*.lst                   \
                            -stderr=$(ERR_PATH)\$*.$(ERR_SUFFIX)       \
                            -c

# Length encoding specific flags
CFLAGS_VLE   = -vle -DC_ENABLE_INSTRUCTION_SET_VLE -D__vle
CFLAGS_BOOKE = -novle

#Please add any other option below (vector default options)
CFLAGS_VECTOR_OPTIONS = $(CFLAGS_$(LENGTH_ENCODING))    \
                        --prototype_warnings            \
                        -Odebug -Osize -Ospace          \
                        -G                              \
                        -dual_debug                     \
                        -nofloatio                      \
                        -cpu=$(GHS_PROC_$(DERIVATIVE))  \
                        -noobj                          \
                        -D$(CPU_RAM_SIZE_$(DERIVATIVE)) \
                        -inline_prologue                \
                        -pragma_asm_inline              \
                        -noSPE                          \
                        --no_exceptions                 \
                        --no_commons                    \
                        -nokeeptempfiles                \
                        -pnone                          \
                        --incorrect_pragma_warnings     \
                        --slash_comment                 \
                        --long_long                     \
                        -preprocess_assembly_files      \
                        -passsource
                                                                                                            

#Please enter all customer options below
CFLAGS_CUSTOMER_OPTIONS =

#------------------------------------------------------------------------------
# $(CVERSION) defines the compiler switch for version report
# E.g.: CVERSION = -V
#------------------------------------------------------------------------------
CVERSION = -V dummy.c

#------------------------------------------------------------------------------
# $(CC_LC) defines the number of lines used for compiler version information
# in BrsVinfo.h and Deliverydescription (default is 5)
#------------------------------------------------------------------------------
CC_LC = 5

#------------------------------------------------------------------------------
# $(CINC) defines the include switch of the used compiler.
# E.g.: COSMIC Compiler use: CINC = -i
#------------------------------------------------------------------------------
CINC = -I

#------------------------------------------------------------------------------
#------------------------- MUST be filled out ---------------------------------
# $(LD_ENV) is the environment necessary to run the linker
# $(LD) defines the path linker
# $(LDFLAGS_VECTOR_MAKESUPPORT) defines all linker switches, mandatory for
#                               the Vector build environment (Makesupport/BrsHw)
# $(LDFLAGS_VECTOR_OPTIONS) defines the Vector default linker switches
# $(LDFLAGS_CUSTOMER_OPTIONS) defines the customer requested linker switches
# Depending of LDFLAGS_SELECTOR, LDFLAGS_VECTOR_OPTIONS or LDFLAGS_CUSTOMER_OPTIONS
# are used together with LDFLAGS_VECTOR_MAKESUPPORT for Build.
#------------------------------------------------------------------------------
#Usage: elxr [options] files...
#Options:
# -A file         take symbols (but not contents) from file
# -a              perform final relocatable link (implies -r)
# -addr_reloc_ppc64_abi give warnings when any section other than opd points into t
# -append         append new sections to section map
# -argcheck=level set link-time argument checking to none|normal|full
# -C name=value   define new constant equal to <value>
# -cfmap_file=file map file used for resolving profile information in CodeFactor
# -cfprof_cutoff=num cutoff percentile for profiling feedback CodeFactor
# -cfprof_file=file profile data used for profile feedback in CodeFactor
# -cfprofile      use profile information to guide CodeFactor
# -cmd=file       alias for @file
# -codefactor     perform Code Factor optimization
# -crc            add a 4-byte crc to the end of every program section
# -D symbol=value define new symbol equal to <value>
# -data_delete    delete unused data
# -delete         delete unused functions
# -dyload[=kernel] create a dynamic relocatable executable (INTEGRITY/VelOSity)
# -e symbol       set entry point to <symbol>
# -elf64          force output of Elf64 executable format
# -force_uvfd=sym force virtual function to get removed
# -func_prefix symbol prefix function names with symbol
# -globalreg=num  set the number of global registers
# -gnu_linkmap[=file] generate gnu linkmap file <output file>.ld
# -inline_trivial inline trivial (return instruction) functions
# -inmemtm_entryexit only instrument the beginning and end of every function
# -integrity_posix_dll output an INTEGRITY POSIX DLL
# -keep=sym       don't delete sym during optimizations
# -keep_argcheck  don't strip argcheck symbols
# -L dir          add <dir> to library search directories
# -lname          include lib<name>.a from search directories
# -M[anx]         map file options (Alpha/Numeric/X-reference)
# -map[=file]     generate map file <output file>.map
# -multiple       allow multiply defined symbols
# -nocpp          don't create C++ constructor/destructors
# -noretainlocals don't retain local symbols (with -r)
# -o file         set name of output file to <file> (default a.out)
# -opt_address    optimize loading of addresses
# -overlap        don't warn on overlapping sections
# -overlap_warn   give a warning for overlapping sections
# -pic            program uses PIC
# -pid            program uses PID
# -ppc64_abi      force output to conform to PPC Elf64 ABI format
# -Q y|n          add a linker ident string to .comment section
# -r              preserve relocation information in output file
# -retainlocals   retain local symbols (with -r)
# -saferc_is_misra_2004 enforce MISRA 2004 rules
# -sdaize         perform link-time SDA optimization
# -speed          optimize for speed (valid with -sdaize and/or -zdaize)
# -T script_file  specifies the link map file
# -tailmerge      perform function tail merging optimization
# -traceedge_entryexit only instrument the beginning and end of every function
# -u symbol       force an undefined symbol reference for <symbol>
# -undefined      allow undefined symbols
# -uvfd           delete C++ virtual functions
# -uvfd_fullerrors generate all errors for C++ virtual function deletion
# -v              verbose mode
# -V              display version banner
# -w              suppress warning messages
# -warn_duplicate_script_file warn for duplicate script file inclusion
# -wrap symbol    use a wrapper function for symbol
# -Y U|L|UL,dir   change default|alternate|both library directories to <dir>
# -zdaize         perform link-time ZDA optimization
# CONSTANTS       synonym for DEFAULTS
# DEFAULTS {...}  define default constants
# MEMORY {...}    define the memory map
# OPTION("-option...") specify a command-line option in script file
# SECTIONS {...}  define the section map
#
# @commandfile    read in additional options from <commandfile>
# -help           show regular help summary
# -Help           show detailed help summary
#
#For options whose names are a single letter, arguments must be separated
#by an equals ('='), or follow as the next argument;
#  '-o=argument' and '-o argument' are equivalent.
#When there is no ambiguity, the '=' may be omitted, as in '-oargument'
#
#For options whose names are multiple letters, either one or two dashes may
#precede the option name; '--option' and '-option' are equivalent.
#Arguments must be separated by an equals sign or follow as the next argument;
# '-option=arg', and '-option arg' are equivalent.
#------------------------------------------------------------------------------
LD_ENV  = $(CC_ENV)
LD      = $(COMPILER_BIN)\ccppc.exe
#LD      = $(COMPILER_BIN)\elxr.exe

#Please add only absolutely mandatory options below
LDFLAGS_VECTOR_MAKESUPPORT = -o $*.$(BINARY_SUFFIX)             \
                             -map=$(PROJECT_NAME).map           \
                             --preprocess_linker_directive_full \
                             $(PROJECT_NAME).$(LNK_SUFFIX)

#Please add any other option below (vector default options)
LDFLAGS_VECTOR_OPTIONS = -overlap_warn     \
                         -Manx             \
                         -nostdlib         \
                         -L$(COMPILER_LIB) \
                         -lansi            \
                         -lind             \
                         -larch            \
                         -keepmap          \
                         -farcallpatch

#Please enter all customer options below
LDFLAGS_CUSTOMER_OPTIONS =

#------------------------------------------------------------------------------
# $(LDVERSION) defines the linker switch for version report
# E.g.: LDVERSION = -v
#------------------------------------------------------------------------------
LDVERSION = -V dummy.c

#------------------------------------------------------------------------------
# $(LD_LC) defines the number of lines used for linker version information
# in BrsVinfo.h and Deliverydescription (default is 5)
#------------------------------------------------------------------------------
LD_LC = 6

#------------------------- MUST be filled out ---------------------------------
# $(HEX_ENV) is the environment necessary to run the hexfile generator
# $(HEX) defines the path linker
# $(HEXFLAGS
#------------------------------------------------------------------------------
HEX_ENV  = $(CC_ENV)
HEX      = $(COMPILER_BIN)\gsrec.exe

HEXFLAGS = -nos5 -skip .tdata $(PROJECT_NAME).$(BINARY_SUFFIX) -o

#------------------------------------------------------------------------------
#------------------------- MUST be filled out ---------------------------------
# $(LB_ENV) is the environment necessary to run the librarian
# $(LB) defines the path to the C-librarian
# $(LBFLAGS) defines all librarian switches
#------------------------------------------------------------------------------
LB_ENV  = $(CC_ENV)
LB      = $(CC)

LBFLAGS  = -archive \
           -o $@

#------------------------------------------------------------------------------
# $(LBVERSION) defines the archiver switch for version report
# E.g.: LBVERSION = -v
#------------------------------------------------------------------------------
LBVERSION = -V

#------------------------------------------------------------------------------
# $(LB_LC) defines the number of lines used for librarian version information
# in BrsVinfo.h
#------------------------------------------------------------------------------
LB_LC = 6

#------------------------------------------------------------------------------
# Additional includes essentially for compilation
#------------------------------------------------------------------------------
ADDITIONAL_INCLUDES +=

#------------------------------------------------------------------------------
# Additional objects essentially for linking
# E.g.: ADDITIONAL_OBJECTS = $(OBJ_PATH)\myobject.$(OBJ_SUFFIX)
#------------------------------------------------------------------------------
ADDITIONAL_OBJECTS +=

#------------------------------------------------------------------------------
# List of assembler source files
# E.g.: ASM_SOURCES = source\startup.$(ASM_SUFFIX)
#------------------------------------------------------------------------------
ASM_SOURCES +=

#------------------------------------------------------------------------------
# Add Startup code to application source list
# E.g.: APP_SOURCE_LST += source\startup.c
#------------------------------------------------------------------------------
APP_SOURCE_LST += $(COMPILER_BASE)\src\libstartup\ind_mcpy.c \
                  $(COMPILER_BASE)\src\libstartup\ind_mset.c
ADDITIONAL_INCLUDES += $(COMPILER_BASE)\src\libsys

#------------------------------------------------------------------------------
# Check if all necessary variables are set
# (Checks that are not possible to be performed within Makefile.static)
#------------------------------------------------------------------------------

###############################################################################
######### DO NOT remove these lines from the end of the Makefile!!! ###########
###############################################################################

#------------------------------------------------------------------------------
# Platform/compiler/derivative/emulator dependant makefile is included here
# It defines a rule to generate the linker and a rule to generate the
# symbol preprocessor command file.
# A template for this Makefile can be found under
#     R:\Can_Base\CANtate\BRS\PlatformSpecific\...\OrganiAndMake\...
#------------------------------------------------------------------------------
include Makefile.$(PLATFORM).$(COMPILER_MANUFACTURER).$(EMULATOR).make

#------------------------------------------------------------------------------
# Include the main makefile where all the targets are defined
#------------------------------------------------------------------------------
include $(MAKESUPPORT_DIR)\Global.Makefile.target.make.$(VERSION)

#End of Makefile

# e200z common makefile scripts and rules.

RM = rm -fR
MK = mkdir -p
NULL = 2>/dev/null

##############################################################################
# Processing options coming from the upper Makefile.
#

# Compiler options
OPT = $(USE_OPT)
COPT = $(USE_COPT)
CPPOPT = $(USE_CPPOPT)

# Garbage collection
ifeq ($(USE_LINK_GC),yes)
  OPT += -ffunction-sections -fdata-sections -fno-common
  LDOPT := --gc-sections
else
  LDOPT := --no-gc-sections
endif

# Linker extra options
ifneq ($(USE_LDOPT),)
  LDOPT := $(LDOPT),$(USE_LDOPT)
endif

# Link time optimizations
ifeq ($(USE_LTO),yes)
  OPT += -flto
endif

# VLE option handling.
ifeq ($(USE_VLE),yes)
  DDEFS += -DPPC_USE_VLE=1
  DADEFS += -DPPC_USE_VLE=1
else
  DDEFS += -DPPC_USE_VLE=0
  DADEFS += -DPPC_USE_VLE=0
endif


# Output directory and files
ifeq ($(BUILDDIR),)
  BUILDDIR = build
endif
ifeq ($(BUILDDIR),.)
  BUILDDIR = build
endif
OUTFILES = $(BUILDDIR)/$(PROJECT).elf $(BUILDDIR)/$(PROJECT).hex \
           $(BUILDDIR)/$(PROJECT).mot $(BUILDDIR)/$(PROJECT).bin \
           $(BUILDDIR)/$(PROJECT).dmp 
ifeq ($(CREATE_LIB),true)
OUTFILES += $(BUILDDIR)/$(PROJECT).a
endif
		   
# Source files groups and paths
SRC	      = $(CSRC)$(CPPSRC)
SRCPATHS  = $(sort $(dir $(ASMXSRC)) $(dir $(ASMSRC)) $(dir $(SRC)))

# Various directories
OBJDIR    = $(BUILDDIR)/obj
LSTDIR    = $(BUILDDIR)/lst
MCSDIR    = $(BUILDDIR)/mcs

# Object files groups
COBJS     = $(addprefix $(OBJDIR)/, $(notdir $(CSRC:.c=.o)))
CPPOBJS   = $(addprefix $(OBJDIR)/, $(notdir $(CPPSRC:.cpp=.o)))
ASMOBJS   = $(addprefix $(OBJDIR)/, $(notdir $(ASMSRC:.s=.o)))
ASMXOBJS  = $(addprefix $(OBJDIR)/, $(notdir $(ASMXSRC:.S=.o)))
OBJS	  = $(ASMXOBJS) $(ASMOBJS) $(COBJS) $(CPPOBJS)

# Paths
IINCDIR   = $(patsubst %,-I%,$(INCDIR) $(DINCDIR) $(UINCDIR))
LLIBDIR   = $(patsubst %,-L%,$(DLIBDIR) $(ULIBDIR))

# Macros
DEFS      = $(DDEFS) $(UDEFS)
ADEFS 	  = $(DADEFS) $(UADEFS)

# Libs
LIBS      = $(DLIBS) $(ULIBS)

# Various settings
MCFLAGS   = $(MCU)
ODFLAGS	  = -x --syms
ASFLAGS   = $(MCFLAGS) -Wa,-amhls=$(LSTDIR)/$(notdir $(<:.s=.lst)) $(ADEFS)
ASXFLAGS  = $(MCFLAGS) -Wa,-amhls=$(LSTDIR)/$(notdir $(<:.S=.lst)) $(ADEFS)
CFLAGS    = $(MCFLAGS) $(OPT) $(COPT) $(CWARN) -Wa,-alms=$(LSTDIR)/$(notdir $(<:.c=.lst)) $(DEFS)
CPPFLAGS  = $(MCFLAGS) $(OPT) $(CPPOPT) $(CPPWARN) -Wa,-alms=$(LSTDIR)/$(notdir $(<:.cpp=.lst)) $(DEFS)
LDFLAGS   = $(MCFLAGS) $(OPT) -nostartfiles $(LLIBDIR) -Wl,-Map=$(BUILDDIR)/$(PROJECT).map,--cref,--no-warn-mismatch,--library-path=$(RULESPATH),$(LDOPT),--script=$(LDSCRIPT)

# Generate dependency information
ASFLAGS  += -MD -MP -MF .dep/$(@F).d
CFLAGS   += -MD -MP -MF .dep/$(@F).d
CPPFLAGS += -MD -MP -MF .dep/$(@F).d

# Paths where to search for sources
VPATH     = $(SRCPATHS)

#
# Makefile rules
#

all: $(OBJS) $(MCS_OBJS) $(ENGINE_MCS_OBJS) $(OUTFILES) MAKE_ALL_RULE_HOOK

MAKE_ALL_RULE_HOOK:

# Build MCS code if GTM component is present
# otherwise just use an empty rule.
build_mcs_code::

$(OBJS): | $(BUILDDIR)

$(BUILDDIR) $(OBJDIR) $(LSTDIR) $(MCSDIR):
	$(MK) $(MCSDIR) $(OBJDIR) $(LSTDIR)

	@make build_mcs_code
ifeq (${USE_VERBOSE_COMPILE},yes)
	@echo Compiler Options:
	@echo "  CFLAGS  = $(CFLAGS)"
	@echo "  INCLUDE = $(IINCDIR)"
	@echo
endif

$(CPPOBJS) : $(OBJDIR)/%.o : %.cpp Makefile
	@echo Compiling $(<F)
	$(AT)$(CPPC) -c $(CPPFLAGS) -I. $(IINCDIR) $< -o $@

$(COBJS) : $(OBJDIR)/%.o : %.c Makefile
	@echo Compiling $(<F)
	$(AT)$(CC) -c $(CFLAGS) -I. $(IINCDIR) $< -o $@

$(ASMOBJS) : $(OBJDIR)/%.o : %.s Makefile
	@echo Compiling $(<F)
	$(AT)$(AS) -c $(ASFLAGS) -I. $(IINCDIR) $< -o $@

$(ASMXOBJS) : $(OBJDIR)/%.o : %.S Makefile
	@echo Compiling $(<F)
	$(AT)$(CC) -c $(ASXFLAGS) -I. $(IINCDIR) $< -o $@

#
# If GTM-IP component is present, add MCS compiler tools and rules
#
-include ./components/spc5_gtm_component_rla/mak/rules.mk

#
# If Security component is present, add rules to generate HSM binary firmware
#
-include ./components/spc5_security_component_rla/mak/rules.mk

%.elf: $(OBJS) $(MCS_OBJS) $(ENGINE_MCS_OBJS) $(LDSCRIPT)
	@echo Linking $@
	$(AT)$(LD) $(OBJS) $(MCS_OBJS) $(ENGINE_MCS_OBJS) $(LIBS) $(LDFLAGS) -o $@

%.hex: %.elf $(LDSCRIPT)
	@echo Creating $@
	$(AT)$(HEX) $< $@

%.mot: %.elf $(LDSCRIPT)
	@echo Creating $@
	$(AT)$(MOT) $< $@

%.bin: %.elf $(LDSCRIPT)
	@echo Creating $@
	$(AT)$(BIN) $< $@

%.dmp: %.elf $(LDSCRIPT)
	@echo Creating $@
	$(AT)$(OD) $(ODFLAGS) $< > $@
	@echo
	$(AT)$(SZ) $<
	@echo
	@echo Done
	
ifeq ($(CREATE_LIB),true)	
%.a: %.elf $(LDSCRIPT)	
	@echo Creating $@
	$(AT)$(AR) $@ build/obj/*.o 
endif

clean:
	@echo Cleaning .dep $(BUILDDIR)
	$(shell $(RM) .dep $(BUILDDIR) $(NULL))
	@echo Done

# lint-nt must be accessible from your PATH
LINT_TOOL = lint-nt
LINT_OPTIONS = pclint/co-gcc.lnt pclint/au-misra3.lnt pclint/waivers.lnt

define AWK_CMD =
/search starts/{inc=1; next}/End of search list./{inc=0; next}{if (inc>0) { a = $$1; printf(gensub(/(.*)$$/, "--i\\\\1", "g", a)) }}
endef
define GET_INCLUDE_PATHS_CMD = 
$(shell $(TRGT)cpp -v 2>&1 | gawk '$(AWK_CMD)' > pclint/gcc-include-path.lnt)
endef

misra: pclint/gcc-include-path.lnt pclint/lint_cmac.h pclint/lint_cppmac.h
	@echo
	@echo Start MISRA Check...
	@echo ${LINT_TOOL} ${LINT_OPTIONS} $(subst \,/,$(IINCDIR)) $(subst \,/,$(SRC)) > misra.txt
	$(AT)${LINT_TOOL} ${LINT_OPTIONS} $(subst \,/,$(IINCDIR)) $(subst \,/,$(SRC)) >> misra.txt
	@echo 
	@echo See results in misra.txt

.PHONY: pclint/gcc-include-path.lnt
pclint/gcc-include-path.lnt:
	@echo
	@echo Generate pclint/gcc-include-path.lnt for current compiler 
	$(AT)$(GET_INCLUDE_PATHS_CMD)

.PHONY: pclint/lint_cmac.h
pclint/lint_cmac.h:
	@echo
	@echo Generate pclint/lint_cmac.h for current compiler 
	@touch t.c 
	$(AT)$(TRGT)gcc -E -dM t.c > pclint/lint_cmac.h
	@rm t.c

.PHONY: pclint/lint_cppmac.h
pclint/lint_cppmac.h:
	@echo
	@echo Generate pclint/lint_cppmac.h for current compiler
	@touch t.cpp 
	$(AT)$(TRGT)g++ -E -dM t.cpp > pclint/lint_cppmac.h
	@rm t.cpp

#
# Include the dependency files, should be the last of the makefile
#
-include $(shell $(MK) .dep $(NULL)) $(wildcard .dep/*)

# *** EOF ***

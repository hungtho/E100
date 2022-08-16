# List of library files exported by the component.
LIB_C_SRC       += ./components/spc570sxx_irq_component_rla/lib/src/irq.c \
                   ./components/spc570sxx_irq_component_rla/lib/src/eirq.c
LIB_CPP_SRC     +=

LIB_ASM_SRC     += ./components/spc570sxx_irq_component_rla/lib/src/vectors.s

LIB_INCLUDES    += ./components/spc570sxx_irq_component_rla/lib/include

APP_C_SRC       += ./components/spc570sxx_irq_component_rla/cfg/irq_cfg.c \
                   ./components/spc570sxx_irq_component_rla/cfg/eirq_cfg.c

APP_CPP_SRC     +=

APP_ASM_SRC     +=

APP_INCLUDES    += ./components/spc570sxx_irq_component_rla/cfg

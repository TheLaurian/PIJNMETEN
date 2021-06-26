################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1030/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS

GEN_OPTS__FLAG := --cmd_file="C:/ti/workspace_v10/tirtos_builds_cc32xx_release_ccs/Debug/configPkg/compiler.opt" 
GEN_CMDS__FLAG := -l"C:/ti/workspace_v10/tirtos_builds_cc32xx_release_ccs/Debug/configPkg/linker.cmd" 

ORDERED_OBJS += \
"./empty.obj" \
"./syscfg/ti_drivers_config.obj" \
"./main_tirtos.obj" \
"../cc32xxs_tirtos.cmd" \
-lti_utils_build_linker.cmd.genlibs \
$(GEN_CMDS__FLAG) \
-l"ti/devices/cc32xx/driverlib/ccs/Release/driverlib.a" \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Project_Pijn.out \

EXE_OUTPUTS__QUOTED += \
"Project_Pijn.out" \

BIN_OUTPUTS += \
Project_Pijn.hex \

BIN_OUTPUTS__QUOTED += \
"Project_Pijn.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "Project_Pijn.out"

dependents:
	-cd C:/ti/workspace_v10/tirtos_builds_cc32xx_release_ccs/Debug && $(MAKE) all

# Tool invocations
Project_Pijn.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS) C:/ti/workspace_v10/tirtos_builds_cc32xx_release_ccs/Debug/tirtos_builds_cc32xx_release_ccs.lib
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"C:/ti/ccs1030/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on -z -m"Project_Pijn.map" -i"C:/ti/simplelink_cc32xx_sdk_5_10_00_02/source" -i"C:/ti/simplelink_cc32xx_sdk_5_10_00_02/kernel/tirtos/packages" -i"C:/ti/workspace_v10/MAXM86146_code/Project_Pijn_backup/MCU+Image/syscfg" -i"C:/ti/ccs1030/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/lib" --diag_wrap=off --display_error_number --warn_sections --xml_link_info="Project_Pijn_linkInfo.xml" --rom_model -o "Project_Pijn.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

Project_Pijn.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: Arm Hex Utility'
	"C:/ti/ccs1030/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armhex" --diag_wrap=off -o "Project_Pijn.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(BIN_OUTPUTS__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "empty.obj" "syscfg\ti_drivers_config.obj" "main_tirtos.obj" 
	-$(RM) "empty.d" "syscfg\ti_drivers_config.d" "main_tirtos.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-C:/ti/ccs1030/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armobjcopy -O binary --only-section .text --only-section .const --only-section .cinit --only-section .resetVecs Project_Pijn.out Project_Pijn.bin
	-C:/ti/simplelink_cc32xx_sdk_5_10_00_02/source/ti/drivers/net/imagecreator/bin/SLImageCreator.exe syscfg create_image --sdk_path C:/ti/simplelink_cc32xx_sdk_5_10_00_02 --json C:\ti\workspace_v10\MAXM86146_code\Project_Pijn_backup\MCU+Image/syscfg/ti_drivers_net_wifi_config.json --file C:\ti\workspace_v10\MAXM86146_code\Project_Pijn_backup\MCU+Image/syscfg/Project_Pijn.sli --mcu  C:\ti\workspace_v10\MAXM86146_code\Project_Pijn_backup\MCU+Image/Project_Pijn.bin
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
C:/ti/workspace_v10/tirtos_builds_cc32xx_release_ccs/Debug/tirtos_builds_cc32xx_release_ccs.lib:

-include ../makefile.targets


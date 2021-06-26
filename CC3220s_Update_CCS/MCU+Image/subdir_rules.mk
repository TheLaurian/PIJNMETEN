################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1030/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/ti/workspace_v10/MAXM86146_code/Project_Pijn_backup" --include_path="C:/ti/workspace_v10/MAXM86146_code/Project_Pijn_backup/MCU+Image" --include_path="C:/ti/simplelink_cc32xx_sdk_5_10_00_02/source" --include_path="C:/ti/simplelink_cc32xx_sdk_5_10_00_02/source/ti/posix/ccs" --include_path="C:/ti/ccs1030/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/ti/workspace_v10/MAXM86146_code/Project_Pijn_backup/MCU+Image/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-979479297: ../empty.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs1030/ccs/utils/sysconfig_1.8.0/sysconfig_cli.bat" -s "C:/ti/simplelink_cc32xx_sdk_5_10_00_02/.metadata/product.json" --script "C:/ti/workspace_v10/MAXM86146_code/Project_Pijn_backup/empty.syscfg" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-979479297 ../empty.syscfg
syscfg/ti_drivers_config.h: build-979479297
syscfg/ti_utils_build_linker.cmd.genlibs: build-979479297
syscfg/syscfg_c.rov.xs: build-979479297
syscfg/ti_utils_runtime_model.gv: build-979479297
syscfg/ti_utils_runtime_Makefile: build-979479297
syscfg/: build-979479297

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1030/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/ti/workspace_v10/MAXM86146_code/Project_Pijn_backup" --include_path="C:/ti/workspace_v10/MAXM86146_code/Project_Pijn_backup/MCU+Image" --include_path="C:/ti/simplelink_cc32xx_sdk_5_10_00_02/source" --include_path="C:/ti/simplelink_cc32xx_sdk_5_10_00_02/source/ti/posix/ccs" --include_path="C:/ti/ccs1030/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/ti/workspace_v10/MAXM86146_code/Project_Pijn_backup/MCU+Image/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-790712799: ../image.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs1030/ccs/utils/sysconfig_1.8.0/sysconfig_cli.bat" -s "C:/ti/simplelink_cc32xx_sdk_5_10_00_02/.metadata/product.json" --script "C:/ti/workspace_v10/MAXM86146_code/Project_Pijn_backup/image.syscfg" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_net_wifi_config.json: build-790712799 ../image.syscfg
syscfg/: build-790712799



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/observer/Desktop/mspm0g3507/01-workspace/opa_inverting_pga_with_dac_LP_MSPM0G3507_nortos_ticlang" -I"C:/Users/observer/Desktop/mspm0g3507/01-workspace/opa_inverting_pga_with_dac_LP_MSPM0G3507_nortos_ticlang/Debug" -I"C:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_01_00_03/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-513424223: ../opa_inverting_pga_with_dac.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs1260/ccs/utils/sysconfig_1.19.0/sysconfig_cli.bat" --script "C:/Users/observer/Desktop/mspm0g3507/01-workspace/opa_inverting_pga_with_dac_LP_MSPM0G3507_nortos_ticlang/opa_inverting_pga_with_dac.syscfg" -o "." -s "C:/ti/mspm0_sdk_2_01_00_03/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-513424223 ../opa_inverting_pga_with_dac.syscfg
device.opt: build-513424223
device.cmd.genlibs: build-513424223
ti_msp_dl_config.c: build-513424223
ti_msp_dl_config.h: build-513424223
Event.dot: build-513424223

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/observer/Desktop/mspm0g3507/01-workspace/opa_inverting_pga_with_dac_LP_MSPM0G3507_nortos_ticlang" -I"C:/Users/observer/Desktop/mspm0g3507/01-workspace/opa_inverting_pga_with_dac_LP_MSPM0G3507_nortos_ticlang/Debug" -I"C:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_01_00_03/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: C:/ti/mspm0_sdk_2_01_00_03/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/observer/Desktop/mspm0g3507/01-workspace/opa_inverting_pga_with_dac_LP_MSPM0G3507_nortos_ticlang" -I"C:/Users/observer/Desktop/mspm0g3507/01-workspace/opa_inverting_pga_with_dac_LP_MSPM0G3507_nortos_ticlang/Debug" -I"C:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_01_00_03/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lv_examples/lv_tutorial/0_porting/lv_tutorial_porting.c 

OBJS += \
./lv_examples/lv_tutorial/0_porting/lv_tutorial_porting.o 

C_DEPS += \
./lv_examples/lv_tutorial/0_porting/lv_tutorial_porting.d 


# Each subdirectory must supply rules for building sources it contributes
lv_examples/lv_tutorial/0_porting/%.o: ../lv_examples/lv_tutorial/0_porting/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F769xx -I"D:/Documents/GitHub/PerfectTuning/Projet/Inc" -I"D:/Documents/GitHub/PerfectTuning/Projet/Drivers/STM32F7xx_HAL_Driver/Inc" -I"D:/Documents/GitHub/PerfectTuning/Projet/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"D:/Documents/GitHub/PerfectTuning/Projet/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/Documents/GitHub/PerfectTuning/Projet/Drivers/CMSIS/Include" -I"D:/Documents/GitHub/PerfectTuning/Projet" -I"D:/Documents/GitHub/PerfectTuning/Projet/lv_examples" -I"D:/Documents/GitHub/PerfectTuning/Projet/Drivers/BSP/Components" -I"D:/Documents/GitHub/PerfectTuning/Projet/Drivers/BSP/STM32F769I-Discovery" -I"D:/Documents/GitHub/PerfectTuning/Projet/Utilities/Fonts" -I"D:/Documents/GitHub/PerfectTuning/Projet/Drivers"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



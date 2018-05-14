################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/stmpe811/stmpe811.c 

OBJS += \
./Drivers/BSP/Components/stmpe811/stmpe811.o 

C_DEPS += \
./Drivers/BSP/Components/stmpe811/stmpe811.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/stmpe811/%.o: ../Drivers/BSP/Components/stmpe811/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F769xx -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Inc" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers/STM32F7xx_HAL_Driver/Inc" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers/CMSIS/Include" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/lv_examples" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers/BSP/Components" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers/BSP/STM32F769I-Discovery" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Utilities/Fonts" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers"  -O3 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



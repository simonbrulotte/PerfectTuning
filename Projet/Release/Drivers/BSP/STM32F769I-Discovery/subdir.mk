################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery.c \
../Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_audio.c \
../Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_eeprom.c \
../Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_lcd.c \
../Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_sdram.c \
../Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_ts.c 

OBJS += \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery.o \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_audio.o \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_eeprom.o \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_lcd.o \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_sdram.o \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_ts.o 

C_DEPS += \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery.d \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_audio.d \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_eeprom.d \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_lcd.d \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_sdram.d \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32F769I-Discovery/%.o: ../Drivers/BSP/STM32F769I-Discovery/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F769xx -I"D:/Documents/GitHub/PerfectTuning/Projet/Inc" -I"D:/Documents/GitHub/PerfectTuning/Projet/Drivers/STM32F7xx_HAL_Driver/Inc" -I"D:/Documents/GitHub/PerfectTuning/Projet/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"D:/Documents/GitHub/PerfectTuning/Projet/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/Documents/GitHub/PerfectTuning/Projet/Drivers/CMSIS/Include" -I"D:/Documents/GitHub/PerfectTuning/Projet" -I"D:/Documents/GitHub/PerfectTuning/Projet/lv_examples" -I"D:/Documents/GitHub/PerfectTuning/Projet/Drivers/BSP/Components" -I"D:/Documents/GitHub/PerfectTuning/Projet/Drivers/BSP/STM32F769I-Discovery" -I"D:/Documents/GitHub/PerfectTuning/Projet/Utilities/Fonts" -I"D:/Documents/GitHub/PerfectTuning/Projet/Drivers"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



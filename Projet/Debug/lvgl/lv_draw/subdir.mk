################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lv_draw/lv_draw.c \
../lvgl/lv_draw/lv_draw_rbasic.c \
../lvgl/lv_draw/lv_draw_vbasic.c 

OBJS += \
./lvgl/lv_draw/lv_draw.o \
./lvgl/lv_draw/lv_draw_rbasic.o \
./lvgl/lv_draw/lv_draw_vbasic.o 

C_DEPS += \
./lvgl/lv_draw/lv_draw.d \
./lvgl/lv_draw/lv_draw_rbasic.d \
./lvgl/lv_draw/lv_draw_vbasic.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lv_draw/%.o: ../lvgl/lv_draw/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F769xx -I"C:/Users/TophersAlien/workspace/Projet/Inc" -I"C:/Users/TophersAlien/workspace/Projet/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/Users/TophersAlien/workspace/Projet/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"C:/Users/TophersAlien/workspace/Projet/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/TophersAlien/workspace/Projet/Drivers/CMSIS/Include" -I"C:/Users/TophersAlien/workspace/Projet" -I"C:/Users/TophersAlien/workspace/Projet/lv_examples" -I"C:/Users/TophersAlien/workspace/Projet/Drivers/BSP/Components" -I"C:/Users/TophersAlien/workspace/Projet/Drivers/BSP/STM32F769I-Discovery" -I"C:/Users/TophersAlien/workspace/Projet/Utilities/Fonts" -I"C:/Users/TophersAlien/workspace/Projet/Drivers"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



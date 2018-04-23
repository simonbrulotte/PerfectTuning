################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lv_examples/lv_tutorial/6_images/lv_tutorial_images.c \
../lv_examples/lv_tutorial/6_images/red_flower.c 

OBJS += \
./lv_examples/lv_tutorial/6_images/lv_tutorial_images.o \
./lv_examples/lv_tutorial/6_images/red_flower.o 

C_DEPS += \
./lv_examples/lv_tutorial/6_images/lv_tutorial_images.d \
./lv_examples/lv_tutorial/6_images/red_flower.d 


# Each subdirectory must supply rules for building sources it contributes
lv_examples/lv_tutorial/6_images/%.o: ../lv_examples/lv_tutorial/6_images/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F769xx -I"C:/PerfectTuning/Projet/Inc" -I"C:/PerfectTuning/Projet/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/PerfectTuning/Projet/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"C:/PerfectTuning/Projet/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/PerfectTuning/Projet/Drivers/CMSIS/Include" -I"C:/PerfectTuning/Projet" -I"C:/PerfectTuning/Projet/lv_examples" -I"C:/PerfectTuning/Projet/Drivers/BSP/Components" -I"C:/PerfectTuning/Projet/Drivers/BSP/STM32F769I-Discovery" -I"C:/PerfectTuning/Projet/Utilities/Fonts" -I"C:/PerfectTuning/Projet/Drivers"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



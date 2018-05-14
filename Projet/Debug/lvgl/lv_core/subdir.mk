################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lv_core/lv_group.c \
../lvgl/lv_core/lv_indev.c \
../lvgl/lv_core/lv_obj.c \
../lvgl/lv_core/lv_refr.c \
../lvgl/lv_core/lv_style.c \
../lvgl/lv_core/lv_vdb.c 

OBJS += \
./lvgl/lv_core/lv_group.o \
./lvgl/lv_core/lv_indev.o \
./lvgl/lv_core/lv_obj.o \
./lvgl/lv_core/lv_refr.o \
./lvgl/lv_core/lv_style.o \
./lvgl/lv_core/lv_vdb.o 

C_DEPS += \
./lvgl/lv_core/lv_group.d \
./lvgl/lv_core/lv_indev.d \
./lvgl/lv_core/lv_obj.d \
./lvgl/lv_core/lv_refr.d \
./lvgl/lv_core/lv_style.d \
./lvgl/lv_core/lv_vdb.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lv_core/%.o: ../lvgl/lv_core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F769xx -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Inc" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers/STM32F7xx_HAL_Driver/Inc" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers/CMSIS/Include" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/lv_examples" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers/BSP/Components" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers/BSP/STM32F769I-Discovery" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Utilities/Fonts" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



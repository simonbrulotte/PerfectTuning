################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lv_themes/lv_theme.c \
../lvgl/lv_themes/lv_theme_alien.c \
../lvgl/lv_themes/lv_theme_default.c \
../lvgl/lv_themes/lv_theme_material.c \
../lvgl/lv_themes/lv_theme_mono.c \
../lvgl/lv_themes/lv_theme_night.c \
../lvgl/lv_themes/lv_theme_templ.c \
../lvgl/lv_themes/lv_theme_zen.c 

OBJS += \
./lvgl/lv_themes/lv_theme.o \
./lvgl/lv_themes/lv_theme_alien.o \
./lvgl/lv_themes/lv_theme_default.o \
./lvgl/lv_themes/lv_theme_material.o \
./lvgl/lv_themes/lv_theme_mono.o \
./lvgl/lv_themes/lv_theme_night.o \
./lvgl/lv_themes/lv_theme_templ.o \
./lvgl/lv_themes/lv_theme_zen.o 

C_DEPS += \
./lvgl/lv_themes/lv_theme.d \
./lvgl/lv_themes/lv_theme_alien.d \
./lvgl/lv_themes/lv_theme_default.d \
./lvgl/lv_themes/lv_theme_material.d \
./lvgl/lv_themes/lv_theme_mono.d \
./lvgl/lv_themes/lv_theme_night.d \
./lvgl/lv_themes/lv_theme_templ.d \
./lvgl/lv_themes/lv_theme_zen.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lv_themes/%.o: ../lvgl/lv_themes/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F769xx -I"C:/PerfectTuning/Projet/Inc" -I"C:/PerfectTuning/Projet/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/PerfectTuning/Projet/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"C:/PerfectTuning/Projet/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/PerfectTuning/Projet/Drivers/CMSIS/Include" -I"C:/PerfectTuning/Projet" -I"C:/PerfectTuning/Projet/lv_examples" -I"C:/PerfectTuning/Projet/Drivers/BSP/Components" -I"C:/PerfectTuning/Projet/Drivers/BSP/STM32F769I-Discovery" -I"C:/PerfectTuning/Projet/Utilities/Fonts" -I"C:/PerfectTuning/Projet/Drivers"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



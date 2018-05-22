################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lv_misc/lv_fonts/lv_font_dejavu_142.c \
../lvgl/lv_misc/lv_fonts/lv_font_dejavu_20.c \
../lvgl/lv_misc/lv_fonts/lv_font_dejavu_20_cyrillic.c \
../lvgl/lv_misc/lv_fonts/lv_font_dejavu_20_latin_sup.c \
../lvgl/lv_misc/lv_fonts/lv_font_dejavu_240.c \
../lvgl/lv_misc/lv_fonts/lv_font_dejavu_96.c 

OBJS += \
./lvgl/lv_misc/lv_fonts/lv_font_dejavu_142.o \
./lvgl/lv_misc/lv_fonts/lv_font_dejavu_20.o \
./lvgl/lv_misc/lv_fonts/lv_font_dejavu_20_cyrillic.o \
./lvgl/lv_misc/lv_fonts/lv_font_dejavu_20_latin_sup.o \
./lvgl/lv_misc/lv_fonts/lv_font_dejavu_240.o \
./lvgl/lv_misc/lv_fonts/lv_font_dejavu_96.o 

C_DEPS += \
./lvgl/lv_misc/lv_fonts/lv_font_dejavu_142.d \
./lvgl/lv_misc/lv_fonts/lv_font_dejavu_20.d \
./lvgl/lv_misc/lv_fonts/lv_font_dejavu_20_cyrillic.d \
./lvgl/lv_misc/lv_fonts/lv_font_dejavu_20_latin_sup.d \
./lvgl/lv_misc/lv_fonts/lv_font_dejavu_240.d \
./lvgl/lv_misc/lv_fonts/lv_font_dejavu_96.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lv_misc/lv_fonts/%.o: ../lvgl/lv_misc/lv_fonts/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F769xx -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Inc" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers/STM32F7xx_HAL_Driver/Inc" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers/CMSIS/Include" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/lv_examples" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers/BSP/Components" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers/BSP/STM32F769I-Discovery" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Utilities/Fonts" -I"D:/Bibliotheque/Documents/GitHub/PerfectTuning/Projet/Drivers"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



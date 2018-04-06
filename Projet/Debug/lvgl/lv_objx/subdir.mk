################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lv_objx/lv_bar.c \
../lvgl/lv_objx/lv_btn.c \
../lvgl/lv_objx/lv_btnm.c \
../lvgl/lv_objx/lv_cb.c \
../lvgl/lv_objx/lv_chart.c \
../lvgl/lv_objx/lv_cont.c \
../lvgl/lv_objx/lv_ddlist.c \
../lvgl/lv_objx/lv_gauge.c \
../lvgl/lv_objx/lv_img.c \
../lvgl/lv_objx/lv_kb.c \
../lvgl/lv_objx/lv_label.c \
../lvgl/lv_objx/lv_led.c \
../lvgl/lv_objx/lv_line.c \
../lvgl/lv_objx/lv_list.c \
../lvgl/lv_objx/lv_lmeter.c \
../lvgl/lv_objx/lv_mbox.c \
../lvgl/lv_objx/lv_objx_templ.c \
../lvgl/lv_objx/lv_page.c \
../lvgl/lv_objx/lv_roller.c \
../lvgl/lv_objx/lv_slider.c \
../lvgl/lv_objx/lv_sw.c \
../lvgl/lv_objx/lv_ta.c \
../lvgl/lv_objx/lv_tabview.c \
../lvgl/lv_objx/lv_win.c 

OBJS += \
./lvgl/lv_objx/lv_bar.o \
./lvgl/lv_objx/lv_btn.o \
./lvgl/lv_objx/lv_btnm.o \
./lvgl/lv_objx/lv_cb.o \
./lvgl/lv_objx/lv_chart.o \
./lvgl/lv_objx/lv_cont.o \
./lvgl/lv_objx/lv_ddlist.o \
./lvgl/lv_objx/lv_gauge.o \
./lvgl/lv_objx/lv_img.o \
./lvgl/lv_objx/lv_kb.o \
./lvgl/lv_objx/lv_label.o \
./lvgl/lv_objx/lv_led.o \
./lvgl/lv_objx/lv_line.o \
./lvgl/lv_objx/lv_list.o \
./lvgl/lv_objx/lv_lmeter.o \
./lvgl/lv_objx/lv_mbox.o \
./lvgl/lv_objx/lv_objx_templ.o \
./lvgl/lv_objx/lv_page.o \
./lvgl/lv_objx/lv_roller.o \
./lvgl/lv_objx/lv_slider.o \
./lvgl/lv_objx/lv_sw.o \
./lvgl/lv_objx/lv_ta.o \
./lvgl/lv_objx/lv_tabview.o \
./lvgl/lv_objx/lv_win.o 

C_DEPS += \
./lvgl/lv_objx/lv_bar.d \
./lvgl/lv_objx/lv_btn.d \
./lvgl/lv_objx/lv_btnm.d \
./lvgl/lv_objx/lv_cb.d \
./lvgl/lv_objx/lv_chart.d \
./lvgl/lv_objx/lv_cont.d \
./lvgl/lv_objx/lv_ddlist.d \
./lvgl/lv_objx/lv_gauge.d \
./lvgl/lv_objx/lv_img.d \
./lvgl/lv_objx/lv_kb.d \
./lvgl/lv_objx/lv_label.d \
./lvgl/lv_objx/lv_led.d \
./lvgl/lv_objx/lv_line.d \
./lvgl/lv_objx/lv_list.d \
./lvgl/lv_objx/lv_lmeter.d \
./lvgl/lv_objx/lv_mbox.d \
./lvgl/lv_objx/lv_objx_templ.d \
./lvgl/lv_objx/lv_page.d \
./lvgl/lv_objx/lv_roller.d \
./lvgl/lv_objx/lv_slider.d \
./lvgl/lv_objx/lv_sw.d \
./lvgl/lv_objx/lv_ta.d \
./lvgl/lv_objx/lv_tabview.d \
./lvgl/lv_objx/lv_win.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lv_objx/%.o: ../lvgl/lv_objx/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F769xx -I"C:/Users/TophersAlien/workspace/Projet/Inc" -I"C:/Users/TophersAlien/workspace/Projet/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/Users/TophersAlien/workspace/Projet/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"C:/Users/TophersAlien/workspace/Projet/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/TophersAlien/workspace/Projet/Drivers/CMSIS/Include" -I"C:/Users/TophersAlien/workspace/Projet" -I"C:/Users/TophersAlien/workspace/Projet/lv_examples" -I"C:/Users/TophersAlien/workspace/Projet/Drivers/BSP/Components" -I"C:/Users/TophersAlien/workspace/Projet/Drivers/BSP/STM32F769I-Discovery" -I"C:/Users/TophersAlien/workspace/Projet/Utilities/Fonts" -I"C:/Users/TophersAlien/workspace/Projet/Drivers"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



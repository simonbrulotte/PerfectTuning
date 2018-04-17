################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include lvgl/lv_themes/subdir.mk
-include lvgl/lv_objx/subdir.mk
-include lvgl/lv_misc/lv_fonts/subdir.mk
-include lvgl/lv_misc/subdir.mk
-include lvgl/lv_hal/subdir.mk
-include lvgl/lv_draw/subdir.mk
-include lvgl/lv_core/subdir.mk
-include lv_examples/lv_tutorial/9_responsive/subdir.mk
-include lv_examples/lv_tutorial/8_animations/subdir.mk
-include lv_examples/lv_tutorial/7_fonts/subdir.mk
-include lv_examples/lv_tutorial/6_images/subdir.mk
-include lv_examples/lv_tutorial/5_antialiasing/subdir.mk
-include lv_examples/lv_tutorial/4_themes/subdir.mk
-include lv_examples/lv_tutorial/3_styles/subdir.mk
-include lv_examples/lv_tutorial/2_objects/subdir.mk
-include lv_examples/lv_tutorial/1_hello_world/subdir.mk
-include lv_examples/lv_tutorial/10_keyboard/subdir.mk
-include lv_examples/lv_tutorial/0_porting/subdir.mk
-include lv_examples/lv_tests/lv_test_theme/subdir.mk
-include lv_examples/lv_tests/lv_test_stress/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_win/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_tabview/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_ta/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_sw/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_slider/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_roller/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_page/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_mbox/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_lmeter/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_list/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_line/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_led/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_label/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_kb/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_img/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_gauge/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_ddlist/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_cont/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_chart/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_cb/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_btnm/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_btn/subdir.mk
-include lv_examples/lv_tests/lv_test_objx/lv_test_bar/subdir.mk
-include lv_examples/lv_tests/lv_test_obj/subdir.mk
-include lv_examples/lv_tests/lv_test_misc/subdir.mk
-include lv_examples/lv_tests/lv_test_group/subdir.mk
-include lv_examples/lv_apps/tpcal/subdir.mk
-include lv_examples/lv_apps/terminal/subdir.mk
-include lv_examples/lv_apps/sysmon/subdir.mk
-include lv_examples/lv_apps/demo/subdir.mk
-include lv_examples/lv_apps/benchmark/subdir.mk
-include Utilities/Fonts/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/STM32F769I-Discovery/subdir.mk
-include Drivers/BSP/Components/wm8994/subdir.mk
-include Drivers/BSP/Components/ts3510/subdir.mk
-include Drivers/BSP/Components/stmpe811/subdir.mk
-include Drivers/BSP/Components/st7789h2/subdir.mk
-include Drivers/BSP/Components/st7735/subdir.mk
-include Drivers/BSP/Components/s5k5cag/subdir.mk
-include Drivers/BSP/Components/ov9655/subdir.mk
-include Drivers/BSP/Components/otm8009a/subdir.mk
-include Drivers/BSP/Components/mfxstm32l152/subdir.mk
-include Drivers/BSP/Components/ft6x06/subdir.mk
-include Drivers/BSP/Components/ft5336/subdir.mk
-include Drivers/BSP/Components/exc7200/subdir.mk
-include Drivers/BSP/Components/adv7533/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Projet.elf

# Tool invocations
Projet.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU G++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -L"D:\Documents\GitHub\PerfectTuning\Projet\Debug\lvgl\lv_objx" -L"D:\Documents\GitHub\PerfectTuning\Projet\lv_examples" -L"D:\Documents\GitHub\PerfectTuning\Projet\Drivers\BSP" -L"D:\Documents\GitHub\PerfectTuning\Projet\Src" -specs=nosys.specs -specs=nano.specs -T"../STM32F769NIHx_FLASH.ld" -Wl,-Map=output.map -Wl,--gc-sections -fno-exceptions -fno-rtti -o "Projet.elf" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O binary "Projet.elf" "Projet.bin"
	arm-none-eabi-size "Projet.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32H5xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/STM32H5xx_Nucleo/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Core/Middlewares/TinyUSB/src/typec/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/wch/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/valentyusb/eptri/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/ti/msp430x5xx/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/template/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/synopsys/dwc2/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/sunxi/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/st/typec/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/st/stm32_fsdev/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/sony/cxd56/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/renesas/rusb2/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/raspberrypi/rp2040/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/raspberrypi/pio_usb/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/ohci/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/nxp/lpc_ip3511/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/nxp/lpc17_40/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/nxp/khci/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/nuvoton/nuc505/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/nuvoton/nuc121/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/nuvoton/nuc120/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/nordic/nrf5x/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/mindmotion/mm32/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/microchip/samx7x/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/microchip/samg/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/microchip/samd/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/microchip/pic32mz/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/microchip/pic/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/mentor/musb/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/ehci/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/dialog/da146xx/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/chipidea/ci_hs/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/chipidea/ci_fs/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/bridgetek/ft9xx/subdir.mk
-include Core/Middlewares/TinyUSB/src/portable/analog/max3421/subdir.mk
-include Core/Middlewares/TinyUSB/src/host/subdir.mk
-include Core/Middlewares/TinyUSB/src/device/subdir.mk
-include Core/Middlewares/TinyUSB/src/common/subdir.mk
-include Core/Middlewares/TinyUSB/src/class/video/subdir.mk
-include Core/Middlewares/TinyUSB/src/class/vendor/subdir.mk
-include Core/Middlewares/TinyUSB/src/class/usbtmc/subdir.mk
-include Core/Middlewares/TinyUSB/src/class/net/subdir.mk
-include Core/Middlewares/TinyUSB/src/class/mtp/subdir.mk
-include Core/Middlewares/TinyUSB/src/class/msc/subdir.mk
-include Core/Middlewares/TinyUSB/src/class/midi/subdir.mk
-include Core/Middlewares/TinyUSB/src/class/hid/subdir.mk
-include Core/Middlewares/TinyUSB/src/class/dfu/subdir.mk
-include Core/Middlewares/TinyUSB/src/class/cdc/subdir.mk
-include Core/Middlewares/TinyUSB/src/class/bth/subdir.mk
-include Core/Middlewares/TinyUSB/src/class/audio/subdir.mk
-include Core/Middlewares/TinyUSB/src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := MIDI controller
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
MIDI\ controller.elf \

MAP_FILES += \
MIDI\ controller.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
MIDI\ controller.list \


# All Target
all: main-build

# Main-build Target
main-build: MIDI\ controller.elf secondary-outputs

# Tool invocations
MIDI\ controller.elf MIDI\ controller.map: $(OBJS) $(USER_OBJS) C:\EntertainmentTech\MIDI\ controller\STM32H533RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "MIDI controller.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m33 -T"C:\EntertainmentTech\MIDI controller\STM32H533RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="MIDI controller.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

MIDI\ controller.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "MIDI controller.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) MIDI\ controller.elf MIDI\ controller.list MIDI\ controller.map MIDI\\ controller.elf default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets

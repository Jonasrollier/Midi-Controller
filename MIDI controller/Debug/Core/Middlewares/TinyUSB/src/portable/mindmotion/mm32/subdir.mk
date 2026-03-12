################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Middlewares/TinyUSB/src/portable/mindmotion/mm32/dcd_mm32f327x_otg.c 

OBJS += \
./Core/Middlewares/TinyUSB/src/portable/mindmotion/mm32/dcd_mm32f327x_otg.o 

C_DEPS += \
./Core/Middlewares/TinyUSB/src/portable/mindmotion/mm32/dcd_mm32f327x_otg.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Middlewares/TinyUSB/src/portable/mindmotion/mm32/%.o Core/Middlewares/TinyUSB/src/portable/mindmotion/mm32/%.su Core/Middlewares/TinyUSB/src/portable/mindmotion/mm32/%.cyclo: ../Core/Middlewares/TinyUSB/src/portable/mindmotion/mm32/%.c Core/Middlewares/TinyUSB/src/portable/mindmotion/mm32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32H533xx -c -I../Core/Inc -I"C:/EntertainmentTech/MIDI controller/Core/Middlewares/TinyUSB/src" -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32H5xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Middlewares-2f-TinyUSB-2f-src-2f-portable-2f-mindmotion-2f-mm32

clean-Core-2f-Middlewares-2f-TinyUSB-2f-src-2f-portable-2f-mindmotion-2f-mm32:
	-$(RM) ./Core/Middlewares/TinyUSB/src/portable/mindmotion/mm32/dcd_mm32f327x_otg.cyclo ./Core/Middlewares/TinyUSB/src/portable/mindmotion/mm32/dcd_mm32f327x_otg.d ./Core/Middlewares/TinyUSB/src/portable/mindmotion/mm32/dcd_mm32f327x_otg.o ./Core/Middlewares/TinyUSB/src/portable/mindmotion/mm32/dcd_mm32f327x_otg.su

.PHONY: clean-Core-2f-Middlewares-2f-TinyUSB-2f-src-2f-portable-2f-mindmotion-2f-mm32


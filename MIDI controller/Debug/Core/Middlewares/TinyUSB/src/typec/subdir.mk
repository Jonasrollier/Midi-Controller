################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Middlewares/TinyUSB/src/typec/usbc.c 

OBJS += \
./Core/Middlewares/TinyUSB/src/typec/usbc.o 

C_DEPS += \
./Core/Middlewares/TinyUSB/src/typec/usbc.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Middlewares/TinyUSB/src/typec/%.o Core/Middlewares/TinyUSB/src/typec/%.su Core/Middlewares/TinyUSB/src/typec/%.cyclo: ../Core/Middlewares/TinyUSB/src/typec/%.c Core/Middlewares/TinyUSB/src/typec/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32H533xx -c -I../Core/Inc -I"C:/EntertainmentTech/MIDI controller/Core/Middlewares/TinyUSB/src" -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32H5xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Middlewares-2f-TinyUSB-2f-src-2f-typec

clean-Core-2f-Middlewares-2f-TinyUSB-2f-src-2f-typec:
	-$(RM) ./Core/Middlewares/TinyUSB/src/typec/usbc.cyclo ./Core/Middlewares/TinyUSB/src/typec/usbc.d ./Core/Middlewares/TinyUSB/src/typec/usbc.o ./Core/Middlewares/TinyUSB/src/typec/usbc.su

.PHONY: clean-Core-2f-Middlewares-2f-TinyUSB-2f-src-2f-typec


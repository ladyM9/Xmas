################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libs/WS2812B.c \
../libs/buzzer.c 

OBJS += \
./libs/WS2812B.o \
./libs/buzzer.o 

C_DEPS += \
./libs/WS2812B.d \
./libs/buzzer.d 


# Each subdirectory must supply rules for building sources it contributes
libs/%.o libs/%.su libs/%.cyclo: ../libs/%.c libs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32C011xx -c -I../Core/Inc -I../Drivers/STM32C0xx_HAL_Driver/Inc -I../Drivers/STM32C0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32C0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Marina/Documents/GitHub/Xmas/Xmas/Xmas/libs" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-libs

clean-libs:
	-$(RM) ./libs/WS2812B.cyclo ./libs/WS2812B.d ./libs/WS2812B.o ./libs/WS2812B.su ./libs/buzzer.cyclo ./libs/buzzer.d ./libs/buzzer.o ./libs/buzzer.su

.PHONY: clean-libs


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libs/.metadata/.plugins/org.eclipse.cdt.make.core/specs.c 

OBJS += \
./libs/.metadata/.plugins/org.eclipse.cdt.make.core/specs.o 

C_DEPS += \
./libs/.metadata/.plugins/org.eclipse.cdt.make.core/specs.d 


# Each subdirectory must supply rules for building sources it contributes
libs/.metadata/.plugins/org.eclipse.cdt.make.core/%.o libs/.metadata/.plugins/org.eclipse.cdt.make.core/%.su libs/.metadata/.plugins/org.eclipse.cdt.make.core/%.cyclo: ../libs/.metadata/.plugins/org.eclipse.cdt.make.core/%.c libs/.metadata/.plugins/org.eclipse.cdt.make.core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32C011xx -c -I../Core/Inc -I../Drivers/STM32C0xx_HAL_Driver/Inc -I../Drivers/STM32C0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32C0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Marina/Documents/GitHub/Xmas/Xmas/Xmas/libs" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-libs-2f--2e-metadata-2f--2e-plugins-2f-org-2e-eclipse-2e-cdt-2e-make-2e-core

clean-libs-2f--2e-metadata-2f--2e-plugins-2f-org-2e-eclipse-2e-cdt-2e-make-2e-core:
	-$(RM) ./libs/.metadata/.plugins/org.eclipse.cdt.make.core/specs.cyclo ./libs/.metadata/.plugins/org.eclipse.cdt.make.core/specs.d ./libs/.metadata/.plugins/org.eclipse.cdt.make.core/specs.o ./libs/.metadata/.plugins/org.eclipse.cdt.make.core/specs.su

.PHONY: clean-libs-2f--2e-metadata-2f--2e-plugins-2f-org-2e-eclipse-2e-cdt-2e-make-2e-core


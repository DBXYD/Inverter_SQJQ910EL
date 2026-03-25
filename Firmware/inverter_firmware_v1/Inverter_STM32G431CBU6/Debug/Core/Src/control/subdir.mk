################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/control/control.c \
../Core/Src/control/motor.c 

OBJS += \
./Core/Src/control/control.o \
./Core/Src/control/motor.o 

C_DEPS += \
./Core/Src/control/control.d \
./Core/Src/control/motor.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/control/%.o Core/Src/control/%.su Core/Src/control/%.cyclo: ../Core/Src/control/%.c Core/Src/control/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-control

clean-Core-2f-Src-2f-control:
	-$(RM) ./Core/Src/control/control.cyclo ./Core/Src/control/control.d ./Core/Src/control/control.o ./Core/Src/control/control.su ./Core/Src/control/motor.cyclo ./Core/Src/control/motor.d ./Core/Src/control/motor.o ./Core/Src/control/motor.su

.PHONY: clean-Core-2f-Src-2f-control


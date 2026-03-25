################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/acquisition/analog.c \
../Core/Src/acquisition/encoder.c 

OBJS += \
./Core/Src/acquisition/analog.o \
./Core/Src/acquisition/encoder.o 

C_DEPS += \
./Core/Src/acquisition/analog.d \
./Core/Src/acquisition/encoder.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/acquisition/%.o Core/Src/acquisition/%.su Core/Src/acquisition/%.cyclo: ../Core/Src/acquisition/%.c Core/Src/acquisition/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-acquisition

clean-Core-2f-Src-2f-acquisition:
	-$(RM) ./Core/Src/acquisition/analog.cyclo ./Core/Src/acquisition/analog.d ./Core/Src/acquisition/analog.o ./Core/Src/acquisition/analog.su ./Core/Src/acquisition/encoder.cyclo ./Core/Src/acquisition/encoder.d ./Core/Src/acquisition/encoder.o ./Core/Src/acquisition/encoder.su

.PHONY: clean-Core-2f-Src-2f-acquisition


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cpp/Src/lsm6ds3.cpp \
../cpp/Src/main_code.cpp 

OBJS += \
./cpp/Src/lsm6ds3.o \
./cpp/Src/main_code.o 

CPP_DEPS += \
./cpp/Src/lsm6ds3.d \
./cpp/Src/main_code.d 


# Each subdirectory must supply rules for building sources it contributes
cpp/Src/%.o cpp/Src/%.su cpp/Src/%.cyclo: ../cpp/Src/%.cpp cpp/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Soltrex/Documents/git_repos/lior-sc/stm32_NUCLEOF401RE_basics/nucleo-f401re-lsm6ds3_test/cpp/Inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-cpp-2f-Src

clean-cpp-2f-Src:
	-$(RM) ./cpp/Src/lsm6ds3.cyclo ./cpp/Src/lsm6ds3.d ./cpp/Src/lsm6ds3.o ./cpp/Src/lsm6ds3.su ./cpp/Src/main_code.cyclo ./cpp/Src/main_code.d ./cpp/Src/main_code.o ./cpp/Src/main_code.su

.PHONY: clean-cpp-2f-Src


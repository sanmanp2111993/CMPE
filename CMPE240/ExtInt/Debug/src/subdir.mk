################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ExtInt.cpp \
../src/GPIO.cpp \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc175x_6x.cpp \
../src/timer.cpp 

C_SRCS += \
../src/crp.c 

OBJS += \
./src/ExtInt.o \
./src/GPIO.o \
./src/cr_cpp_config.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/timer.o 

C_DEPS += \
./src/crp.d 

CPP_DEPS += \
./src/ExtInt.d \
./src/GPIO.d \
./src/cr_cpp_config.d \
./src/cr_startup_lpc175x_6x.d \
./src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -DCPP_USE_HEAP -D__LPC17XX__ -I"/home/dheeraj/LPCXpresso/workspace/CMSIS_CORE_LPC17xx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -DCPP_USE_HEAP -D__LPC17XX__ -I"/home/dheeraj/LPCXpresso/workspace/CMSIS_CORE_LPC17xx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/adcuser.c \
../src/cdcuser.c \
../src/cos.c \
../src/cr_startup_lpc11u.c \
../src/fct.c \
../src/gpio.c \
../src/serial.c \
../src/usbcore.c \
../src/usbdesc.c \
../src/usbdmain.c \
../src/usbhw.c \
../src/usbuser.c 

OBJS += \
./src/adcuser.o \
./src/cdcuser.o \
./src/cos.o \
./src/cr_startup_lpc11u.o \
./src/fct.o \
./src/gpio.o \
./src/serial.o \
./src/usbcore.o \
./src/usbdesc.o \
./src/usbdmain.o \
./src/usbhw.o \
./src/usbuser.o 

C_DEPS += \
./src/adcuser.d \
./src/cdcuser.d \
./src/cos.d \
./src/cr_startup_lpc11u.d \
./src/fct.d \
./src/gpio.d \
./src/serial.d \
./src/usbcore.d \
./src/usbdesc.d \
./src/usbdmain.d \
./src/usbhw.d \
./src/usbuser.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC11Uxx -I"C:\Users\nxp41306\Documents\LPCXpresso_4.0.5_123\workspace\CMSISv2p00_LPC11Uxx\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/cr_startup_lpc11u.o: ../src/cr_startup_lpc11u.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC11Uxx -I"C:\Users\nxp41306\Documents\LPCXpresso_4.0.5_123\workspace\CMSISv2p00_LPC11Uxx\inc" -O0 -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_lpc11u.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



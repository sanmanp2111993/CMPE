################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: LPCXpresso11U14_usbaudiowithFFT.axf

# Tool invocations
LPCXpresso11U14_usbaudiowithFFT.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\andy.rikin\Documents\lpcxpresso_3.6.3_317\workspace\CMSISv2p00_LPC11Uxx\Release" -Xlinker -Map=LPCXpresso11U14_usbaudiowithFFT.map -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "LPCXpresso11U14_usbaudiowithFFT_Release.ld" -o"LPCXpresso11U14_usbaudiowithFFT.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) LPCXpresso11U14_usbaudiowithFFT.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size LPCXpresso11U14_usbaudiowithFFT.axf; # arm-none-eabi-objcopy -O binary LPCXpresso11U14_usbaudiowithFFT.axf LPCXpresso11U14_usbaudiowithFFT.bin ; checksum -p LPC11U14_201 -d LPCXpresso11U14_usbaudiowithFFT.bin;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

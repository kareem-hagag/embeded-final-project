################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/USART/subdir.mk
-include MCAL/TIM0/subdir.mk
-include MCAL/LCD_1/subdir.mk
-include MCAL/KEYPAD/subdir.mk
-include MCAL/DIO_1/subdir.mk
-include MCAL/ADC/subdir.mk
-include APP/subdir.mk
-include .metadata/.plugins/org.eclipse.cdt.make.core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
nti45.lss \

FLASH_IMAGE += \
nti45.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: nti45.elf secondary-outputs

# Tool invocations
nti45.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,nti45.map -mmcu=atmega32 -o "nti45.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

nti45.lss: nti45.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S nti45.elf  >"nti45.lss"
	@echo 'Finished building: $@'
	@echo ' '

nti45.hex: nti45.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex nti45.elf  "nti45.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: nti45.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 nti45.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) nti45.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/LCD_1/LCD_prog.c 

OBJS += \
./MCAL/LCD_1/LCD_prog.o 

C_DEPS += \
./MCAL/LCD_1/LCD_prog.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/LCD_1/%.o: ../MCAL/LCD_1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\Mohamed\Desktop\Drivers\nti45\STD_LIB" -I"C:\Users\Mohamed\Desktop\Drivers\nti45\MCAL" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



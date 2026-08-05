################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mcal/DIO/Dio_prog.c 

OBJS += \
./mcal/DIO/Dio_prog.o 

C_DEPS += \
./mcal/DIO/Dio_prog.d 


# Each subdirectory must supply rules for building sources it contributes
mcal/DIO/%.o: ../mcal/DIO/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\karee\OneDrive\Desktop\final project kareem" -I"C:\Users\karee\OneDrive\Desktop\final project kareem\mcal" -I"C:\Users\karee\OneDrive\Desktop\final project kareem\mcal\DIO" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



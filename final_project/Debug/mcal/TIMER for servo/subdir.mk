################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mcal/TIMER\ for\ servo/Timer1_prog.c 

OBJS += \
./mcal/TIMER\ for\ servo/Timer1_prog.o 

C_DEPS += \
./mcal/TIMER\ for\ servo/Timer1_prog.d 


# Each subdirectory must supply rules for building sources it contributes
mcal/TIMER\ for\ servo/Timer1_prog.o: ../mcal/TIMER\ for\ servo/Timer1_prog.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\karee\OneDrive\Desktop\final project kareem" -I"C:\Users\karee\OneDrive\Desktop\final project kareem\mcal" -I"C:\Users\karee\OneDrive\Desktop\final project kareem\mcal\DIO" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"mcal/TIMER for servo/Timer1_prog.d" -MT"mcal/TIMER\ for\ servo/Timer1_prog.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



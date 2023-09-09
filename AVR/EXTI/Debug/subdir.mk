################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_prog.c \
../EXTI_config.c \
../EXTI_prog.c \
../GIE.c \
../LCD_prog.c \
../PORT__Prog.c \
../main.c 

OBJS += \
./DIO_prog.o \
./EXTI_config.o \
./EXTI_prog.o \
./GIE.o \
./LCD_prog.o \
./PORT__Prog.o \
./main.o 

C_DEPS += \
./DIO_prog.d \
./EXTI_config.d \
./EXTI_prog.d \
./GIE.d \
./LCD_prog.d \
./PORT__Prog.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCU2.c \
../buzzer.c \
../gpio.c \
../led.c \
../timer1.c \
../uart.c 

OBJS += \
./MCU2.o \
./buzzer.o \
./gpio.o \
./led.o \
./timer1.o \
./uart.o 

C_DEPS += \
./MCU2.d \
./buzzer.d \
./gpio.d \
./led.d \
./timer1.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



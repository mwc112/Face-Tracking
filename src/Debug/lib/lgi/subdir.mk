################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/lgi/buffer.c \
../lib/lgi/callable.c \
../lib/lgi/core.c \
../lib/lgi/gi.c \
../lib/lgi/marshal.c \
../lib/lgi/object.c \
../lib/lgi/record.c 

OBJS += \
./lib/lgi/buffer.o \
./lib/lgi/callable.o \
./lib/lgi/core.o \
./lib/lgi/gi.o \
./lib/lgi/marshal.o \
./lib/lgi/object.o \
./lib/lgi/record.o 

C_DEPS += \
./lib/lgi/buffer.d \
./lib/lgi/callable.d \
./lib/lgi/core.d \
./lib/lgi/gi.d \
./lib/lgi/marshal.d \
./lib/lgi/object.d \
./lib/lgi/record.d 


# Each subdirectory must supply rules for building sources it contributes
lib/lgi/%.o: ../lib/lgi/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/awesome/objects/button.c \
../lib/awesome/objects/client.c \
../lib/awesome/objects/drawable.c \
../lib/awesome/objects/drawin.c \
../lib/awesome/objects/key.c \
../lib/awesome/objects/screen.c \
../lib/awesome/objects/tag.c \
../lib/awesome/objects/window.c 

OBJS += \
./lib/awesome/objects/button.o \
./lib/awesome/objects/client.o \
./lib/awesome/objects/drawable.o \
./lib/awesome/objects/drawin.o \
./lib/awesome/objects/key.o \
./lib/awesome/objects/screen.o \
./lib/awesome/objects/tag.o \
./lib/awesome/objects/window.o 

C_DEPS += \
./lib/awesome/objects/button.d \
./lib/awesome/objects/client.d \
./lib/awesome/objects/drawable.d \
./lib/awesome/objects/drawin.d \
./lib/awesome/objects/key.d \
./lib/awesome/objects/screen.d \
./lib/awesome/objects/tag.d \
./lib/awesome/objects/window.d 


# Each subdirectory must supply rules for building sources it contributes
lib/awesome/objects/%.o: ../lib/awesome/objects/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



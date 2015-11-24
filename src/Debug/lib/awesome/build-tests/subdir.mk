################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/awesome/build-tests/__builtin_clz.c 

OBJS += \
./lib/awesome/build-tests/__builtin_clz.o 

C_DEPS += \
./lib/awesome/build-tests/__builtin_clz.d 


# Each subdirectory must supply rules for building sources it contributes
lib/awesome/build-tests/%.o: ../lib/awesome/build-tests/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



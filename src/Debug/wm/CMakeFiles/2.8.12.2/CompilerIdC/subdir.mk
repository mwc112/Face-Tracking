################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../wm/CMakeFiles/2.8.12.2/CompilerIdC/CMakeCCompilerId.c 

OBJS += \
./wm/CMakeFiles/2.8.12.2/CompilerIdC/CMakeCCompilerId.o 

C_DEPS += \
./wm/CMakeFiles/2.8.12.2/CompilerIdC/CMakeCCompilerId.d 


# Each subdirectory must supply rules for building sources it contributes
wm/CMakeFiles/2.8.12.2/CompilerIdC/%.o: ../wm/CMakeFiles/2.8.12.2/CompilerIdC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



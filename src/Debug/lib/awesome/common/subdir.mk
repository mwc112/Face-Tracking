################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/awesome/common/atoms.c \
../lib/awesome/common/backtrace.c \
../lib/awesome/common/buffer.c \
../lib/awesome/common/luaclass.c \
../lib/awesome/common/lualib.c \
../lib/awesome/common/luaobject.c \
../lib/awesome/common/util.c \
../lib/awesome/common/version.c \
../lib/awesome/common/xcursor.c \
../lib/awesome/common/xembed.c \
../lib/awesome/common/xutil.c 

OBJS += \
./lib/awesome/common/atoms.o \
./lib/awesome/common/backtrace.o \
./lib/awesome/common/buffer.o \
./lib/awesome/common/luaclass.o \
./lib/awesome/common/lualib.o \
./lib/awesome/common/luaobject.o \
./lib/awesome/common/util.o \
./lib/awesome/common/version.o \
./lib/awesome/common/xcursor.o \
./lib/awesome/common/xembed.o \
./lib/awesome/common/xutil.o 

C_DEPS += \
./lib/awesome/common/atoms.d \
./lib/awesome/common/backtrace.d \
./lib/awesome/common/buffer.d \
./lib/awesome/common/luaclass.d \
./lib/awesome/common/lualib.d \
./lib/awesome/common/luaobject.d \
./lib/awesome/common/util.d \
./lib/awesome/common/version.d \
./lib/awesome/common/xcursor.d \
./lib/awesome/common/xembed.d \
./lib/awesome/common/xutil.d 


# Each subdirectory must supply rules for building sources it contributes
lib/awesome/common/%.o: ../lib/awesome/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



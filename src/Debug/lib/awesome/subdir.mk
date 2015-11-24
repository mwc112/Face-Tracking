################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/awesome/awesome.c \
../lib/awesome/banning.c \
../lib/awesome/color.c \
../lib/awesome/dbus.c \
../lib/awesome/draw.c \
../lib/awesome/event.c \
../lib/awesome/ewmh.c \
../lib/awesome/keygrabber.c \
../lib/awesome/luaa.c \
../lib/awesome/mouse.c \
../lib/awesome/mousegrabber.c \
../lib/awesome/property.c \
../lib/awesome/root.c \
../lib/awesome/selection.c \
../lib/awesome/spawn.c \
../lib/awesome/stack.c \
../lib/awesome/strut.c \
../lib/awesome/systray.c \
../lib/awesome/xkb.c \
../lib/awesome/xrdb.c \
../lib/awesome/xwindow.c 

OBJS += \
./lib/awesome/awesome.o \
./lib/awesome/banning.o \
./lib/awesome/color.o \
./lib/awesome/dbus.o \
./lib/awesome/draw.o \
./lib/awesome/event.o \
./lib/awesome/ewmh.o \
./lib/awesome/keygrabber.o \
./lib/awesome/luaa.o \
./lib/awesome/mouse.o \
./lib/awesome/mousegrabber.o \
./lib/awesome/property.o \
./lib/awesome/root.o \
./lib/awesome/selection.o \
./lib/awesome/spawn.o \
./lib/awesome/stack.o \
./lib/awesome/strut.o \
./lib/awesome/systray.o \
./lib/awesome/xkb.o \
./lib/awesome/xrdb.o \
./lib/awesome/xwindow.o 

C_DEPS += \
./lib/awesome/awesome.d \
./lib/awesome/banning.d \
./lib/awesome/color.d \
./lib/awesome/dbus.d \
./lib/awesome/draw.d \
./lib/awesome/event.d \
./lib/awesome/ewmh.d \
./lib/awesome/keygrabber.d \
./lib/awesome/luaa.d \
./lib/awesome/mouse.d \
./lib/awesome/mousegrabber.d \
./lib/awesome/property.d \
./lib/awesome/root.d \
./lib/awesome/selection.d \
./lib/awesome/spawn.d \
./lib/awesome/stack.d \
./lib/awesome/strut.d \
./lib/awesome/systray.d \
./lib/awesome/xkb.d \
./lib/awesome/xrdb.d \
./lib/awesome/xwindow.d 


# Each subdirectory must supply rules for building sources it contributes
lib/awesome/%.o: ../lib/awesome/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



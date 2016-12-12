################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../proj/app/usbaud.c \
../proj/app/usbcdc.c \
../proj/app/usbkb.c \
../proj/app/usbmouse.c \
../proj/app/usbms.c \
../proj/app/usbsomatic.c 

OBJS += \
./proj/app/usbaud.o \
./proj/app/usbcdc.o \
./proj/app/usbkb.o \
./proj/app/usbmouse.o \
./proj/app/usbms.o \
./proj/app/usbsomatic.o 


# Each subdirectory must supply rules for building sources it contributes
proj/app/%.o: ../proj/app/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"F:\TL_ZB_SDK\proj\common" -D__PROJECT_HA_LIGHT__=1 -DZB_PLATFORM_TELINK_TC32=1 -O2 -fpack-struct -fshort-enums -finline-small-functions -std=c99 -v -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



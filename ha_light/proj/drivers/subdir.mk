################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../proj/drivers/adc.c \
../proj/drivers/audio.c \
../proj/drivers/battery.c \
../proj/drivers/eth_hw.c \
../proj/drivers/ethernet.c \
../proj/drivers/flash.c \
../proj/drivers/i2c.c \
../proj/drivers/id.c \
../proj/drivers/image.c \
../proj/drivers/ip_adapt.c \
../proj/drivers/mic.c \
../proj/drivers/mouse.c \
../proj/drivers/ota_util.c \
../proj/drivers/pwm.c \
../proj/drivers/pwm_gpioSim.c \
../proj/drivers/sbc.c \
../proj/drivers/somatic_sensor.c \
../proj/drivers/spi.c \
../proj/drivers/syshw.c \
../proj/drivers/usb.c \
../proj/drivers/usbdesc.c \
../proj/drivers/usbhw.c 

OBJS += \
./proj/drivers/adc.o \
./proj/drivers/audio.o \
./proj/drivers/battery.o \
./proj/drivers/eth_hw.o \
./proj/drivers/ethernet.o \
./proj/drivers/flash.o \
./proj/drivers/i2c.o \
./proj/drivers/id.o \
./proj/drivers/image.o \
./proj/drivers/ip_adapt.o \
./proj/drivers/mic.o \
./proj/drivers/mouse.o \
./proj/drivers/ota_util.o \
./proj/drivers/pwm.o \
./proj/drivers/pwm_gpioSim.o \
./proj/drivers/sbc.o \
./proj/drivers/somatic_sensor.o \
./proj/drivers/spi.o \
./proj/drivers/syshw.o \
./proj/drivers/usb.o \
./proj/drivers/usbdesc.o \
./proj/drivers/usbhw.o 


# Each subdirectory must supply rules for building sources it contributes
proj/drivers/%.o: ../proj/drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"F:\TL_ZB_SDK\proj\common" -D__PROJECT_HA_LIGHT__=1 -DZB_PLATFORM_TELINK_TC32=1 -O2 -fpack-struct -fshort-enums -finline-small-functions -std=c99 -v -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



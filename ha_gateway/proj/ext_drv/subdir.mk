################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../proj/ext_drv/a350.c \
../proj/ext_drv/did.c \
../proj/ext_drv/flash_vendor.c \
../proj/ext_drv/gyro_l3g.c \
../proj/ext_drv/mma865x.c \
../proj/ext_drv/mouse_optical.c \
../proj/ext_drv/mpu6050.c \
../proj/ext_drv/ofn_a320.c \
../proj/ext_drv/ofn_vd5377.c 

OBJS += \
./proj/ext_drv/a350.o \
./proj/ext_drv/did.o \
./proj/ext_drv/flash_vendor.o \
./proj/ext_drv/gyro_l3g.o \
./proj/ext_drv/mma865x.o \
./proj/ext_drv/mouse_optical.o \
./proj/ext_drv/mpu6050.o \
./proj/ext_drv/ofn_a320.o \
./proj/ext_drv/ofn_vd5377.o 


# Each subdirectory must supply rules for building sources it contributes
proj/ext_drv/%.o: ../proj/ext_drv/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"C:\Documents and Settings\Administrator\×ÀÃæ\telink_zigbee_sdk\proj\common" -D__PROJECT_HA_GATEWAY__=1 -DZB_PLATFORM_TELINK_TC32=1 -O2 -fpack-struct -fshort-enums -finline-small-functions -std=c99 -v -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



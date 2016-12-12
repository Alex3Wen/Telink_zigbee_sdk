################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vendor/haApp/ha_light.c \
../vendor/haApp/light_hwControl.c \
../vendor/haApp/zb_appCb.c \
../vendor/haApp/zcl_appCb.c 

OBJS += \
./vendor/haApp/ha_light.o \
./vendor/haApp/light_hwControl.o \
./vendor/haApp/zb_appCb.o \
./vendor/haApp/zcl_appCb.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/haApp/%.o: ../vendor/haApp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"F:\TL_ZB_SDK\proj\common" -D__PROJECT_PHY_TEST__=1 -DZB_PLATFORM_TELINK_TC32=1 -O2 -fpack-struct -fshort-enums -finline-small-functions -std=c99 -v -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



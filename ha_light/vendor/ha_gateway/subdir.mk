################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vendor/ha_gateway/gwCmd.c \
../vendor/ha_gateway/ha_gateway.c \
../vendor/ha_gateway/zb_appCb.c \
../vendor/ha_gateway/zcl_appCb.c 

OBJS += \
./vendor/ha_gateway/gwCmd.o \
./vendor/ha_gateway/ha_gateway.o \
./vendor/ha_gateway/zb_appCb.o \
./vendor/ha_gateway/zcl_appCb.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/ha_gateway/%.o: ../vendor/ha_gateway/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"F:\TL_ZB_SDK\proj\common" -D__PROJECT_HA_LIGHT__=1 -DZB_PLATFORM_TELINK_TC32=1 -O2 -fpack-struct -fshort-enums -finline-small-functions -std=c99 -v -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



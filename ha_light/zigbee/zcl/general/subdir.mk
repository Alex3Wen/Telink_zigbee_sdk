################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../zigbee/zcl/general/zcl_identify_attr.c \
../zigbee/zcl/general/zcl_level_attr.c \
../zigbee/zcl/general/zcl_onoff_attr.c 

OBJS += \
./zigbee/zcl/general/zcl_identify_attr.o \
./zigbee/zcl/general/zcl_level_attr.o \
./zigbee/zcl/general/zcl_onoff_attr.o 


# Each subdirectory must supply rules for building sources it contributes
zigbee/zcl/general/%.o: ../zigbee/zcl/general/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"F:\TL_ZB_SDK\proj\common" -D__PROJECT_HA_LIGHT__=1 -DZB_PLATFORM_TELINK_TC32=1 -O2 -fpack-struct -fshort-enums -finline-small-functions -std=c99 -v -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



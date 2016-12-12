################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../zigbee/common/zb_globals.c 

OBJS += \
./zigbee/common/zb_globals.o 


# Each subdirectory must supply rules for building sources it contributes
zigbee/common/%.o: ../zigbee/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"C:\Documents and Settings\Administrator\×ÀÃæ\telink_zigbee_sdk\proj\common" -D__PROJECT_HA_GATEWAY__=1 -DZB_PLATFORM_TELINK_TC32=1 -O2 -fpack-struct -fshort-enums -finline-small-functions -std=c99 -v -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



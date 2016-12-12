################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vendor/common/led_cfg.c \
../vendor/common/led_cfg_module_5328.c \
../vendor/common/main.c 

OBJS += \
./vendor/common/led_cfg.o \
./vendor/common/led_cfg_module_5328.o \
./vendor/common/main.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/common/%.o: ../vendor/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"F:\TL_ZB_SDK\proj\common" -D__PROJECT_PHY_TEST__=1 -DZB_PLATFORM_TELINK_TC32=1 -O2 -fpack-struct -fshort-enums -finline-small-functions -std=c99 -v -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../proj/common/breakpoint.c \
../proj/common/bufm.c \
../proj/common/compatibility.c \
../proj/common/list.c \
../proj/common/log.c \
../proj/common/mempool.c \
../proj/common/mmem.c \
../proj/common/printf.c \
../proj/common/string.c \
../proj/common/utility.c 

OBJS += \
./proj/common/breakpoint.o \
./proj/common/bufm.o \
./proj/common/compatibility.o \
./proj/common/list.o \
./proj/common/log.o \
./proj/common/mempool.o \
./proj/common/mmem.o \
./proj/common/printf.o \
./proj/common/string.o \
./proj/common/utility.o 


# Each subdirectory must supply rules for building sources it contributes
proj/common/%.o: ../proj/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"F:\TL_ZB_SDK\proj\common" -D__PROJECT_PHY_TEST__=1 -DZB_PLATFORM_TELINK_TC32=1 -O2 -fpack-struct -fshort-enums -finline-small-functions -std=c99 -v -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



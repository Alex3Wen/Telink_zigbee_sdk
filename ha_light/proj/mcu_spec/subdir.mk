################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../proj/mcu_spec/cstartup_3520.S \
../proj/mcu_spec/cstartup_5320.S \
../proj/mcu_spec/cstartup_5328.S \
../proj/mcu_spec/cstartup_5328_ram.S \
../proj/mcu_spec/cstartup_5332.S 

OBJS += \
./proj/mcu_spec/cstartup_3520.o \
./proj/mcu_spec/cstartup_5320.o \
./proj/mcu_spec/cstartup_5328.o \
./proj/mcu_spec/cstartup_5328_ram.o \
./proj/mcu_spec/cstartup_5332.o 


# Each subdirectory must supply rules for building sources it contributes
proj/mcu_spec/%.o: ../proj/mcu_spec/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 CC/Assembler'
	tc32-elf-gcc -DMCU_CORE_5320 -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



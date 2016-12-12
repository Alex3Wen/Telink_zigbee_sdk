################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include zigbee/zcl/general/subdir.mk
-include zigbee/common/subdir.mk
-include vendor/phy_test/subdir.mk
-include vendor/ha_light/subdir.mk
-include vendor/ha_gateway/subdir.mk
-include vendor/common/subdir.mk
-include vendor/common/TH_api/subdir.mk
-include proj/zboss/zdo/subdir.mk
-include proj/zboss/zcl/subdir.mk
-include proj/zboss/zcl/security_safety/subdir.mk
-include proj/zboss/zcl/measument_sensing/subdir.mk
-include proj/zboss/zcl/general/subdir.mk
-include proj/zboss/zbapi/subdir.mk
-include proj/zboss/secur/subdir.mk
-include proj/zboss/osif/subdir.mk
-include proj/zboss/nwk/subdir.mk
-include proj/zboss/mac/subdir.mk
-include proj/zboss/ha/subdir.mk
-include proj/zboss/common/subdir.mk
-include proj/zboss/aps/subdir.mk
-include proj/rf/subdir.mk
-include proj/os/subdir.mk
-include proj/mcu_spec/subdir.mk
-include proj/mcu/subdir.mk
-include proj/ext_drv/subdir.mk
-include proj/drivers/subdir.mk
-include proj/common/subdir.mk
-include proj/app/subdir.mk
-include objects.mk

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LST += \
boot-.lst \

FLASH_IMAGE += \
boot.bin \

SIZEDUMMY += \
sizedummy \


# All Target
all: pre-build main-build

# Main-build Target
main-build: TL_SDK.elf secondary-outputs

# Tool invocations
TL_SDK.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: TC32 C Linker'
	tc32-elf-ld --gc-sections -L"F:\TL_ZB_SDK\proj_lib" -L"F:\TL_ZB_SDK\proj_lib\lib" -L"F:\TL_ZB_SDK\proj\lib" -L"F:\TL_ZB_SDK\rf\lib" -L"F:\TL_ZB_SDK\zigbee\lib" -T ../boot.link -o"TL_SDK.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

boot-.lst: TL_SDK.elf
	@echo 'Invoking: TC32 Create Extended Listing'
	tc32-elf-objdump -x -D -l -S TL_SDK.elf  >"boot-.lst"
	@echo 'Finished building: $@'
	@echo ' '

boot.bin: TL_SDK.elf
	@echo 'Create Flash image (binary format)'
	tc32-elf-objcopy -O binary TL_SDK.elf  "boot.bin"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: TL_SDK.elf
	@echo 'Invoking: Print Size'
	tc32-elf-size -t TL_SDK.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(FLASH_IMAGE)$(ELFS)$(LST)$(SIZEDUMMY) TL_SDK.elf
	-@echo ' '

pre-build:
	-../../tlsdk/getver.sh
	-@echo ' '

secondary-outputs: $(LST) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY: main-build pre-build

-include ../makefile.targets

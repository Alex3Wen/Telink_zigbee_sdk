
#pragma once

_attribute_flash_code_ void image_write(u32 srcAddr, u16 len, u8 *data);
_attribute_flash_code_ void image_init(u32 srcAddr, u8 sectors);
_attribute_flash_code_ void image_read(u32 srcAddr, u16 len, u8 *data);
_attribute_flash_code_ void image_copy(u32 srcAddr, u32 len);


#pragma once

  /* Set CTRL_REG1 (0x20)
   ====================================================================
   BIT  Symbol    Description                                   Default
   ---  ------    --------------------------------------------- -------
   7-6  DR1/0     Output data rate                                   00
   5-4  BW1/0     Bandwidth selection                                00
     3  PD        0 = Power-down mode, 1 = normal/sleep mode          0
     2  ZEN       Z-axis enable (0 = disabled, 1 = enabled)           1
     1  YEN       Y-axis enable (0 = disabled, 1 = enabled)           1
     0  XEN       X-axis enable (0 = disabled, 1 = enabled)           1 */

  /* Switch to normal mode and enable all three channels */
  /* ------------------------------------------------------------------ */

  /* Set CTRL_REG2 (0x21)
   ====================================================================
   BIT  Symbol    Description                                   Default
   ---  ------    --------------------------------------------- -------
   5-4  HPM1/0    High-pass filter mode selection                    00
   3-0  HPCF3..0  High-pass filter cutoff frequency selection      0000 */

  /* Nothing to do ... keep default values */
  /* ------------------------------------------------------------------ */

  /* Set CTRL_REG3 (0x22)
   ====================================================================
   BIT  Symbol    Description                                   Default
   ---  ------    --------------------------------------------- -------
     7  I1_Int1   Interrupt enable on INT1 (0=disable,1=enable)       0
     6  I1_Boot   Boot status on INT1 (0=disable,1=enable)            0
     5  H-Lactive Interrupt active config on INT1 (0=high,1=low)      0
     4  PP_OD     Push-Pull/Open-Drain (0=PP, 1=OD)                   0
     3  I2_DRDY   Data ready on DRDY/INT2 (0=disable,1=enable)        0
     2  I2_WTM    FIFO wtrmrk int on DRDY/INT2 (0=dsbl,1=enbl)        0
     1  I2_ORun   FIFO overrun int on DRDY/INT2 (0=dsbl,1=enbl)       0
     0  I2_Empty  FIFI empty int on DRDY/INT2 (0=dsbl,1=enbl)         0 */

  /* Nothing to do ... keep default values */
  /* ------------------------------------------------------------------ */

  /* Set CTRL_REG4 (0x23)
   ====================================================================
   BIT  Symbol    Description                                   Default
   ---  ------    --------------------------------------------- -------
     7  BDU       Block Data Update (0=continuous, 1=LSB/MSB)         0
     6  BLE       Big/Little-Endian (0=Data LSB, 1=Data MSB)          0
   5-4  FS1/0     Full scale selection                               00
                                  00 = 250 dps
                                  01 = 500 dps
                                  10 = 2000 dps
                                  11 = 2000 dps
     0  SIM       SPI Mode (0=4-wire, 1=3-wire)                       0 */

enum
{                                               // DEFAULT    TYPE
      GYRO_L3G_REG_WHO_AM_I            = 0x0F,   // 11010100   r
      GYRO_L3G_REG_CTRL_REG1           = 0x20,   // 00000111   rw
      GYRO_L3G_REG_CTRL_REG2           = 0x21,   // 00000000   rw
      GYRO_L3G_REG_CTRL_REG3           = 0x22,   // 00000000   rw
      GYRO_L3G_REG_CTRL_REG4           = 0x23,   // 00000000   rw
      GYRO_L3G_REG_CTRL_REG5           = 0x24,   // 00000000   rw
      GYRO_L3G_REG_REFERENCE           = 0x25,   // 00000000   rw
      GYRO_L3G_REG_OUT_TEMP            = 0x26,   //            r
      GYRO_L3G_REG_STATUS_REG          = 0x27,   //            r
      GYRO_L3G_REG_OUT_X_L             = 0x28,   //            r
      GYRO_L3G_REG_OUT_X_H             = 0x29,   //            r
      GYRO_L3G_REG_OUT_Y_L             = 0x2A,   //            r
      GYRO_L3G_REG_OUT_Y_H             = 0x2B,   //            r
      GYRO_L3G_REG_OUT_Z_L             = 0x2C,   //            r
      GYRO_L3G_REG_OUT_Z_H             = 0x2D,   //            r
      GYRO_L3G_REG_FIFO_CTRL_REG       = 0x2E,   // 00000000   rw
      GYRO_L3G_REG_FIFO_SRC_REG        = 0x2F,   //            r
      GYRO_L3G_REG_INT1_CFG            = 0x30,   // 00000000   rw
      GYRO_L3G_REG_INT1_SRC            = 0x31,   //            r
      GYRO_L3G_REG_TSH_XH              = 0x32,   // 00000000   rw
      GYRO_L3G_REG_TSH_XL              = 0x33,   // 00000000   rw
      GYRO_L3G_REG_TSH_YH              = 0x34,   // 00000000   rw
      GYRO_L3G_REG_TSH_YL              = 0x35,   // 00000000   rw
      GYRO_L3G_REG_TSH_ZH              = 0x36,   // 00000000   rw
      GYRO_L3G_REG_TSH_ZL              = 0x37,   // 00000000   rw
      GYRO_L3G_REG_INT1_DURATION       = 0x38    // 00000000   rw
};

#define I2C_ID_GYRO_L3G     0xd0

extern void  	gyro_init(void);
extern void 	gyro_powerup(int up);


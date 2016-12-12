
#pragma once

#define MMA865X_ADDRESS                (0x3a)        // 
#define MMA865X_POLL_TIMEOUT           (100)         // Maximum number of read attempts
#define MMA865X_ID                     (0b11010100)

#define I2C_ID_MMA865X					MMA865X_ADDRESS

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
      MMA865X_REGISTER_STATUS_REG          = 0x00,   //            r
      // 7     6     5     4     3     2      1     0

      MMA865X_REGISTER_OUT_X_H             = 0x01,   //            r
      MMA865X_REGISTER_OUT_X_L             = 0x02,   //            r
      MMA865X_REGISTER_OUT_Y_H             = 0x03,   //            r
      MMA865X_REGISTER_OUT_Y_L             = 0x04,   //            r
      MMA865X_REGISTER_OUT_Z_H             = 0x05,   //            r
      MMA865X_REGISTER_OUT_Z_L             = 0x06,   //            r

      MMA865X_REGISTER_FF_MT_CFG           = 0x15,   //  78: motion detection with debounce 
      // 7     6     5     4     3     2      1     0
      // ele   oae   z     y     x     -      -     -

      MMA865X_REGISTER_FF_MT_SRC           = 0x16,   //  78: wakeup source
      // 7     6     5     4     3     2      1     0
      // ele   oae   z     y     x     -      -     -

      MMA865X_REGISTER_FF_MT_THR           = 0x17,   //  40: threshold 4g
      // 7     6     5     4     3     2      1     0
      // mode  cnt

      MMA865X_REGISTER_FF_MT_DEB           = 0x18,   //  04: debounce counter
      // 7     6     5     4     3     2      1     0
      // counter

      MMA865X_REGISTER_TRAN_CFG		   = 0x1d,  //   0e: enable xyz
      // 7     6     5     4     3     2      1     0
      // -     -     -     ELE   Z     Y      X    HPP_BYP

      MMA865X_REGISTER_TRAN_SRC		   = 0x1e,  //   RO: enable xyz interrupt
      // 7     6     5     4     3     2      1     0
      // -     EA    ZT    ZP    YT    YP     XT    XP

      MMA865X_REGISTER_TRAN_THR           = 0x1f,   //  40: threshold 4g
      // 7     6     5     4     3     2      1     0
      // 

      MMA865X_REGISTER_TRAN_DEB           = 0x20,   //  04: debounce counter
      // 7     6     5     4     3     2      1     0
      // counter

      MMA865X_REGISTER_data_cfg            = 0x0e,   //   rw
      // 7     6     5     4     3     2      1     0
      //       0     0     hpfo  0     0      fs1   fs0
      //	[fs1,fs0]: 00 2g; 01 4g; 10; 8g
      
      MMA865X_REGISTER_CTRL_REG1           = 0x2a,   //   rw: 58 standby; 59:active
      // 7     6     5     4     3     2      1     0
      // aslp_rate   dr2  dr1   dr0    lnoise fread active

      MMA865X_REGISTER_CTRL_REG2           = 0x2b,   //   rw: 1c
      // 7     6     5     4     3     2      1     0
      // st    rst   0     smods[1:0]  slpe   mods[1:0]
      // 00 normal; 01 low noise low power; 10 high resuluion; 11 low power
      
      MMA865X_REGISTER_CTRL_REG3           = 0x2c,   //   rw
      // 7     6     5     4     3     2      1     0
      // fifog wtran wori  wpls  wffmt 0      ipol  od
      
      MMA865X_REGISTER_CTRL_REG4           = 0x2d,   //   rw	interrupt enable
      // 7     6     5     4     3     2      1     0
      // aslp  fifo  trans ori   pls   ffmt   0     drdy 
      
      MMA865X_REGISTER_CTRL_REG5           = 0x2e,   //   rw  interrupt config
      // 7     6     5     4     3     2      1     0
      // aslp  fifo  trans ori   pls   ffmt   0     drdy 

      MMA865X_REGISTER_WHO_AM_I            = 0x0d   //
};

#define			MMA865X_SLEEP_MODE			1
#define			MMA865X_ACTIVE_MODE			0


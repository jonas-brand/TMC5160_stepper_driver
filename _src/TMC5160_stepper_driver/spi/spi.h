#ifndef __TMC5160_SPI_H__
#define __TMC5160_SPI_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <utils/periferals.h>
#include <TMC5160_stepper_driver/drv/drv.h>

//enum for representing driver register
typedef enum
{
    GCONF           = 0x00,
    GSTAT           = 0x01,
    IFCNT           = 0x02,
    SLAVECONF       = 0x03,
    IOIN            = 0x04,
    OUTPUT          = 0x04,
    X_COMPARE       = 0x05,
    OTP_PROG        = 0x06,
    OTP_READ        = 0x07,
    FACTORY_CONF    = 0x08,
    SHORT_CONF      = 0x09,
    DRV_CONF        = 0x0A,
    GLOBALSCALAR    = 0x0B,
    OFFSET_READ     = 0x0C,
    IHOLD_IRUN      = 0x10,
    TPOWERDOWN      = 0x11,
    TSTEP           = 0x12,
    TPWM_THRS       = 0x13,
    TCOOL_THRS      = 0x14,
    THIGH           = 0x15,
    RAMPMODE        = 0x20,
    XACTUAL         = 0x21,
    VACTUAL         = 0x22,
    VSTART          = 0x23,
    A1              = 0x24,
    V1              = 0x25,
    AMAX            = 0x26,
    VMAX            = 0x27,
    DMAX            = 0x28,
    D1              = 0x2A,
    VSTOP           = 0x2B,
    TZEROWAIT       = 0x2C,
    XTARGET         = 0x2D,
    VDCMIN          = 0x33,
    SW_MODE         = 0x34,
    RAMP_STAT       = 0x35,
    XLACH           = 0x36,
    ENCMODE         = 0x38,
    XENC            = 0x39,
    ENC_CONST       = 0x3A,
    ENC_STATUS      = 0x3B,
    ENC_LACH        = 0x3C,
    ENC_DEVIATION   = 0x3D,
    MSLUT0          = 0x60,
    MSLUT1          = 0x61,
    MSLUT2          = 0x62,
    MSLUT3          = 0x63,
    MSLUT4          = 0x64,
    MSLUT5          = 0x65,
    MSLUT6          = 0x66,
    MSLUT7          = 0x67,
    MSLUTSEL        = 0x68,
    MSLUTSTART      = 0x69,
    MSCNT           = 0x6A,
    MSCURACT        = 0x6B,
    CHOPCONF        = 0x6C,
    COOLCONF        = 0x6D,
    DCCTRL          = 0x6E,
    DRV_STATUS      = 0x6F,
    PWMCONF         = 0x70,
    PWM_SCALE       = 0x71,
    PWM_AUTO        = 0x72,
    LOST_STEPS      = 0x73
}drv_reg_t;

//type for storing spi status
typedef uint8_t spi_stat_t;

//function for setting up spi modul
void spi_init(gpio_ptr_t _cs_reg);

//send 40-bit data frame consisting of 8-bit adress and 32-bit data, returns spi status byte
spi_stat_t spi_send(drv_idx_t drv, drv_reg_t reg, uint32_t data);

//receive 32-bit data
uint32_t spi_receive(drv_idx_t drv, drv_reg_t reg);

#endif //! __TMC5160_SPI_H__
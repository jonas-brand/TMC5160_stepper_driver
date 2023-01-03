#ifndef __TMC5160_DRV_H__
#define __TMC5160_DRV_H__

#include <stdbool.h>
#include <utils/periferals.h>

//enum for representing driver index
typedef enum
{
    DRIVER0 = _BV(PA0),
    DRIVER1 = _BV(PA1),
    DRIVER2 = _BV(PA2),
    DRIVER3 = _BV(PA3),
    DRIVER4 = _BV(PA4),
    DRIVER5 = _BV(PA5),
    DRIVER6 = _BV(PA6),
    DRIVER7 = _BV(PA7)
}drv_idx_t;

//enum for representing microstep resolution
typedef enum
{
    MICROSTEP_256 = 0,
    MICROSTEP_128 = 1,
    MICROSTEP_64 =  2,
    MICROSTEP_32 =  3,
    MICROSTEP_16 =  4,
    MICROSTEP_8 =   5,
    MICROSTEP_4 =   6,
    MICROSTEP_2 =   7,
    FULLSTEP =      8
}drv_res_t;

//function for setting ports
void drv_set_ports(gpio_ptr_t _cs_reg, gpio_ptr_t _dir_reg, gpio_ptr_t _stp_reg);

//function for setting up driver
bool drv_init(drv_idx_t self, float i_max/*mA*/, drv_res_t res);

//function for moving motor one step forwards (dir == LOW)
void drv_stp_fw(drv_idx_t self);

//function for moving motor one step backwards (dir == HIGH)
void drv_stp_bw(drv_idx_t self);

#endif //! __TMC5160_DRV_H__
#ifndef __TMC5160_DRV_H__
#define __TMC5160_DRV_H__

#include "utils/periferals.h"
#include "TMC5160_stepper_driver/spi/spi.h"

//struct for stepper driver
typedef struct
{
    drv_idx_t idx;
}stp_drv_t;

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
}stp_drv_res_t;

//function for setting up driver
void stp_drv_init(stp_drv_t* self, drv_idx_t idx, float i_max/*mA*/, stp_drv_res_t res);

#endif //! __TMC5160_DRV_H__
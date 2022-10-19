#ifndef __TMC5160_DRV_H__
#define __TMC5160_DRV_H__

#include "utils/periferals.h"
#include "TMC5160_stepper_driver/spi/spi.h"

//struct for stepper driver
typedef struct
{
    drv_idx_t idx;
}stp_drv_t;

//function for setting up driver
bool stp_drv_init(stp_drv_t* self, drv_idx_t idx);

#endif //! __TMC5160_DRV_H__
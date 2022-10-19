#ifndef __TMC5160_DRV_H__
#define __TMC5160_DRV_H__

#include "utils/periferals.h"
#include "TMC5160_stepper_driver/spi/spi.h"

//struct for stepper driver
typedef struct
{
    drv_idx_t idx;
}stp_drv_t;

#endif //! __TMC5160_DRV_H__
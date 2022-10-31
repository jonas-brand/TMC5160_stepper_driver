#include "drv_const.h"
#include <util/delay.h>
#include <utils/print.h>

#define US_PER_S 1000000

static void wait(uint16_t t/*us*/)
{
    while(t--)
        _delay_us(1);
}

static uint16_t next_delay(uint32_t dist, uint32_t pos, uint16_t v, uint16_t a)
{
    
}

void stp_drv_mov(drv_idx_t self, int32_t dist/*steps*/, uint16_t v/*steps/s*/, uint16_t a/*steps/s^2*/)
{
    if(dist < 0)
        DIR_REG->portx |= self;
    else
        DIR_REG->portx &= ~self;

    for(uint32_t pos = 0; ; pos++)
    {
        //pulse the step pin
        STP_REG->portx |= self;
        STP_REG->portx &= ~self;

        //break out of the loop if movement is finished
        //this avoids a delay behind the last step
        if(pos + 1 >= abs(dist)) break;
        _delay_ms(1);
    }
}
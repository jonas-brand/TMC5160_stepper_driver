#include "drv_const.h"
#include <util/delay.h>

#define WAIT_PER_S 100000

//function for getting dynamic delay
static void wait(uint16_t t/*100us*/)
{
    while(t--)
        _delay_us(1000000 / WAIT_PER_S);
}

//function for calculating next delay of movement according to position maximum velosity and acceleration 
static uint16_t next_delay(uint32_t dist, uint32_t pos, uint32_t v, uint32_t a)
{
    uint32_t x = pos < (dist / 2) ? pos : dist / 2 - (pos - dist / 2);
    return fmax(fmax(WAIT_PER_S / sqrt(2.0f * (float)a * (float)x), WAIT_PER_S / v), 1);    //output ist immer > 0
}

void stp_drv_mov(drv_idx_t self, int32_t dist/*steps*/, uint32_t v/*steps/s*/, uint32_t a/*steps/s^2*/)
{
    if(dist < 0)
        DIR_REG->portx |= self;
    else
        DIR_REG->portx &= ~self;

    for(uint32_t pos = 1; ; pos++)
    {
        //pulse the step pin
        STP_REG->portx |= self;
        STP_REG->portx &= ~self;

        //break out of the loop if movement is finished
        //this avoids a delay behind the last step
        if(pos == abs(dist)) break;
        wait(next_delay(abs(dist), pos, v, a));
    }
}
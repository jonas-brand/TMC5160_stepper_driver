#include <TMC5160_stepper_driver/drv/drv.h>
#include <util/delay.h>

int main(void)
{
    stp_drv_init(DRIVER0, 100, MICROSTEP_4);

    stp_drv_mov(DRIVER0, -800, 0, 0);

    //end of the programm
    for(;;);
}
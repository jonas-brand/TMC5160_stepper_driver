#include <TMC5160_stepper_driver/drv/drv.h>
#include <util/delay.h>
#include <utils/print.h>

int main(void)
{
    drv_set_ports(GPIO_L, GPIO_F, GPIO_K);

    drv_init(DRIVER0, 1000, MICROSTEP_8);

    for(;;)
    {
        drv_stp_fw(DRIVER0);
        _delay_ms(10);
    }

    //end of the programm
    for(;;);
}
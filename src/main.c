#include <TMC5160_stepper_driver/spi/spi.h>
#include <utils/print.h>

int main(void)
{
    spi_init();

    spi_send(DRIVER0, CHOPCONF,     0x000100C3);
    spi_send(DRIVER0, IHOLD_RUN,    0x00061F0A);
    spi_send(DRIVER0, TPOWERDOWN,   0x0000000A);
    spi_send(DRIVER0, GCONF,        0x00000004);
    spi_send(DRIVER0, TPWM_THRS,    0x000001F4);

    //end of the programm
    for(;;);
}
#include "drv.h"
#include <TMC5160_stepper_driver/spi/spi.h>
#include <math.h>

//chip select, step and direction ports
gpio_ptr_t dir_reg = NULL, stp_reg = NULL;

//values needed to calculate global scalar
#define V_FS 325.0f /*mV*/
#define R_S 75.0f /*mOhm*/

//configuration for chopconf register
#define TOFF 3      //controlls decay time
#define HSTRT 4     //controlls start of chopper hysteresis
#define HEND 1      //controlls end of chopper hysteresis
#define INTPOL 28   //flag for microstep interpolation
#define MRES 24     //position of microstep resolution bits
#define CHOPCONF_CONFIG TOFF | (HSTRT<<4) | (HEND<<7) | _BV(INTPOL)

//configuration for IHOLD_IRUN register
#define IRUN 31                         //scaler for running current (31 = max)
#define IHOLD (uint32_t)(IRUN * 0.7)    //scaler for holding current
#define IHOLDDELAY 6                    //powerdown duration
#define IHOLD_IRUN_CONFIG IHOLD | (IRUN<<8) | ((uint32_t)IHOLDDELAY<<16)

//configuration for TPOWERDOWN register
#define TPOWERDOWN_CONFIG 10    //delay before powerdown

//function for getting max of two uint8_t's
static uint8_t u8_max(uint8_t a, uint8_t b)
{
    return a > b ? a : b;
}

//function for calculating global scalar
static uint8_t get_global_scalar(float i_max/*mA*/)
{
    /*
                   i_max * 256 * R_SENS * sqrt(2)
    GLOBALSCALAR = ------------------------------
                                V_FS
    */
    return  u8_max(32, (i_max / 1000.0f) * 256 * R_S * sqrt(2) / V_FS);
}

//function for setting ports
void drv_set_ports(gpio_ptr_t _cs_reg, gpio_ptr_t _dir_reg, gpio_ptr_t _stp_reg)
{
    //initialise spi
    spi_init(_cs_reg);

    dir_reg = _dir_reg;
    stp_reg = _stp_reg;
}

//function for setting up driver
bool drv_init(drv_idx_t self, float i_max/*mA*/, drv_res_t res)
{
    //check if variables have been initialised
    if(dir_reg == NULL) return false;
    if(stp_reg == NULL) return false;

    //set step/direction ports as output
    dir_reg->ddrx |= self;
    stp_reg->ddrx |= self;

    //set scalar according to supplied max current
    spi_send(self, GLOBALSCALAR, get_global_scalar(i_max));

    //configure CHOPCONF for SpreadCycle
    spi_send(self, CHOPCONF, CHOPCONF_CONFIG | ((uint32_t)res<<MRES));

    //configure IHOLD_IRUN
    spi_send(self, IHOLD_IRUN, IHOLD_IRUN_CONFIG);

    //configure TPOWERDOWN
    spi_send(self, TPOWERDOWN, TPOWERDOWN_CONFIG);

    return true;
}

//function for moving motor one step forwards (dir == LOW)
void drv_stp_fw(drv_idx_t self)
{
    //write direction pin low
    dir_reg->portx &= ~self;

    //make shure pin starts of as low
    stp_reg->portx &= ~self;

    //output edge on step pin
    stp_reg->portx |= self;
}

//function for moving motor one step backwards (dir == HIGH)
void drv_stp_bw(drv_idx_t self)
{
    //write direction pin high
    dir_reg->portx |= self;

    //make shure pin starts of as low
    stp_reg->portx &= ~self;

    //output edge on step pin
    stp_reg->portx |= self;
}
#include "drv_const.h"

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

//function for setting up driver
void stp_drv_init(drv_idx_t self, drv_idx_t idx, float i_max/*mA*/, stp_drv_res_t res)
{
    //initialise self
    self = idx;

    //set step/direction ports as output
    DIR_REG->ddrx |= self;
    STP_REG->ddrx |= self;

    //initialise spi
    spi_init();

    //set scalar according to supplied max current
    spi_send(self, GLOBALSCALAR, get_global_scalar(i_max));

    //configure CHOPCONF for SpreadCycle
    spi_send(self, CHOPCONF, CHOPCONF_CONFIG | ((uint32_t)res<<MRES));

    //configure IHOLD_IRUN
    spi_send(self, IHOLD_IRUN, IHOLD_IRUN_CONFIG);

    //configure TPOWERDOWN
    spi_send(self, TPOWERDOWN, TPOWERDOWN_CONFIG);
}
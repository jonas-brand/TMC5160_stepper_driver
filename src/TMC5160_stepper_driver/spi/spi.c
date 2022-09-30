#include "spi.h"

//SPI pins
#define DDR_SPI DDRB
#define SCK PB1
#define MOSI PB2
#define MISO PB3

//function for setting up spi modul
bool spi_init(bitorder_t bitorder, spi_mode_t mode, spi_freq_t freq_divdr)
{
    //write the power reduction spi bit to 0 to enable spi operation
    PRR0 &= _BV(PRSPI);

    //set MOSI and SCK as output, MISO as input
    DDR_SPI |= _BV(MOSI) | _BV(SCK);
    DDR_SPI &= _BV(MISO);

    //configure spi control register
    SPCR = bitorder | mode | freq_divdr;

    //set mode to master and enable spi
    SPCR = _BV(MSTR) | _BV(SPE);
}
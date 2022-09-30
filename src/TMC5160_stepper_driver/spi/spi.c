#include "spi.h"

//SPI pins
#define DDR_SPI DDRB
#define SCK PB1
#define MOSI PB2
#define MISO PB3

//function for setting up spi modul
void spi_init()
{
    //write the power reduction spi bit to 0 to enable spi operation
    PRR0 &= _BV(PRSPI);

    //set MOSI and SCK as output, MISO as input
    DDR_SPI |= _BV(MOSI) | _BV(SCK);
    DDR_SPI &= _BV(MISO);

    //configure spi control register
    //master operation, spi mode 3, SCK frequency = F_CPU / 16
    SPCR = _BV(MSTR) | _BV(CPOL) | _BV(CPHA) | _BV(SPR0);

    //enable spi
    SPCR = _BV(SPE);
}

//function for transmitting and receiving data
uint8_t spi_com(uint8_t data_out)
{
    //transmit data
    SPDR = data_out;

    //wait until transmission is finished
    while(SPSR & _BV(SPIF));
    
    //return received data
    return SPDR;
}
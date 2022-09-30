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

//send 40-bit data frame consisting of 8-bit adress and 32-bit data, returns spi status byte
spi_stat_t spi_send(uint8_t addr, uint32_t data)
{
    //transmit adress
    spi_com(addr);

    //transmit data
    spi_com((uint8_t)(data >> 24));
    spi_com((uint8_t)(data >> 16));
    spi_com((uint8_t)(data >> 8));
    return spi_com((uint8_t)(data));
}

//receive 32-bit data
uint32_t spi_receive()
{
    //read and discard status byte
    spi_com(0);

    //read data
    uint32_t data;
    data = (uint32_t)spi_com(0) << 24;
    data |= (uint32_t)spi_com(0) << 16;
    data |= (uint32_t)spi_com(0) << 8;
    return data |= (uint32_t)spi_com(0);
}
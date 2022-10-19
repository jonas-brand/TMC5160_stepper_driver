#include "spi.h"

//SPI pins
#define DDR_SPI DDRB
#define SCK PB1
#define MOSI PB2
#define MISO PB3

//chip select register
#define CS_REG GPIO_A

//function for setting up spi modul
void spi_init()
{
    //set chip select port as output and set all outputs to high
    CS_REG->ddrx = 0xFF;
    CS_REG->portx = 0xFF;

    //write the power reduction spi bit to 0 to enable spi operation
    PRR0 &= ~_BV(PRSPI);

    //set MOSI and SCK as output, MISO as input
    DDR_SPI |= _BV(MOSI) | _BV(SCK);
    DDR_SPI &= ~_BV(MISO);

    //configure spi control register
    //master operation, spi mode 3, SCK frequency = F_CPU / 16
    SPCR = _BV(MSTR) | _BV(CPOL) | _BV(CPHA) | _BV(SPR0);

    //enable spi
    SPCR |= _BV(SPE);
}

//function for transmitting and receiving data
static uint8_t spi_com(uint8_t data_out)
{
    //transmit data
    SPDR = data_out;

    //wait until transmission is finished
    while(!(SPSR & _BV(SPIF)));
    
    //return received data
    return SPDR;
}

//send 40-bit data frame consisting of 8-bit adress and 32-bit data, returns spi status byte
spi_stat_t spi_send(drv_idx_t drv, drv_reg_t reg, uint32_t data)
{
    //start transaction
    CS_REG->portx &= ~drv;

    //transmit adress with write bit set to one
    spi_com(reg | 0b10000000);

    //transmit data
    spi_stat_t stat = spi_com((uint8_t)(data >> 24));
    spi_com((uint8_t)(data >> 16));
    spi_com((uint8_t)(data >> 8));
    spi_com((uint8_t)(data));

    //stop transaction
    CS_REG->portx = 0xFF;

    //return status byte
    return stat;
}

//receive 32-bit data
uint32_t spi_receive(drv_idx_t drv, drv_reg_t reg)
{
    //start transaction
    CS_REG->portx &= ~drv;

    //transmit adress
    spi_com(reg);

    //transmit dummy bytes
    for(uint8_t i = 0; i < 4; i++)
        spi_com(0);

    //stop transaction
    CS_REG->portx = 0xFF;

    //start transaction
    CS_REG->portx &= ~drv;

    //read and discard status byte
    spi_com(0);

    //read data
    uint32_t data;
    data = (uint32_t)spi_com(0) << 24;
    data |= (uint32_t)spi_com(0) << 16;
    data |= (uint32_t)spi_com(0) << 8;
    data |= (uint32_t)spi_com(0);

    //stop transaction
    CS_REG->portx = 0xFF;

    //return read data
    return data;
}
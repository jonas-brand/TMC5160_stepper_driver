#ifndef __TMC5160_SPI_H__
#define __TMC5160_SPI_H__

#include <stdbool.h>
#include <stdint.h>
#include <utils/periferals.h>

//enum for describing bit order
typedef enum
{
    MSB_FIRST = 0,
    LSB_FIRST = _BV(DORD)
}bitorder_t;

//enum for describing spi mode
typedef enum
{
    SPI_MODE_0 = 0,
    SPI_MODE_1 = _BV(CPHA),
    SPI_MODE_2 = _BV(CPOL),
    SPI_MODE_3 = _BV(CPOL) | _BV(CPHA)
}spi_mode_t;

//enum for describing clock rate devider
typedef enum
{
    SPI_FREQ_4 = 0,
    SPI_FREQ_16 = _BV(SPR0),
    SPI_FREQ_64 = _BV(SPR1),
    SPI_FREQ_128 = _BV(SPR0) | _BV(SPR1)
}spi_freq_t;

//function for setting up spi modul
bool spi_init(bitorder_t bitorder, spi_mode_t mode, spi_freq_t freq_divdr);

#endif //! __TMC5160_SPI_H__
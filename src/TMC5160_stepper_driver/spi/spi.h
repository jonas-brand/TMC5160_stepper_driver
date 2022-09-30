#ifndef __TMC5160_SPI_H__
#define __TMC5160_SPI_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <utils/periferals.h>

//type for storing spi status
typedef uint8_t spi_stat_t;

//function for setting up spi modul
void spi_init();

//send 40-bit data frame consisting of 8-bit adress and 32-bit data, returns spi status byte
spi_stat_t spi_send(uint8_t addr, uint32_t data);

//receive 32-bit data
uint32_t spi_receive();

#endif //! __TMC5160_SPI_H__
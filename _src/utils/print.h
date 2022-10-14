#ifndef __PRINT_H__
#define __PRINT_H__

#include "periferals.h"
#include <stdarg.h>
#include <stddef.h>

//initialiser function
void print_init(usart_ptr_t port, uint16_t baud_rate);

//formated output
uint16_t uprintf(const char* fmt, ...);

#endif //! __PRINT_H__
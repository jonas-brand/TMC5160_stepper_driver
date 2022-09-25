#include "print.h"
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

static usart_ptr_t _port;

static void _uputchar(char c)
{
    while(! (_port->ucsrxa & _BV(UDRE0)));   //wait for preceeding transmisson to finnish
    _port->udrx = c;  //write data
}

static void _unputstr(size_t n, const char* s)
{
    for(size_t i = 0; i < n; i++)
    {
        if(s[i] == '\0') return;
        _uputchar(s[i]);
    }
}

#define PRINT_BUFFER_SIZE 50

//formated output
static uint16_t _vunprintf(const char* fmt, va_list args)
{
    static char buffer[PRINT_BUFFER_SIZE];

    uint16_t out = vsnprintf(buffer, PRINT_BUFFER_SIZE, fmt, args);
    _unputstr(PRINT_BUFFER_SIZE, buffer);

    return out;
}

//initialiser function
void print_init(usart_ptr_t port, uint16_t baud_rate)
{
    _port = port;

    cli();  //disable interrupts

    //set control registers
    port->ucsrxb = _BV(UCSZ00) | _BV(UCSZ01) | _BV(TXEN0);    //char size 8, transmitter enable

    //calculate baud rate
    uint16_t ubrrx = F_CPU / 16 / baud_rate - 1;

    //move ubbrx into registers
    port->ubrrxh = (uint8_t)(ubrrx >> 8);
    port->ubrrxl = (uint8_t)ubrrx;

    sei(); //enable interrupts
}

uint16_t uprintf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    _vunprintf(fmt, args);
    va_end(args);
}
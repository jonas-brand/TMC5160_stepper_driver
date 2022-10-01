#ifndef __PERIFERALS_H__
#define __PERIFERALS_H__

#ifndef __AVR_ATmega2560__
#define __AVR_ATmega2560__
#endif //! __AVR_ATmega2560__

#include <stdint.h>
#include <avr/io.h>

//register types
typedef volatile uint8_t reg8_t;
typedef volatile uint16_t reg16_t;

//==================================================================================GPIO

//struct for gpio
typedef struct
{
    reg8_t pinx;   //input
    reg8_t ddrx;   //data direction
    reg8_t portx;  //port
}* gpio_ptr_t;

#define GPIO_A ((gpio_ptr_t)&PINA)
#define GPIO_B ((gpio_ptr_t)&PINB)
#define GPIO_C ((gpio_ptr_t)&PINC)
#define GPIO_D ((gpio_ptr_t)&PIND)
#define GPIO_E ((gpio_ptr_t)&PINE)
#define GPIO_F ((gpio_ptr_t)&PINF)
#define GPIO_G ((gpio_ptr_t)&PING)
#define GPIO_H ((gpio_ptr_t)&PINH)
#define GPIO_J ((gpio_ptr_t)&PINJ)
#define GPIO_K ((gpio_ptr_t)&PINK)
#define GPIO_L ((gpio_ptr_t)&PINL)

//==================================================================================timers

//struct for 8-bit timer
typedef struct
{
    reg8_t tccrna;  //timer control register a to b
    reg8_t tccrnb;
    reg8_t tcntn;   //counter
    reg8_t ocrna;   //output compare register a to b
    reg8_t ocrnb;
}* t8_ptr_t;

//struct for 16-bit timer
typedef struct
{
    reg8_t tccrna;      //timer control register a to c
    reg8_t tccrnb;
    reg8_t tccrnc;
    const uint8_t _;    //reserve
    reg16_t tcntn;      //counter
    reg16_t icrn;       //input capture register
    reg16_t crna;       //output register a to c
    reg16_t ocrnb;
    reg16_t ocrnc;
}* t16_ptr_t;

#define TIMER_0 (t8_ptr_t)&TCCR0A
#define TIMER_1 (t16_ptr_t)&TCCR1A
#define TIMER_2 (t8_ptr_t)&TCCR2A
#define TIMER_3 (t16_ptr_t)&TCCR3A
#define TIMER_4 (t16_ptr_t)&TCCR4A
#define TIMER_5 (t16_ptr_t)&TCCR5A

//==================================================================================USART

//struct for usart port
typedef struct
{
    reg8_t ucsrxa;      //config byte a to c
    reg8_t ucsrxb;
    reg8_t ucsrxc;
    const uint8_t _;    //reserve
    reg8_t ubrrxl;      //baud rate low byte
    reg8_t ubrrxh;      //baud rate high byte
    reg8_t udrx;        //data
}* usart_ptr_t;

#define USART_0 (usart_ptr_t)&UCSR0A
#define USART_1 (usart_ptr_t)&UCSR1A
#define USART_2 (usart_ptr_t)&UCSR2A
#define USART_3 (usart_ptr_t)&UCSR3A

#endif //! __PERIFERALS_H__
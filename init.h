/* 
 * Name : Rehan Shakoor
 * Date : 07/02/2025
 * Description : LED pattern using switch, timer and sleep mode
 * File  : init.h
 * 
 */

#ifndef INIT_H
#define INIT_H

//include required headers
#include <xc.h>
#include <stdint.h>

//define BITs macros
#define BIT0 (0x01)
#define BIT1 (0x02)
#define BIT2 (0x04)
#define BIT3 (0x08)
#define BIT4 (0x10)
#define BIT5 (0x20)
#define BIT6 (0x40)
#define BIT7 (0x80)

//define switch port
#define SW_DDR TRISB
#define SW_REG PORTB
//define switch pin
#define SW_PIN BIT0

//PORTD LEDs are used
#define LED_DDR TRISD
#define LED_REG PORTD
//define LED pin
#define LED_PIN BIT0


//define switch debounce in ms
#define SW_DELAY 10
//define system clock frequency
#define _XTAL_FREQ 20000000

//function declaration to initialize led and switch
void led_sw_init(void);
//function declaration of TIMER1 initialization
void timer1_init(void);

#endif


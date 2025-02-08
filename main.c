/* 
 * Name : Rehan Shakoor
 * Date : 07/02/2025
 * Description : LED pattern using switch, timer and sleep mode
 * File  : main.c
 * 
 */

//include required headers
#include "init.h"

//disable watchdog timer
#pragma config WDTE = OFF
//HS oscillator is used (20 MHz)
#pragma config FOSC = HS 

//declare extern variables
extern int8_t mode;
extern uint16_t timer1_overflow_threshold;

void main(void) 
{   
    //call function to initialize led and switch
    led_sw_init();  
    //call TIMER1 initialization function
    timer1_init();
       
    //infinite loop
    while(1)
    {
        //switch case according to mode
        switch(mode)
        {
            //go to SLEEP and turn of LED
            case 0:
                //clear PEIE (bit6), to disable peripheral interrupt
                //this will disable timer interrupt, before going to 
                //sleep (no wakeup from timer)
                INTCON &= ~(BIT6);
                
                //turn LED off
                LED_DDR &= ~(LED_PIN);
                //goto sleep
                SLEEP();
                //after wakeup NOP is required as per data-sheet
                __asm__ volatile ("nop");
            
                //set PEIE (bit6), to enable peripheral interrupt
                //this will enable timer interrupt after wakeup
                INTCON |= BIT6;
                break;
                
            //LED blinks at 0.5 Hz
            case 1:
                //100 overflows is 1 sec
                timer1_overflow_threshold = 100;
                break;
                    
            //LED blinks at 1 Hz
            case 2:
                //50 overflows is 500 ms
                timer1_overflow_threshold = 50;
                break;
                    
            //LED blinks at 2 Hz
            case 3:
                //25 overflows is 250 ms
                timer1_overflow_threshold = 25;
                break;
        }
    }
    
    return;
}
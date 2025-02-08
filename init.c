/* 
 * Name : Rehan Shakoor
 * Date : 07/02/2025
 * Description : LED pattern using switch, timer and sleep mode
 * File  : init.c
 * 
 */


//include required headers
#include "init.h"

//variables to calculate timer1 overflow count
uint16_t timer1_overflow_count = 0;
//variables to calculate timer1 overflow threshold
uint16_t timer1_overflow_threshold = 0;
//variable to store current mode
int8_t mode = -1;

//function definition to initialize led and switch
void led_sw_init(void)
{
    //set LED port as output
    LED_DDR = 0x00;
    //turn off LED port
    LED_REG = 0x00;
    
    //clear INTEDG (bit6), to enable interrupt on falling edge
    OPTION_REG &= ~(BIT6); 
    //set INTE (bit4), to enable INT external interrupt
    INTCON |= BIT4;
    //clear INTF (bit1), to clear interrupt flag
    INTCON &= ~(BIT1);
    //initialize swith pin as input
    SW_DDR |= SW_PIN;
    
    //give delay so that value on input pin is stable
    __delay_ms(SW_DELAY);
}

//function definition of TIMER1 initialization
void timer1_init(void)
{
    //set TMR1ON (bit0), to enable Timer1
    T1CON |= BIT0;
    //clear TMR1CS (bit1), to use CLK0 clock source for Timer1
    T1CON &= ~BIT1;
    //clear bit(5:4) (11), 1:1 pre-scalar is used 
    T1CON &= ~(BIT5 | BIT4);
    //set TMR1 to 15536, one overflow takes 10 MS
    TMR1 = 15536;
    
    //set GIE (bit7), to enable global interrupt
    INTCON |= BIT7;
    //set PEIE (bit6), to enable peripheral interrupt
    INTCON |= BIT6;
    //set TMR1IE (bit0), to enable Timer1 interrupt
    PIE1 |= BIT0;
    //clear TMR1IF (bit0), to clear Timer1 interrupt flag
    PIR1 &= ~BIT0;
}

//define interrupt service routine (ISR)
void __interrupt() ISR(void)
{
    //check INTF (bit1), to check INT interrupt
    if(INTCON & BIT1)
    {
        //delay for switch press de-bounce
        __delay_ms(SW_DELAY);
        //wait till switch is pressed (pull up configuration)
        while(!(SW_REG & SW_PIN));
        //delay for switch release de-bounce
        __delay_ms(SW_DELAY);
               
        //increment mode (repeat after mode 3)
        mode = mode == 3 ? 0 : mode + 1;   
        
        //restart timer
        //set TMR1 to 15536, one overflow takes 10 MS
        TMR1 = 15536;
        timer1_overflow_count = 0;
        //turn LED off
        LED_DDR &= ~(LED_PIN);
        
        //clear INTF (bit1) flag
        INTCON &= ~(BIT1);
    }
       
    //read TMR1IF (bit0), to check Timer1 interrupt
    if(PIR1 & BIT0)
    {
        //clear TMR1IF (bit0), to clear Timer1 interrupt flag
        PIR1 &= ~BIT0;
        //increment timer1 overflow count
        timer1_overflow_count = timer1_overflow_count + 1;
        //to get a time delay of 10 MS for each timer1 overflow
        TMR1 = 15536;
        
        //if timer1 overflow count reaches current threshold
        if(timer1_overflow_count == timer1_overflow_threshold)
        {
            //reset timer1 overflow count
            timer1_overflow_count = 0;
            //toggle LED1
            LED_REG ^= LED_PIN;
        }
    }
}
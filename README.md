# led_switch_interrupt_sleep
Code Explanation : (Controller used : PIC16F877A, 8bit, 20 Mhz external clock)

1) LED (PD0) is initiazed as output and turned OFF, SW (PB0) is initialized as input and external interrupt is enabled for this pin at falling edge.

2) TIMER1 (16bit) is configured with 1:1 prescalar, and internal clock (FOSC / 4) is used for this. Initial value is set to 15536, to get a time delay of 10 ms for each overflow. TIMER1 interrupt is enabled.

3) Inside ISR, we check for external switch press and change mode accordingly. For each mode timer interval is defined in main loop.

4) Inside ISR, LED is toggled as timer overflow occour for give time interval.

5) In main, for mode 0, LED off, controller goes into power down mode by SLEEP, before going to sleep, timer interrupt is disabled so that timer won’t wakeup the device, it can only wakeup from external switch interrupt.

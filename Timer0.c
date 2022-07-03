#include "Timer0.h"
 
void Timer0AInit(void) {         
                  //Timer Config
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);               //ENABLES CLOCK CONTROL FOR THE TIMER
    TimerDisable(TIMER0_BASE, TIMER_A);                         //Disabling the timer to configure its settings
    TimerConfigure(TIMER0_BASE , TIMER_CFG_PERIODIC);           //Configuring the timer on pre-set settings
    TimerLoadSet(TIMER0_BASE ,TIMER_A, 16000000);               //Setting the timer load
    TimerControlStall(TIMER0_BASE , TIMER_A, true);             
    //Timer Interrupt Enabling   
    IntEnable(INT_TIMER0A_TM4C123);                             //Enables the timer interrupt in the interrupt controller
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);          // Enables the indicated timer interrupt sources
    TimerIntRegister(TIMER0_BASE , TIMER_A, Timer0Handle);    //Registers the handler to be called when a timer interrupt occurs
}


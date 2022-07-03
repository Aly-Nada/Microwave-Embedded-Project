#ifndef __MICROWAVE__
#define __MICROWAVE__

//Definitions
#define TIMER0_BASE             0x40030000  // Timer0

//TERATERM
// Standard controlling commands for monitor sent using UART0    
#define ASCII_ESC 27

#define         CLEAR           "\033[2J\033[H"
#define         TAB             "\033t"
#define         NL              "\033[E"
#define         R               0x0D

//bitwise operations
#define CLEAR_BIT(REGISTER,PIN) (REGISTER) =((REGISTER) & ~((1) << (PIN)))
#define TOGGLE_BIT(REGISTER,PIN) (REGISTER) =(REGISTER^(1<<PIN))

//Inclusions
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "Timer0.h"
#include "UART.h"
#include "GPIOF.h"

//Function prototypes

void GPIOF_Handler(void); // Handles the GPIO interrupt when the start/stop/stopping for 3 seconds (PF4/PF0) buttons are pressed
void Timer0Handle(void); //Handles the timer interrupt after every second to decrement the counter 
void UART0_Handler(void); // Handles the UART0 interrupt when either M/G/Q/W/E are pressed(Received) to set the mode and  the incrementing option
void Status(void); //Displays on the screen the counter in hh:mm:ss and the current mode name and if process is stopped/finished ("STOPPED"/"DONE")



#endif
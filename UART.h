


#ifndef __UART__
#define __UART__
//Definitions
#define UART0_BASE              0x4000C000  // UART0
#define NULL (0)

//INCLUSIONS

#include "Microwave.h"


//Initializing function
void UART0Init(void);

//send function on tx
void UART0_Tx(uint8_t tx); //Sends 8 bits object (char/number) per time
void UART0_Send(uint8_t a[]); //Sends an array of characters

  

#endif
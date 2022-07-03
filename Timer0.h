#ifndef __TIMER0__
#define __TIMER0__

#define INT_TIMER0A_TM4C123     35          // 16/32-Bit Timer 0A
#include "Microwave.h"

//initializes timer
void Timer0AInit(void);  //Initializes the Timer0A and enables its interrupt


#endif
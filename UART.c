#include "UART.h"

void UART0Init(void) {
              SYSCTL_RCGCUART_R |= 1;           /* provide clock to UART0 */
              SYSCTL_RCGCGPIO_R |= 1;           /* enable clock to PORTA */
              SYSCTL_RCGCGPIO_R |= 0x20;        /* enable clock to PORTF */
/* UART0 initialization */
              UART0_CTL_R = 0;                  /* disable UART0 */
              UART0_IBRD_R = 104;               /* Intiger part 16MHz/16=1MHz, 1MHz/104=9600 baud rate */
              UART0_FBRD_R = 11;                /* fraction part*/
              UART0_CC_R = 0;                   /* use system clock */
              UART0_LCRH_R = 0x60;              /* 8-bit, no parity, 1-stop bit, no FIFO */
              UART0_IM_R |= 0x0010;             /* enable RX interrupt */
              UART0_CTL_R = 0x301;              /* enable UART0, TXE, RXE */
/* UART0 TX0 and RX0 use PA0 and PA1. Set them up. */
              GPIO_PORTA_DEN_R = 0x03;          /* Make PA0 and PA1 as digital */
              GPIO_PORTA_AFSEL_R = 0x03;        /* Use PA0,PA1 alternate function */
              GPIO_PORTA_PCTL_R = 0x11;         /* configure PA0 and PA1 for UART */
              GPIO_PORTF_DATA_R = 0;
              NVIC_EN0_R |=0x00000020;                                         /* Enabling interrupt in NVIC */
              UARTIntRegister(UART0_BASE,UART0_Handler);                 /*Registers the handler to be called when a UART0 interrupt occurs*/
}




void UART0_Tx(uint8_t tx){
          while ( (UART0_FR_R & 0x20 ) != 0);
          UART0_DR_R= tx;
}

void UART0_Send(uint8_t a[]){
      uint8_t i=0;
          while((a[i])!= NULL) {
          UART0_Tx(a[i]);
          i++;
          }   
}




    
   
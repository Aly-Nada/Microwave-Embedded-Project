
#include "GPIOF.h"

void PORTFInit(){
          SYSCTL_RCGCGPIO_R  |= 0x20;                           /* enable clock to PORTF */
          GPIO_PORTF_LOCK_R = 0x4C4F434B;                       /* unlock commit register */
          GPIO_PORTF_CR_R = 0x01;                               /* make PORTF0 configurable */
          GPIO_PORTF_LOCK_R = 0;                                /* lock commit register */
          GPIO_PORTF_DIR_R =0X00;                               /* make PORTF4 input for switch */
          GPIO_PORTF_DIR_R |=0x0E;                              /* make PORTF3, 2, 1 output for LEDs */
          GPIO_PORTF_DEN_R |= 0x1F;                             /* make PORTF4-0 digital pins */
          GPIO_PORTF_PUR_R |= 0x11;                             /* enable pull up for PORTF4, 0 */                     
          GPIO_PORTF_IS_R &=0x11;                               /* make bit 4, 0 edge sensitive */
          GPIO_PORTF_IBE_R &=0x11;                              /* trigger is controlled by IEV */
          GPIO_PORTF_IEV_R &=0x11;                              /* falling edge trigger */
          GPIO_PORTF_ICR_R |= 0x11;                             /* clear any prior interrupt */
          NVIC_EN0_R =0x40000000;                               /* Enabling interrupt in NVIC */
          GPIO_PORTF_IM_R = 0x11;                               /* unmask interrupt */
          GPIOIntRegister(GPIO_PORTF_BASE,GPIOF_Handler);       /*Registers the handler to be called when a GPIO PORT F interrupt occurs*/
}


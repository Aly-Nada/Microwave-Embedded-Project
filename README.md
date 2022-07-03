# Microwave-Embedded-Project
This Application is developed to immitiate the function of a microwave
using the Tiva C launchpad kit "TM4C123GH6PM" and some TivaWare library functions	
To use this driver you should be aware of the functions included

******IMPORTANT******
The included functions are:
PORTFInit(void);		General Purpose initializing function for port F
UART0_Tx (uint8_t tx); 		Function sends one character using uart0
UART0_Send (uint8_t a[]);	Function sends a string using uart0
Timer0AInit(void);		Timer0A initializing function
GPIOF_Handler(void); 		Handler function when there is a GPIO interrupt
Timer0Handle(void); 		Handler function when there is a Timer interrupt
UART0_Handler(void);		Handler function when there is a UART0 interrupt
Status(void);			Function sends current status and time to display
main(void);			function puts device sleep unless there is interrupt

#include "Microwave.h"


// variables used in different functions
uint8_t command;   //Character in which the UART Data Register value is saved
uint32_t time=0;   // Used for saving the counter  to be displayed on screen in minutes and seconds 
uint8_t StatusFlag=1; //Status flag is set to zero when an incremental option is set to allow the timer to start the decrementing
uint8_t StopFlag=2;  // A flag that is raised when the stop button is pressed for 3 seconds so as to disable the timer and clears counter
uint8_t BlinkingCounter=0; // Counter that is used to count 5 seconds of blinking the red LED after the counter reaches zero
uint8_t mode;  //Stores the name of the current process ('G'==Grill/ 'M'==Microwave) to display it on the screen during the process
uint8_t StoppingCounter=0; // A counter that is incremented each second when the stop button is pressed until it reaches 3,then StopFlag is raised
uint8_t process=0; //A flag that turns 1 when 'M' or 'G' are pressed so as to ignore any changes in the process when the counter is decrementing
uint8_t ProcessEndFlag=1; // A flag that is raised when counter reaches zero or gets cleared to prevent displaying "DONE" when a new mode is selected

//TERATERM
uint32_t hours;
uint32_t minutes;
uint32_t seconds;

void Status(void){
 hours=time/3600;
 minutes=(time/60)-(hours*60);
 seconds=time-((minutes*60)+(hours *3600));
 UART0_Send(CLEAR);
 if(mode=='M') {
   UART0_Send("Microwave Process");
 }
 else if(mode=='G') {
      UART0_Send("Grill Process");
 }
    UART0_Send(NL);
    UART0_Tx(R);
    UART0_Tx((hours/10)+'0');
    UART0_Tx((hours%10)+'0');
    UART0_Send(TAB);
    UART0_Tx(':');
    UART0_Send(TAB);
    UART0_Tx((minutes/10)+'0');
    UART0_Tx((minutes%10)+'0');
    UART0_Send(TAB);
    UART0_Tx(':');
    UART0_Send(TAB);
    UART0_Tx((seconds/10)+'0');
    UART0_Tx((seconds%10)+'0');
if(StatusFlag==5) {
    UART0_Send(NL);
    UART0_Tx(R);
    UART0_Send("STOPPED!");
     
  }
  if(StoppingCounter==3) {
    UART0_Send(NL);
    UART0_Tx(R);
    UART0_Send("Process Eliminated");
    UART0_Send(NL);
    UART0_Tx(R);
    CLEAR_BIT(GPIO_PORTF_DATA_R,2);
    CLEAR_BIT(GPIO_PORTF_DATA_R,3);
    ProcessEndFlag=1;
    StatusFlag=2;
}

else if(((command=='M'&&time==0)||(command=='G'&&time==0)||(command=='Q'&&time==0)||(command=='W'&&time==0)||(command=='E'&&time==0)) && (ProcessEndFlag==0) ){
 
     UART0_Send(NL);
     UART0_Tx(R);

     UART0_Send("DONE!");
              
     if(BlinkingCounter<6) {
       TOGGLE_BIT(GPIO_PORTF_DATA_R,1);
       BlinkingCounter++;
     }
        CLEAR_BIT(GPIO_PORTF_DATA_R,2);
      CLEAR_BIT(GPIO_PORTF_DATA_R,3);
                
     if(BlinkingCounter==6) {
              GPIO_PORTF_DATA_R=0x00;
               TimerDisable(TIMER0_BASE, TIMER_A);
               process=0;
               ProcessEndFlag=1;
   
       
  }

}
} 


//UART HANDLER

void UART0_Handler(void) {
  if(process==0) {
  if(UART0_MIS_R & 0x0010) {
    command=UART0_DR_R;
        UART0_ICR_R = 0x0010;

  if(command=='M') {
    GPIO_PORTF_DATA_R=0x04;
    mode='M';
  }
  else if(command=='G') {
        GPIO_PORTF_DATA_R=0x08;
        mode='G';
  }
  if(command=='M' || command=='G' || command=='Q'  || command=='W' || command=='E') {
   if(command=='Q') {
     time+=10;
   StatusFlag=0;}
if(command=='W') {
  time+=60;
StatusFlag=0;}
if(command=='E') {
  time+=1800;
StatusFlag=0;}
  }
}
Status();
}
}

//GPIO HANDLER
void GPIOF_Handler(void)
{
  while (GPIO_PORTF_MIS_R != 0)
{
  if (GPIO_PORTF_MIS_R & 0x10) {
      GPIO_PORTF_ICR_R = 0x11; 
      GPIO_PORTF_MIS_R = 0;
      BlinkingCounter=0;
      CLEAR_BIT(GPIO_PORTF_DATA_R,1);
      StatusFlag=0;
                         TimerEnable(TIMER0_BASE, TIMER_A);
                         process=1;
  }
  else if (GPIO_PORTF_MIS_R & 0x01) {
        GPIO_PORTF_ICR_R = 0x11;
              GPIO_PORTF_MIS_R = 0;
        
        process=0;

        StatusFlag=5;
        Status();
}
}
}
//TIMER0 HANDLER
void Timer0Handle() {
   TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
   if(StatusFlag==0) {
         time--;
      if(time==0) {
          StopFlag=1;
          ProcessEndFlag=0;
      }
          StatusFlag=1;
      if(StatusFlag==1 && time>0) {
          Status();
          StatusFlag=0;
         }
   }
   
   if(time==0 && StopFlag==1) {
          Status();
          StatusFlag=3;
   }

  if((GPIO_PORTF_DATA_R & 0x01)==0) {
    StoppingCounter++;
    if(StoppingCounter==3) {
        time=0;
        Status();
        StatusFlag=3;
        StoppingCounter=0;
        TimerDisable(TIMER0_BASE, TIMER_A);
        process=0;
    }
  }
}

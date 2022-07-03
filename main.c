#include "Microwave.h"

int main()
{
  //Initializations
  PORTFInit();
  UART0Init();
  Timer0AInit();
  //Master interrupt enabling
  IntMasterEnable();     

  while(1)
  {
    SysCtlSleep();              // System sleep for saving power
  }
}



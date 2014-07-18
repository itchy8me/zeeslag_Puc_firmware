//#include <inc/lm4f120h5qr.h>

//#include <driverlib/gpio.h>
#include "../include/dc_motor.h"
#include "../include/strobe.h"
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <driverlib/adc.h>
#include <driverlib/gpio.h>
#include <driverlib/sysctl.h>
#include <utils/uartstdio.h>
#include "../include/diag_interface.h"
#include "../include/PowerSysCtrl.h"

 
/* General delay function */
void delay(unsigned long count){
  unsigned long i = 0;
  for(i=0; i < count; i++){;}
}

int main(void){
  SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
  //
  // This array is used for storing the data read from the ADC FIFO. It
  // must be as large as the FIFO for the sequencer in use.  This example
  // uses sequence 3 which has a FIFO depth of 1.  If another sequence
  // was used with a deeper FIFO, then the array size must be changed.
  //
 
  volatile unsigned long analog_diag = 0; 
  unsigned long count = 5000000;
  unsigned long i = 0;
  
  //CLOCK_CFG;
  InitConsole();
  strobe_enable();
  
  analog_diag_enable();
  dc_motor_init(1,1,1);
  while(1){
    //for(i=0; i < count; i++){;}
    analog_diag = sample_analog_diag();
    analog_diag = analog_diag*1048576;
    strobe_set_interval(analog_diag);
    delay(5000000);
    // = sample_analog_diag();
    

  }
}
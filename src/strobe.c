
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"

#include <inc/hw_types.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/timer.h>
#include "../include/strobe.h"
#include "../include/diag_interface.h"

static volatile int strobe_sequence_IDLE[14] = {LED_YELLOW, LED_BLACK, LED_BLACK, LED_YELLOW, LED_BLACK, LED_BLACK, LED_YELLOW, LED_BLACK, LED_BLACK, LED_YELLOW, LED_BLACK, LED_BLACK, LED_YELLOW, LED_BLACK}; //{LED_R, LED_BLACK, LED_B};
static volatile int strobe_sequence_SUPERSYS[14] = {LED_R, LED_BLACK, LED_G, LED_BLACK, LED_B, LED_BLACK, LED_WHITE, LED_BLACK, LED_YELLOW, LED_BLACK, LED_PURPLE, LED_BLACK, LED_CYAN, LED_BLACK}; //{LED_R, LED_BLACK, LED_B};

//static * strobe_sequence = strobe_sequence_A;
static volatile int LED = 0;
volatile unsigned long analog_diag = 0;


void strobe_pattern(int pattern_num){
	switch (pattern_num){
		case 0:
			if(LED == STROBE_SEQ_LEN){LED = 0;}
			GPIOPinWrite(GPIO_PORTF_BASE, LED_WHITE, strobe_sequence_IDLE[LED]);
			LED++;
			break;
		case 1:
			if(LED == STROBE_SEQ_LEN){LED = 0;}
			GPIOPinWrite(GPIO_PORTF_BASE, LED_WHITE, strobe_sequence_SUPERSYS[LED]);
			LED++;
			break;
	}
}


void strobe_enable(void){

  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_WHITE);
  GPIOPinWrite(GPIO_PORTF_BASE, LED_WHITE, 0x02);
  
  
  /* Start timer for strobe */
  
  //void (*strobe_handle) (strobe);
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER4);
  TimerConfigure(TIMER4_BASE, TIMER_CFG_A_PERIODIC);
  TimerIntEnable(TIMER4_BASE, TIMER_TIMA_TIMEOUT);
  TimerIntRegister(TIMER4_BASE,TIMER_A, strobe);
}


// void strobe_init(void){
//   TimerConfigure(TIMER0_BASE,)
// }
void strobe_disable(void){
}


void strobe_set_interval(unsigned long interval){
  TimerDisable(TIMER4_BASE, TIMER_A);
  TimerLoadSet(TIMER4_BASE, TIMER_A, interval);
  TimerMatchSet(TIMER4_BASE, TIMER_A, interval); //(TimerLoadGet(TIMER0_BASE, TIMER_A)/2));
  TimerEnable(TIMER4_BASE, TIMER_A);
}


void strobe(void){
  TimerIntClear(TIMER4_BASE, TIMER_TIMA_TIMEOUT);
  strobe_set_interval(analog_diag);
  strobe_pattern(1);
}
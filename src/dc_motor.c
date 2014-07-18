
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"

#include <inc/hw_types.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/timer.h>
#include "../include/dc_motor.h"
#include <driverlib/pin_map.h>


/*
 * 	Function: dc_motor_ctrl :
 * 	Description : Drives the attached dc motor according to the input paameters past to the function
 * 	Param:
 * 	direction : 	
 * 		off 		- 	0x1
 * 		clockwise 	-	0x2
 *		anticlockwise	-	0x3
 *	throttle :
 * 		[0 - 100] %
 * 
 */


void dc_motor_init(unsigned short throttle, unsigned short bridgA, unsigned short bridgeB){

  /* Cannot get PIN F0 unlocked, routing T0CCP0 to PB6 instead, will try later again */
  
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  ///Reset PF0, release from NMI
  HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY_DD;
  HWREG(GPIO_PORTF_BASE + GPIO_O_CR)  |= 0x01;
  HWREG(GPIO_PORTF_BASE + GPIO_O_AFSEL) &= 0xFE;
  HWREG(GPIO_PORTF_BASE + GPIO_O_DEN) &= 0xFE;
  HWREG(GPIO_PORTF_BASE + GPIO_O_PCTL) = 0x00;
  //
  
  HWREG(GPIO_PORTF_BASE + GPIO_O_AFSEL) |= 0x01;
  HWREG(GPIO_PORTF_BASE + GPIO_O_DEN) |= 0x01;
  HWREG(GPIO_PORTF_BASE + GPIO_O_PCTL) |= 0x07;
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  
  /* F0 unclock code

  */
  HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
  
  GPIOPinConfigure(GPIO_PF0_T0CCP0);
  GPIOPinTypeTimer(GPIO_PORTF_BASE, GPIO_PIN_0);
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PWM);
  TimerLoadSet(TIMER0_BASE, TIMER_A, 50000);
  TimerMatchSet(TIMER0_BASE, TIMER_A, 25000); //(TimerLoadGet(TIMER0_BASE, TIMER_A)/2));
  TimerEnable(TIMER0_BASE, TIMER_A);  
  //GPIODirModeSet(GPIO_PORTF_BASE, 0x01, GPIO_DIR_MODE_OUT);
  
//   HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) |= GPIO_LOCK_KEY;
//   HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;  
//   HWREG(GPIO_PORTF_BASE + GPIO_O_PCTL) |= 0x10;
  //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
  
  
//     unsigned long ulPeriod, dutyCycle;
// 
//     // 40 MHz system clock
//     SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|
//         SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
// 
//     ulPeriod = 1000;
//     dutyCycle = 250;
// 
//     // Turn off LEDs
//     SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//     GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
//     GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
// 
//     // Configure PB6 as T0CCP0
//     SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
//     GPIOPinConfigure(GPIO_PB6_T0CCP0);
//     GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_6);
// 
//     // Configure timer
//     SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
//     TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PWM);
//     TimerLoadSet(TIMER0_BASE, TIMER_A, ulPeriod -1);
//     TimerMatchSet(TIMER0_BASE, TIMER_A, dutyCycle); // PWM
//     TimerEnable(TIMER0_BASE, TIMER_A);
}

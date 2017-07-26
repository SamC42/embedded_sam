/* 
 * Sam Cesario
 * Description: From edx Class Lab 7. Function to mimic a pacemaker
 *  Ready output is connected to PF3
 *  LED will be green when Ready is high
 *  VT output is connected to PF1
 *  LED will be Red when VT is high
 *  A 250 ms pulse will cause the ventricules to contract
 *  
 *  Notes:
 *  	Input  = PF4(SW1) is AS (atrial sensor), 
 *  	Output = PF3, Green LED, is Ready,
 *  	Output = to PF1, Red LED, is VT (ventricular trigger) 
 *  	Initialize Ready to high and VT to low
 */

// inclues
#include "TExaS.h"
//#include <stdint.h>
//#include <stdbool.h>
//#include "../tm4c123gh6pm.h"
//#include "../driverlib/sysctl.h"

// AS = PF4
#define AS (*((volatile unsigned long *) 0x40025040)) 
// Ready = PF3
#define Rdy (*((volatile unsigned long *) 0x40025020)) 
// VT = PF1
#define VT (*((volatile unsigned long *) 0x40025008)) 

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
//   Global Variables

// Functions
void PortF_Init(void);
void Delay1ms(unsigned long msec);
void EnableInterrupts(void);
void WaitForASLow(void);
void WaitForASHigh(void);
void SetVT(void);
void ClearVT(void);
void SetReady(void);
void ClearReady(void);


int main(void){
  TExaS_Init(SW_PIN_PF40, LED_PIN_PF31,ScopeOn);  // activate grader and set system clock to 80 MHz
  PortF_Init();                            // Init port PF4 PF3 PF1    
  EnableInterrupts();                      // enable interrupts for the grader  
  while(1){
		VT = 0x00;
		// Make Ready signal go high
		SetReady();
		// Wait for AS to be 0, switch to be pressed
		WaitForASLow();
		// Make the Ready signal go low
		ClearReady();
		// wait 10ms
		Delay1ms(10);
		// Wait for AS to be 1, switch to be released
		WaitForASHigh();
		// Wait 250ms
		Delay1ms(250);
		// Make the VT signal go high
		SetVT();
		// Wait 250ms
		Delay1ms(250);	
		// Make the VT signal go low
		ClearVT();
	}
  
}
/* Subroutine to initialize port F pins for input and output
 * PF4 is input SW1 and PF3-1 is output LEDs
 * Inputs: None
 * Outputs: None
 */ 
void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;      // 1) F clock
  delay = SYSCTL_RCGC2_R;            // delay to allow clock to stabilize     
  GPIO_PORTF_AMSEL_R &= 0x00;        // 2) disable analog function
  GPIO_PORTF_PCTL_R &= 0x00000000;   // 3) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R &= ~0x10;         // 4.1) PF4 input,
  GPIO_PORTF_DIR_R |= 0x0E;          // 4.2) PF3,2,1 output  
  GPIO_PORTF_AFSEL_R &= 0x00;        // 5) no alternate function
  GPIO_PORTF_PUR_R |= 0x10;          // 6) enable pullup resistor on PF4       
  GPIO_PORTF_DEN_R |= 0x1E;          // 7) enable digital pins PF4-PF1
}
// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E


/* Subroutine reads AS input and waits for signal to be low
 * If AS is already low, it returns right away
 * If AS is currently high, it will wait until it to go low
 * Inputs:  None
 * Outputs: None
 */
void WaitForASLow(void){
//Read AS
	while(AS){
		
	}
	// If AS is low -> return right away
	// If AS is high -> wait untill it goes low then returns
}

/* Subroutine reads AS input and waits for signal to be high
 * If AS is already high, it returns right away
 * If AS is currently low, it will wait until it to go high
 * Inputs:  None
 * Outputs: None
 */
void WaitForASHigh(void){
	while(!AS){
		
	}
}
/* Subroutine sets VT high
 * Inputs:  None
 * Outputs: None
 */
void SetVT(void){
	VT = 0x02;
}

/* Subroutine clears VT low
 * Inputs:  None
 * Outputs: None
 */
void ClearVT(void){
	VT = 0x00;
}

/* Subroutine sets Ready high
 * Inputs:  None
 * Outputs: None
 */ 
void SetReady(void){
	Rdy = 0x08;
}


/* Subroutine clears Ready low
 * Inputs:  None
 * Outputs: None
 */ 
void ClearReady(void){
	Rdy = 0x00;
}

/* Subroutine to delay in units of milliseconds
 * Inputs:  Number of milliseconds to delay
 * Outputs: None
 */
void Delay1ms(unsigned long time){
	
	//SysCtlDelay(msec * (SysCtlClockGet() / 3 /1000));
	unsigned long i;
	while(time>0){
		i=13333; //this num means 1000ms
		while(i>0){
			i=i-1;
		}
		time = time-1; //decrements every 100ms
	}

}


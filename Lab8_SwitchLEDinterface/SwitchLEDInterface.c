// ***** 0. Documentation Section *****
// SwitchLEDInterface.c for Lab 8
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to toggle an LED
// while a button is pressed and turn the LED on when the
// button is released.  This lab requires external hardware
// to be wired to the LaunchPad using the prototyping board.
// January 15, 2016
//      Jon Valvano and Ramesh Yerraballi

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "../tm4c123gh6pm.h"

// ***** 2. Global Declarations Section *****
// GPIO_PORTE_DATA_R definitions
#define SW1 (*((volatile unsigned long *) 0x40024004)) //Switch - PE0
#define LED1 (*((volatile unsigned long *) 0x40024008)) //LED   - PE1

// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

unsigned long volatile delay; //output to PF2 (LED)

void PortE_init(void);
void Delay1ms(unsigned long time);

int main(void){
	TExaS_Init(SW_PIN_PE0, LED_PIN_PE1, ScopeOn);  // activate grader and set system clock to 80 MHz
  EnableInterrupts();           // enable interrupts for the grader
	PortE_init(); // Make PF2 an output and make PF4 and input (enable PUR for PF4)
	// The system starts with the LED ON (make PE1=1)
	LED1 =0x02;
	while(1){
		// If the switch is pressed (PE0 is 0)
		if(!SW1){ //PE0 is 1
			// Then toggle the LED once	
			LED1 = 0x02; // Toggle LED1 on 

		} 
		else{
			LED1 = LED1^0x02; // Toggle LED1
			Delay1ms(100);

		}
	}
}



// Initialize Port E Register w/ PE1 output and PE0 input
void PortE_init(void){
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000010;   // 1. activate the clock for Port E
	delay = SYSCTL_RCGC2_R;         //    allow time for clock to start
	//GPIO_PORTE_LOCK_R = 0x4C4F434B;// 2. Unlock GPIO Port F
	//GPIO_PORTE_CR_R = 0x1F;       //    allow changes to PF4-0 
	GPIO_PORTE_AMSEL_R &= ~0x03;    // 3. Disable analog on Port E
	GPIO_PORTE_PCTL_R = 0x00000000; // 4. PCTL GPIO on PE1, PE4 (see table 6.1)
	GPIO_PORTE_DIR_R |= 0x02;       // 5. PE1 output .... 0000 0010
	GPIO_PORTE_DIR_R &= ~0x01;      // 5. PE0 input  .... 0000 0001
	GPIO_PORTE_AFSEL_R = 0x00;      // 6. disable alt functionality on PE7-0
	//GPIO_PORTE_PUR_R = 0x10;      //    enable pull-up on PF4
	GPIO_PORTE_DEN_R |= 0x03;       // 7. Enable digital I/O on PE1,0
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

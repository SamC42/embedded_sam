/* BranchingFunctionsDelays.c Lab 6 - from UTAustinX: UT.6.10x Embedded Systems - Shape The World: Microcontroller Input/output 

// Description:
// 	Use simple programming structures in C to 
// 	toggle an LED while a button is pressed and 
// 	turn the LED on when the button is released.  

*/

// built-in connection: PF0 connected to negative logic momentary switch, SW2
// built-in connection: PF1 connected to red LED
// built-in connection: PF2 connected to blue LED
// built-in connection: PF3 connected to green LED
// built-in connection: PF4 connected to negative logic momentary switch, SW1

#include "TExaS.h"
#include <../TM4C123GH6PM.H>

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOF      0x00000020  // port F Clock Gating Control

#define SW1 (*((volatile unsigned long *) 0x40025040)) // Switch = PF4
#define LED1 (*((volatile unsigned long *) 0x40025010)) //LED - PF2

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void PortF_init(void);
void Delay100ms(unsigned long);
int main(void){ 
	unsigned long volatile delay;
	unsigned long time1=1;
  TExaS_Init(SW_PIN_PF4, LED_PIN_PF2);  // activate grader and set system clock to 80 MHz
  // initialization goes here
	PortF_init();
  EnableInterrupts();           // enable interrupts for the grader
	while(1){
		Delay100ms(time1);		
    if(SW1){ //PF4 is 1
			LED1 = 0x04; // LED On
			
  }
		else{ //PR4 is 0
			LED1 = LED1^0x04; // LED On
		}
	}
}


void PortF_init(void){
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x0000020;    // 1. Activate the clock for port F
	delay = SYSCTL_RCGC2_R;         // allow time for the clock to start
	GPIO_PORTF_LOCK_R &= 0x4C4F434B; // 2. Unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;         // allow changes to PF4-0 TODO: Fix
	GPIO_PORTF_AMSEL_R = 0x00;      // 3. Disable analog output
	GPIO_PORTF_PCTL_R = 0x00000000; // 4. PCTL GPIO on PF7-0 (see table 6.1)
	GPIO_PORTF_DIR_R = 0x0E;        // 5. PF4 in, PF2 out // setting/clearing bits
	GPIO_PORTF_AFSEL_R = 0x00;      // 6. disable alt functionality on PF7-0
	GPIO_PORTF_PUR_R = 0x10;        // 7. Enable pullup resistor
	GPIO_PORTF_DEN_R = 0x1F;        // Enable Digital I/O on PF4-0 TODO: Fix
}
 
void Delay100ms(unsigned long time){
	unsigned long i;
	while(time>0){
		i=1333333; //this num means 1000ms
		while(i>0){
			i=i-1;
		}
		time = time-1; //decrements every 100ms
	}
}

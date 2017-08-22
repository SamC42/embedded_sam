// Arm notes
// Sam Cesario

/* Initializing a Port (F)
 * Notation help - see table 6.1 
 * Note: For Port F only bits PF0 - PF4 are used in data register
 * Port Bit  | Bits |  Binary  
 * PF0		 |  0   | 0000 0001
 * PF1		 |  1   | 0000 0010
 * PF2		 |  2   | 0000 0100
 * PF3		 |  3   | 0000 1000
 * PF4		 |  4   | 0001 0000 
 */
void PortF_init(void){
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000020; // Activates the Clock for Port F (0x20)
	delay = SYSCTL_RCGC2_R; // Allows time for the clock to start
	GPIO_PORTF_LOCK_R &= 0x4C4F434B; // Unlock GPIO Port F (address from datasheet)
	GPIO_PORTF_CR_R = 0x1F;  // Allow changes to specifc Port bits
							 // Port Bits are defined where bit 0 is 0000 0001, bit 1 is 0000 0010 etc.
	GPIO_PORT_AMSEL_R = 0x00; //Disable Analog on PF
	GPIO_PORTF_PCTL_R = 0x00000000; // Clear bits to select regular digital function
	GPIO_PORTF_DIR_R = 0x0E; // set = output clear = input, this example = 0000 1110 so PF4 and PF0 are inputs, PF3-PF1 are outputs
	GPIO_PORTF_AFSEL = 0x00; //Disable the Alt functions
	GPIO_PORTF_PUR_R = 0x11; // Enable Pullup resistors on PF4,PF0
	GPIO_PORTF_DEN_R = 0x1F;	// Enable digital I/O on PF4-PF0
	
	
}
/* Bit Specific Addressing - Defining bits of the Data Port A
 * We use the notation: (*((volatile unsigned long *) ... )) to define a 32 bit address. We then point a constant to that address.
 * Example: 8 bits of Port A
 * Data Reg for Port A starts at 0x40004000
 * volatile - Forces compiler to read new value each time, stating that it can be changed from outside the program
 * for PA7 - bit 7 is 0x0200 for the bits of the data reg
 * Bit | Hex    | Binary
 * 0   | 0x0200 | 0000 0010 0000 0000
 * 1   | 0x0100 | 0000 0001 0000 0000
 * 2   | 0x0080 | 0000 0000 1000 0000
 * 3   | 0x0040 | 0000 0000 0100 0000
 * 4   | 0x0020 | 0000 0000 0010 0000
 * 5   | 0x0010 | 0000 0000 0001 0000
 * 6   | 0x0008 | 0000 0000 0000 1000
 * 7   | 0x0004 | 0000 0000 0000 0100
 * 
 * Notice: The bits are just offset by 0000 0000
 */
#define PA7 (*((volatile unsigned long *) 0x40004200 ))
#define PA6 (*((volatile unsigned long *) 0x40004100 ))
#define PA5 (*((volatile unsigned long *) 0x40004080 ))
#define PA4 (*((volatile unsigned long *) 0x40004040 ))
#define PA3 (*((volatile unsigned long *) 0x40004020 ))
#define PA2 (*((volatile unsigned long *) 0x40004010 ))
#define PA1 (*((volatile unsigned long *) 0x40004008 ))
#define PA0 (*((volatile unsigned long *) 0x40004004 ))

/* Clearing a Bit &= ~0xYY
 * Clearning a bit makes the bit  low or 0
 * Using the Define statement above we can clear PA5
 * This code will only change the value at PA5
 */
 PA5 = 0x00;
 PE4 & = ~0x10;
 
/* Setting a Bit
 * Setting a bit makes the bit high or 1
 * Using the Define statement above we can set PA5
 * This code will only change the value at PA5
 * NOTE: We use 1 in the bit 5 space, do not get confused between the data register address and normal space for bit 5. We are only changing the VALUE OF PA5
 * PA5  | 0x00000020 | ... 0000 0000 0010 0000
 */
	PA5 = 0x20;
	//Set PE4 to 1
	PE4 = 0x10; // .... 0001 0000 Setting the addresw pf PE4 Data to 1
	
	
/* Toggling a bit (^)
 * Example: Toggle bit 5
 * If PA5 is an output then the Or functionality will toggle it on or off
 */
 PA5 = PA5^0x20;
 
 /* Initializing
  *
  */
	//Output 
	GPIO_PORTE_DIR_R |= 0x02;        // 5. PE1 output .... 0000 0010
	//Input since &= ~0xYY zeros out the bit you show
	GPIO_PORTE_DIR_R &= ~0x01;        // 5. PE0 input  .... 0000 0001
	
#include "exti.h"


// P1.2 input  Button 2  ~ EXTI1
// P1.4 input  Button 7  ~ EXTI0

void EXTI_Init(void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;              // Configured for IT01CF

	//set pin exti
	
	 IT01CF = 0x24 ;  // P1.2 = exti1,  P1.4 = exti0
										//input is active low(falling) = 0x24.
										//input is active high(rising) = 0xac.
	
	 // Priority
	
	 PX1 = 1;        // exti1  priority level.
	 PX0 = 0;				 // exti0  priority level.
	
	 TCON  |= 0x05;     //External Interrupt 0, 1  edge triggered = 0x05 / level = 0x00.
											//
	
	 EX0 = 1;            // Enable External Interrupt 0
   EX1 = 1;            // Enable External Interrupt 1

   SFRPAGE = SFRPAGE_save;
}


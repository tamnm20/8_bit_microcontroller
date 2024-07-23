#include <compiler_defs.h>
#include <C8051F580_defs.h>
#include <stdio.h>
#include "clock.h"
#include "gpio.h"
#include "timer.h"
#include "exti.h"

int x0 = 0;
int x1 = 0;
int i =0;
INTERRUPT(EXTI0, INTERRUPT_INT0)
{
	LED_YELLOW = 0x01;
	//for(i =0; i<2; i++){ex0 ++;}
	x0 ++;
	x0 ++;
}

INTERRUPT(EXTI1, INTERRUPT_INT1)
{
	LED_YELLOW = 0x00; 
	for(i =0; i<10; i++){x1 ++;}
	x1 ++;
}
 

unsigned int adc_value;
float temperature;
int main(void)
{
   SFRPAGE = ACTIVE_PAGE;

   PCA0MD &= ~0x40;                    // Disable the watchdog timer

   RCC_Init ();                 // Configure system clock
   PORT_Init ();                       // Initialize crossbar
   TIMER2_Init ();      // Init Timer2 to generate 
	//TIMER2_Interrupt_Init();   // Init Timer2 to generate interrupts
                                      
   EXTI_Init();
	
   EA = 1;                             // Enable global interrupts
	 LED_GREEN = 0;
   LED_YELLOW = 0; 
   while (1)                        
	{
		LED_GREEN = 0x01;
		Delay_ms(1000);
		//Delay_IT_ms(100);
		LED_GREEN = 0x00;
		//Delay_IT_ms(100);
		Delay_ms(1000);
		

	}

	return 0;
}




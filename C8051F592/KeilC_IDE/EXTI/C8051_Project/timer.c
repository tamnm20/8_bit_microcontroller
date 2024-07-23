#include "timer.h"


//-----------------------------------------------------------------------------
// TIMER2_Init
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    U16 counts - number of system clock cycles between interrupts
//                             range is 0 to 65535
//
// Configure Timer2 to 16-bit auto-reload and generate an interrupt at
// interval specified by <counts> using SYSCLK/12 as its time base.
// 
//  RCC: 24M/12 = 2M
// => 1s thuc hien 2M giao dong
// => 1ms ---------2M/1000 = 2000 giao dong
//-----------------------------------------------------------------------------

void TIMER2_Init (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = ACTIVE_PAGE;

	 TMR2CN = 0x00; // Timer 2 operates in 16-bit auto-reload mode.
									//Timer 2 clock is the system clock divided by 12.

	 CKCON &= ~0x30; //Selects the clock supplied to Timer 2, System clock divided by 12
	
	 TMR2RL  = 0xFFFF - 2000;   // Init reload values
	
		TMR2  = TMR2RL;
	  TR2     = 1;

   SFRPAGE = SFRPAGE_save;
}


void Delay_ms(U32 time)
{
	while ( time > 0)
	{
		if(TF2H  == 1)
		{
			time --;
			TF2H = 0;
		}
	}
}


//----------------------------------- config timer 2 interrupt------------------------------------------

void TIMER2_Interrupt_Init (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = ACTIVE_PAGE;

	 TMR2CN = 0x00; // Timer 2 operates in 16-bit auto-reload mode.
									//Timer 2 clock is the system clock divided by 12.

	 CKCON &= ~0x30; //Selects the clock supplied to Timer 2, System clock divided by 12
	
	 TMR2RL  = 0xFFFF - 2000;   // Init reload values
	
   TMR2    =  TMR2RL;          // Set to reload immediately
   ET2     = 1;                        // Enable Timer2 interrupts
   TR2     = 1;                        // Start Timer2

   SFRPAGE = SFRPAGE_save;
}

U32 time_delay = 0;
INTERRUPT (TIMER2_ISR, INTERRUPT_TIMER2)
{
   time_delay ++;
   TF2H = 0;                           // Reset Interrupt 
}

void Delay_IT_ms(U32 time)
{
	while(time > time_delay);
	time_delay =0;
}
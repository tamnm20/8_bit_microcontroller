#include "gpio.h"

//-----------------------------------------------------------------------------
// PORT_Init
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configure the Crossbar and GPIO ports.
//
// P2.1 - digital  push-pull   LED Green
// P2.0 - digital  push-pull   LED Yellow

// P1.2 - digital  push-pull   Button 2
// P1.4 - digital  push-pull   Button 7
//
//-----------------------------------------------------------------------------
void PORT_Init (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;

	// P2.1 led green
   P2MDOUT |= (1<<1);                    // Enable LED as a push-pull output
   P2SKIP  |= (1<<1);                    // Skip the LED pin on the crossbar

		// P2.0 led yellow
   P2MDOUT |= (1<<0);                    // Enable LED as a push-pull output
   P2SKIP  |= (1<<0);                    // Skip the LED pin on the crossbar
		
	// P1.2  switch 2
	 P1MDIN  |= (1<<2);
	 P1SKIP  |= (1<<2); 
	
   XBR2     = 0x40;                    // Enable crossbar and weak pull-ups

   SFRPAGE = SFRPAGE_save;
}


U8 State_SW2()
{
//	U8 status = (status_sw2 >>2) &1;
//	return status;
	return SW2_Button;
}




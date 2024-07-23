#include "clock.h"
//-----------------------------------------------------------------------------
// OSCILLATOR_Init
//-----------------------------------------------------------------------------
// 
// Return Value:  None
// Parameters:    None
//
// Configure the internal oscillator to maximum internal frequency 24M / 1
//
//-----------------------------------------------------------------------------
void RCC_Init (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;

   OSCICN = 0x87;

   SFRPAGE = SFRPAGE_save;
}
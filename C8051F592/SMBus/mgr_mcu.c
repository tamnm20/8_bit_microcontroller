#include "compiler_defs.h"
#include "C8051F580_defs.h"
#include "mgr_mcu.h"
#include "drv_mcu.h"
#include "drv_timer.h"
#include "drv_i2c.h"

void Init_McuTask(void) {
	SEG_XDATA U8	i;
	SFRPAGE = ACTIVE_PAGE;			// Set SFR Page for PCA0

	PCA0MD &= (U8)(~0x40U);			// Disable Watchdog Timer
	
	VDM0CN = 0x80U;					// low 1.75V VDD Monitor

	for (i = 0; i < 255U; i++){;}	// Wait 5us for initialization

	Osc_Init();		
	Port_Init();
	Exinterrupt_Init();
	Global_Timer_Init();
	EA = 1;						// Enable global interrupts
}
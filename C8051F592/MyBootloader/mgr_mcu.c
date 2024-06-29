/*_____ I N C L U D E __________________________________________*/
#include "compiler_defs.h"
#include "C8051F580_defs.h"
#include "global_define.h"
#include "mgr_mcu.h"
#include "mgr_diag.h"
#include "drv_timer.h"
#include "drv_mcu.h"
#include "drv_mem.h"
#include "desc.h"
#include "nm_basic.h"
#include "il_inc.h"
/*--------------------------------------------------------------*/

void Init_McuTask(void)
{	
	SEG_XDATA U8	i;


	SFRPAGE = (U8)ACTIVE_PAGE;		// Set SFR Page for PCA0

	PCA0MD &= (U8)(~0x40U);			// Disable Watchdog Timer
	
	VDM0CN	= 0x80U;				// low 1.75V VDD Monitor

	for (i = 0; i < 255; i++){;}		// Wait 5us for initialization

	RSTSRC   = 0x06U;    			// Enable Missing Clock Detector, VDD MONITOR
	
	Osc_Init();				// Initialize oscillator
	Port_Init();					// Initialize Port
	Global_Timer_Init();

	EA = 0;                             // Disable global interrupts					// Enable global interrupts
}

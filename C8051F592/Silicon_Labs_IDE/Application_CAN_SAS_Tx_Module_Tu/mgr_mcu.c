/*_____ I N C L U D E __________________________________________*/
#include "compiler_defs.h"
#include "C8051F580_defs.h"
#include "global_define.h"
#include "mgr_mcu.h"
#include "drv_timer.h"
#include "drv_mcu.h"
#include "drv_mem.h"
#include "drv_spi.h"
#include "mgr_diag.h"
#include "mgr_comm.h"

/*--------------------------------------------------------------*/

void Init_McuTask(void)
{	
	SEG_XDATA U8	i,ret;
	SFRPAGE = ACTIVE_PAGE;		// Set SFR Page for PCA0

	PCA0MD &= (U8)(~0x40U);			// Disable Watchdog Timer
	
	VDM0CN = 0x80U;				// low 1.75V VDD Monitor

	for (i = 0; i < 255U; i++){;}		// Wait 5us for initialization
	
	Osc_Init();				// Initialize oscillator
	Port_Init();	
	Exinterrupt_Init();
	Global_Timer_Init();
	EA = 1;						// Enable global interrupts
}

void Operate_McuTask(void)
{
	U8 On_Time;
	U8 ret = FALSE;
	static SEG_XDATA U8	init_flag = FALSE;
}

void Reset_Mcu(void)
{
	MCU_Reset();
}

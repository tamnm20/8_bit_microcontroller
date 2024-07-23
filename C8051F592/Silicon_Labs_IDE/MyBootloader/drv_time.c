/*_____ I N C L U D E __________________________________________*/
#include "compiler_defs.h"
#include "C8051F580_defs.h"
#include "Global_Define.h"
#include "drv_time.h"
#include "drv_mcu.h"
/*--------------------------------------------------------------*/

INTERRUPT_PROTO (Timer2_ISR, INTERRUPT_TIMER2);


INTERRUPT(Timer2_ISR, INTERRUPT_TIMER2)
{
	TF2H = 0x00U;
	
}

void Timer2_Init (void)
{
	SEG_XDATA U8 SFRPAGE_save = (U8)SFRPAGE;
	SFRPAGE = (U8)ACTIVE_PAGE;

	TMR2CN  = 0x00U;                    // Stop Timer2; Clear TF2;
	                                   // use SYSCLK/12 as timebase 500ns unit
	CKCON  &= (U8)(~0x60U);             // Timer2 clocked based on T2XCLK;

	//   TMR2RL  = 0xB1E0U;           // Init reload values//for 10ms -20000
	TMR2RL  = 0xF830U;           // Init reload values//for 1ms	-2000

	TMR2    = 0xFFFFU;                   // Set to reload immediately
	ET2     = 0x01U;                     // Enable Timer2 interrupts
	TR2     = 0x01U;                     // Start Timer2

	SFRPAGE = SFRPAGE_save;
}
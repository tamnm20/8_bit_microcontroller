#include "GPIO.h"

#define SYSCLK       24000000        // SYSCLK frequency in Hz

//SBIT(GREEN, SFR_P2, 1);
//SBIT(YELLOW, SFR_P2, 0);
//SBIT(BT, SFR_P1, 2);
//SBIT(SW, SFR_P1, 4);
//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
//U8 dem = 0;
void OSCILLATOR_Init (void);
//void external_IT(void);
//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------

void(*Function_poiter)() = 0;

void main (void)
{
	SFRPAGE = ACTIVE_PAGE;
	PCA0MD &= ~0x40;                    // Disable the watchdog timer
	
	SFRPAGE = CONFIG_PAGE;
	OSCICN = 0x87;
	SFRPAGE = ACTIVE_PAGE;
	
	PORT_Init();
	
	if(P1 == 0xFF)
	{
		Function_poiter = (void*)0x4000;
	}
	else
	{
		Function_poiter = (void*)0x6000;
	}
	Function_poiter();
//	while (1)
//	{

//	}
}

void OSCILLATOR_Init (void)
{
	U8 SFRPAGE_save = SFRPAGE;
	SFRPAGE = CONFIG_PAGE;

	OSCICN = 0x87;

	SFRPAGE = SFRPAGE_save;
}





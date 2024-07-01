#include <compiler_defs.h>             // Compiler declarations
#include <C8051F580.h>
#include "F580_FlashPrimitives.h"
#include "F580_FlashUtils.h"

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------
#define SYSCLK       24000000        // SYSCLK frequency in Hz
SBIT(GREEN, SFR_P2, 1);
//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
void OSCILLATOR_Init (void);
void PORT_Init (void);
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
		FLASH_Copy_VTTB (0x0003, 0x4003, 187);
		Function_poiter = (void*)0x4000;
	}
	else
	{
		FLASH_Copy_VTTB (0x0003, 0x6003, 187);
		Function_poiter = (void*)0x6000;
	}

	Function_poiter();
	while (1)
	{
//		if(P1 == 0xFB)
//		{
//			Function_poiter = (void*)0x10000;
//		}
	}
}

void PORT_Init (void)
{
	U8 SFRPAGE_save = SFRPAGE;
	SFRPAGE = CONFIG_PAGE;

	P1MDIN |= 0xFF;                    // Enable LED as a push-pull output
	P1SKIP  |= 0xFF;                    // Skip the LED pin on the crossbar

	P2MDOUT |= 0x07;                   
	P2SKIP  |= 0x07;                   


	XBR2     = 0x40;                    // Enable crossbar and weak pull-ups

	SFRPAGE = SFRPAGE_save;
}


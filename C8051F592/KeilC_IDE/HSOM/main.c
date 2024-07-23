#include <compiler_defs.h> // Compiler declarations
#include <C8051F580.h>
#include <string.h>
//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------
#define SYSCLK 24000000 // SYSCLK frequency in Hz
SBIT(TEST, P1, 3);
//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
void SYSTEM_Init(void);
void PORT_Init(void);
void PCA0_Init(void);
void delay(U16 ms);
void delay_test(U16 test);
// #define ISR_PCA0
//----------------------------------------------------------------------------
//  MAIN Routine
//-----------------------------------------------------------------------------
void main(void)
{
	SFRPAGE = ACTIVE_PAGE;
	PCA0MD &= ~(1 << 6); // Disable the watchdog timer
	SYSTEM_Init();		 // Configure system clock
	PORT_Init();		 // Congigure pin
	PCA0_Init();
	EA = 1; // Enable global interrupts
	while (1)
	{
#ifndef ISR_PCA0
		if (CCF0)
		{
			CCF0 = 0;
			PCA0L = 0; // Reset PCA Counter Value to 0x0000
		}
#endif
	}
}

void SYSTEM_Init(void)
{
	U8 SFRPAGE_save = SFRPAGE;
	SFRPAGE = CONFIG_PAGE;
	CLKSEL &= ~(3 << 0);		   // choose internal oscillator
	OSCICN |= (2 << 6) | (7 << 0); // config clock internal oscillator devided by 1
	SFRPAGE = SFRPAGE_save;
}
void PORT_Init(void)
{
	U8 SFRPAGE_save = SFRPAGE;
	SFRPAGE = CONFIG_PAGE;

	P1MDOUT |= (1 << 3); // Push-pull
	P0SKIP = 0xFF;
	P1SKIP = 0x07;
	XBR1 = 1 << 2;
	XBR2 |= (1 << 6); // Enable crossbar and weak pull-ups

	SFRPAGE = SFRPAGE_save;
}

void PCA0_Init(void)
{
	
	U8 SFRPAGE_save = SFRPAGE;
	SFRPAGE = ACTIVE_PAGE;
	PCA0CN = 0x00;		// Stop counter; clear all flags
	PCA0MD |= (1 << 3); // PCA0 pulse select system clock
	PCA0CPL0 = 0x03;
	PCA0CPM0 = 0x4D;
	EIE1 |= 0x08;
	PCA0CN |= 1 << 6; //  PCA0 Counter/Timer enabled.
	SFRPAGE = SFRPAGE_save;
}
#ifdef ISR_PCA0
INTERRUPT(PCA0_ISR, INTERRUPT_PCA0)
{
	CCF0 = 0;
	PCA0L = 0; // Reset PCA Counter Value to 0x0000
	PCA0H = 0;
}
#endif

/*
L� do v� sao lai 430k hz l� max :
	+ chu k� max l� 12Mhz
	+ moi lan vao ngat thi mat 27 chu ki xung
*/

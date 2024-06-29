//-----------------------------------------------------------------------------
// F580_Blinky.c
//-----------------------------------------------------------------------------
// Copyright (C) 2008 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This program flashes the green LED on the C8051F580 target board about
// five times a second using the interrupt handler for Timer2.
//
//
// How To Test:
//
// 1) Download code to the 'F580 target board
// 2) Ensure that the P1.3 pins are shorted together on the J19 header
// 3) Run the program.  If the LED flashes, the program is working
//
//
// Target:         C8051F580 (C8051F580-TB)
// Tool chain:     Raisonance / Keil / SDCC
// Command Line:   None
//
// Release 1.1 / 11 MAR 2010 (GP)
//    -Tested with Raisonance
//
// Release 1.0 / 21 JUL 2008 (ADT)
//    - Initial Revision
//
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "si_toolchain.h"
#include <compiler_defs.h>             // Compiler declarations
#include <C8051F580.h>
#include "stdint.h"

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------
#define SYSCLK       24000000        // SYSCLK frequency in Hz
SBIT(LED, SFR_P1, 3);                 // LED='1' means ON
SBIT(GREEN, SFR_P2, 1);
//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
uint32_t num = 0;
void OSCILLATOR_Init (void);
void PORT_Init (void);
void TIMER2_Init (uint16_t counts);
void delayms(int time);
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
	while (1)
	{

	}
}

void OSCILLATOR_Init (void)
{
   uint8_t SFRPAGE_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;

   OSCICN = 0x87;

   SFRPAGE = SFRPAGE_save;
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


void TIMER2_Init (uint16_t counts)
{
   uint8_t SFRPAGE_save = SFRPAGE;
   SFRPAGE = ACTIVE_PAGE;

   TMR2CN  = 0x00;                     // Stop Timer2; Clear TF2;
                                       // use SYSCLK/12 as timebase
   CKCON  &= ~0x60;                    // Timer2 clocked based on T2XCLK;

   TMR2RL  = -counts;                  // Init reload values
   TMR2    = 0xFFFF;                   // Set to reload immediately
   ET2     = 1;                        // Enable Timer2 interrupts
   TR2     = 1;                        // Start Timer2

   SFRPAGE = SFRPAGE_save;
}

INTERRUPT(Timer2_ISR, INTERRUPT_TIMER2)
{
   TF2H = 0;                           // Clear Timer2 interrupt flag
   num++;
}
//void Timer2_ISR(void)
//{
//   TF2H = 0;                           // Clear Timer2 interrupt flag
//   num++;	
//}
void delayms(int time)
{
   //volatile int tmp = num;
   num = 0;
   while(num < time);
}

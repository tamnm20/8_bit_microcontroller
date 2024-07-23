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
//#include <C8051F580_defs.h>            // SFR declarations
#include <C8051F580.h>
#include "stdint.h"

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------
#define SYSCLK       24000000        // SYSCLK frequency in Hz
SBIT(YELLOW, SFR_P2, 0);
SBIT(GREEN, SFR_P2, 1);
//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
uint32_t num = 0;
void OSCILLATOR_Init (void);
void PORT_Init (void);
void TIMER2_Init (uint16_t counts);
void delayms(int time);
void delay(int time);
//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------
void main (void)
{
   SFRPAGE = ACTIVE_PAGE;

   PCA0MD &= ~0x40;                    // Disable the watchdog timer

   OSCILLATOR_Init();                 // Configure system clock
   PORT_Init ();                       // Initialize crossbar
   TIMER2_Init (SYSCLK / 12 / 1000);     // Init Timer2 to generate interrupts

   EA = 1;                             // Enable global interrupts
		P2 =1;
   while (1)
   {
      YELLOW = !YELLOW;
      //_nop_();
      delayms(100);
			//delay(1000);  
   }                          // Spin forever
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
   uint8_t SFRPAGE_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;

   P1MDOUT |= 0x08;                    // Enable LED as a push-pull output
   P1SKIP  |= 0x08;                    // Skip the LED pin on the crossbar

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
void delayms(int time)
{
   //volatile int tmp = num;
   num = 0;
   while(num < time);
}
void delay(int time)
{
	volatile int i,j;
	for(i=0;i<time;i++){
		for(j=0;j<885;j++){
			_nop_();
		}
	}
}
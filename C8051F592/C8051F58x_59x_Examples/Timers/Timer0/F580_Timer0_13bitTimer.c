//-----------------------------------------------------------------------------
// F580_Timer0_13bitReloadTimer.c
//-----------------------------------------------------------------------------
// Copyright (C) 2008 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This program flashes the green LED on the C8051F580 target board about
// once a second using the interrupt handler for Timer0.
//
//
// How To Test:
//
// 1) Download code to the 'F580 target board
// 2) Ensure that the P1.3 pins are shorted together on the J19 header
// 3) Run the program.  If the LED flashes, the program is working
//
//
// Target:         C8051F580 (Side A of a C8051F580-TB)
// Tool chain:     Keil C51 8.0 / Keil EVAL C51
// Command Line:   None
//
// Release 1.0 / 21 JUL 2008 (ADT)
//    - Initial Revision
//
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <compiler_defs.h>
#include <C8051F580_defs.h>            // SFR declarations

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

#define SYSCLK       24000000/8        // SYSCLK frequency in Hz

#define BLINK_RATE   8                 // Number of 131.072 ms intervals 
                                       // between toggling the LED pin
                                       // 8 intervals is about 1 per second

//-----------------------------------------------------------------------------
// Pin Definitions
//-----------------------------------------------------------------------------

SBIT (LED, SFR_P1, 3);                 // LED==1 means ON

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------

void OSCILLATOR_Init (void);           
void PORT_Init (void);                 
void TIMER0_Init (void);               

INTERRUPT_PROTO (Timer0_ISR, INTERRUPT_TIMER0);

//-----------------------------------------------------------------------------
// main() Routine
//-----------------------------------------------------------------------------

void main (void)
{
   SFRPAGE = ACTIVE_PAGE;              // Set SFRPAGE for PCA0MD

   PCA0MD &= ~0x40;                    // Disable the watchdog timer

   OSCILLATOR_Init ();                 // Configure system clock
   PORT_Init ();                       // Initialize crossbar
   TIMER0_Init ();                     // Initialize Timer0

   EA = 1;                             // Enable global interrupts

   while (1);                          // Spin forever
}

//-----------------------------------------------------------------------------
// Initialization Subroutines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// OSCILLATOR_Init
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configure the internal oscillator to maximum internal frequency / 8, which
// is 3 MHz
//
//-----------------------------------------------------------------------------
void OSCILLATOR_Init (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;

   OSCICN = 0x84;                      // Internal freq / 8

   SFRPAGE = SFRPAGE_save;
}

//-----------------------------------------------------------------------------
// PORT_Init
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configure the Crossbar and GPIO ports.
//
// P1.3 - digital  push-pull   LED
//
//-----------------------------------------------------------------------------
void PORT_Init (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;

   P1MDOUT |= 0x08;                    // Enable LED as a push-pull output
   P1SKIP  |= 0x08;                    // Skip the LED pin on the crossbar

   XBR2     = 0x40;                    // Enable crossbar and weak pull-ups

   SFRPAGE = SFRPAGE_save;
}

//-----------------------------------------------------------------------------
// TIMER0_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configure Timer0 to 13-bit mode (mode 0) and generate an interrupt
// every 8192 Timer0 cycles using SYSCLK/48 as the Timer0 time base.
//
// With the system clock at 3 MHz, the Timer0 time base is 62.5 kHz.  Timer0
// will overflow every 131.072 ms
//
//-----------------------------------------------------------------------------
void TIMER0_Init(void)
{
   // No need to set SFRPAGE as all registers accessed in this function
   // are available on all pages

   TH0 = 0x00;                         // Init Timer0 reload register
   TL0 = 0x00;                         // Set the intial Timer0 value
   
   TMOD  = 0x00;                       // Timer0 in 13-bit mode
   CKCON = 0x02;                       // Timer0 uses a 1:48 prescaler
   ET0   = 1;                          // Timer0 interrupt enabled
   TCON  = 0x10;                       // Timer0 ON
}


//-----------------------------------------------------------------------------
// Interrupt Service Routines
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Timer0_ISR
//-----------------------------------------------------------------------------
//
// This routine changes the state of the LED whenever Timer0 overflows.
//
//-----------------------------------------------------------------------------

INTERRUPT(Timer0_ISR, INTERRUPT_TIMER0)
{
   // The Timer0 interrupt flag is automatically cleared by vectoring to
   // the Timer0 ISR

   static U8 count = 0;
   count++;                            // Increment when an interrupt occurs

   if (count == BLINK_RATE)
   {
      LED = !LED;                      // Change state of LED
      count = 0;                       // Clear the counter
   }
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------

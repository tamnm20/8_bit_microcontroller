#include <compiler_defs.h>             // Compiler declarations
#include <C8051F580.h>
#include <string.h>
//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------
#define SYSCLK       24000000        // SYSCLK frequency in Hz
SBIT(TEST, P1, 3);
//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
void SYSTEM_Init (void);
void PORT_Init (void);
void PCA0_Init (void);
void delay(U16 ms);
void delay_test(U16 test);
//----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------
void main (void)
{
		SFRPAGE = ACTIVE_PAGE;
		PCA0MD &= ~(1 << 6);                   // Disable the watchdog timer
		SYSTEM_Init();                 				// Configure system clock
		PORT_Init ();                       		// Congigure pin
		PCA0_Init();
		EA = 1;                             		// Enable global interrupts
   while (1)
   {
   }                        
}
void SYSTEM_Init(void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;
	 CLKSEL &= ~(3<< 0) ; 			// choose internal oscillator   
   OSCICN |= (2<<6) | (7<<0); // congig clock internal oscillator devided by 1
   SFRPAGE = SFRPAGE_save;
}
void PORT_Init (void)
{
			U8 SFRPAGE_save = SFRPAGE;
			SFRPAGE = CONFIG_PAGE;
			
			P1MDOUT |= (1<<3); 		// Push-pull
			P0SKIP    = 0xFF;
			P1SKIP    = 0x07;
			XBR1    = 1<<2 ;
			//XBR1    = 1<<1;
			XBR2    |= (1<<6);   	// Enable crossbar and weak pull-ups

			SFRPAGE = SFRPAGE_save;
}

void PCA0_Init (void){
			U8 SFRPAGE_save = SFRPAGE;
			SFRPAGE = ACTIVE_PAGE;
			PCA0CN = 0x00;          // Stop counter; clear all flags
			PCA0MD |= (1 << 3); // PCA0 pulse select system clock/12
			PCA0CPM0 |= (1<<2) | (1<<1) ; // 
			PCA0CPH0 = ((SYSCLK) / ((U32) 2* (U32)4000000));//a write to this register will set the module's ECOMn bit to a 1
			PCA0CN |= 1 << 6; //  PCA0 Counter/Timer enabled.
			SFRPAGE = SFRPAGE_save;
}



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

#define CYCLE 4000
#define PWM 33

//----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------
void main (void)
{
		SFRPAGE = ACTIVE_PAGE;
		PCA0MD &= ~(1 << 6);                  	// Disable the watchdog timer
		SYSTEM_Init();                 					// Configure system clock
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
   OSCICN |= (2<<6) | (7<<0); // config clock internal oscillator devided by 1
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
			XBR2    |= (1<<6);   	// Enable crossbar and weak pull-ups

			SFRPAGE = SFRPAGE_save;
}

void PCA0_Init (void){
			U16 L_pwm = (65535 - CYCLE)+(((CYCLE)/100)*PWM );
			U8 SFRPAGE_save = SFRPAGE;
			SFRPAGE = ACTIVE_PAGE;
			PCA0CN = 0x00;					// Stop counter; clear all flags
			PCA0MD &= ~(7 << 1); 		// PCA0 pulse select system clock/12
			PCA0 = -CYCLE;          // Init value count 
			PCA0CP0 = L_pwm;				// Init value match
			PCA0CPM0 |= (1 << 7) 		// select 16bit PWM	
									|(1 << 6)
									|(1 << 1); 	// enable mode PWM 
			PCA0MD |= (1 << 0) ; 		// enable interrupt when CF is set 
			EIE1 |= 0x08; 
			PCA0CN |= 1 << 6; 			//  PCA0 Counter/Timer enabled.
			SFRPAGE = SFRPAGE_save;
	
}
INTERRUPT(PCA0_ISR, INTERRUPT_PCA0)
{
	CF = 0;
	PCA0 = -CYCLE;	
}


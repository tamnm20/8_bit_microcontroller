#include <compiler_defs.h>             // Compiler declarations
#include <C8051F580.h>
#include <string.h>
//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------
#define SYSCLK       24000000        // SYSCLK frequency in Hz
//#define ISR_PCA0
SBIT(TEST, P1, 3);
//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
U32 G_count = 0;
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
		 TEST = ~TEST;
		 delay(200);
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
			P1SKIP  |= (1<<3);		// Skip P1.3
	
			XBR2    |= (1<<6);   	// Enable crossbar and weak pull-ups
	
			SFRPAGE = SFRPAGE_save;
}

#ifndef ISR_PCA0 
void PCA0_Init (void){
			U8 SFRPAGE_save = SFRPAGE;
			SFRPAGE   = CONFIG_PAGE;
			//PCA0PWM   = 1<<6;
			PCA0PWM |= (3 << 0);
			SFRPAGE = ACTIVE_PAGE;
			PCA0CN = 0x00;          // Stop counter; clear all flags
			PCA0MD &= ~(7 << 1); // PCA0 pulse select system clock/12
			PCA0L = 0x2f ;
			EIE1 |= (1 <<3 );                       // Enable PCA interrupts
			PCA0CN |= 1 << 6; //  PCA0 Counter/Timer enabled.
			SFRPAGE = SFRPAGE_save;
}
void delay(U16 ms){
			int i = 0 ; 
			U8 SFRPAGE_save = SFRPAGE;
			SFRPAGE = CONFIG_PAGE;
			for( i = 0 ; i < ms ; ){
				if(((PCA0PWM >> 5)&1)==1){
					PCA0PWM &= ~(1<<5);
					i++;
					PCA0L = 0x2f ;
				}
		}
			SFRPAGE = SFRPAGE_save;
}
#else
void PCA0_Init (void){
			U8 SFRPAGE_save = SFRPAGE;
			SFRPAGE   = CONFIG_PAGE;
			PCA0PWM   = 1<<6;
			PCA0PWM |= (3 << 0);
			SFRPAGE = ACTIVE_PAGE;
			PCA0CN = 0x00;          // Stop counter; clear all flags
			PCA0MD &= ~(7 << 1); // PCA0 pulse select system clock/12
			PCA0L = 0x2f ;
			EIE1 |= (1 <<3 );  // Enable PCA interrupts
			PCA0CN |= 1 << 6; //  PCA0 Counter/Timer enabled.
			SFRPAGE = SFRPAGE_save;
}
void delay(U16 ms){
			G_count =0 ; 
			while(G_count < ms);
}
INTERRUPT(PCA0_ISR, INTERRUPT_PCA0){
		U8 SFRPAGE_save = SFRPAGE;
    PCA0L = 0x2F; 
    G_count++;
		SFRPAGE = CONFIG_PAGE;
		PCA0PWM &= ~(1<<5);
		SFRPAGE = SFRPAGE_save;
}

#endif

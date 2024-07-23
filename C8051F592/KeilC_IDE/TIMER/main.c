#include <compiler_defs.h>             // Compiler declarations
#include <C8051F580.h>
#include <string.h>
//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------
#define SYSCLK       24000000        // SYSCLK frequency in Hz
#define ISR_PCA0
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
			SFRPAGE = ACTIVE_PAGE;
			PCA0CN = 0x00;          // Stop counter; clear all flags
			PCA0MD &= ~(7 << 1); // PCA0 pulse select system clock/12
			PCA0H = 0xf8;
			PCA0L = 0x2f ;
			PCA0CN |= 1 << 6; //  PCA0 Counter/Timer enabled.
			SFRPAGE = SFRPAGE_save;
}
void delay(U16 ms){
			int i = 0 ; 
			for( i = 0 ; i < ms ; ){
				if(CF == 1){
					CF = 0 ;
					i++;
					PCA0H = 0xf8;
					PCA0L = 0x2f ;
				}
		}
}
#else
void PCA0_Init (void){
			U8 SFRPAGE_save = SFRPAGE;
			SFRPAGE = ACTIVE_PAGE;
			PCA0CN = 0x00;          // Stop counter; clear all flags
			PCA0MD &= ~(7 << 1); // PCA0 pulse select system clock/12
			PCA0MD |= (1 << 0); // PCA0 Counter/Timer Overflow Interrupt Enable
			PCA0H = 0xf8;
			PCA0L = 0x2f ;
			  EIE1 |= (1 <<3 );                       // Enable PCA interrupts
			PCA0CN |= 1 << 6; //  PCA0 Counter/Timer enabled.
			SFRPAGE = SFRPAGE_save;
}
void delay(U16 ms){
			G_count =0 ; 
			while(G_count < ms);
}
INTERRUPT(PCA0_ISR, INTERRUPT_PCA0){
    PCA0H = 0xF8; 
    PCA0L = 0x2F; 
    CF = 0; 
    G_count++;
}

#endif
void delay_test(U16 test){
			U32 i = 0, j = 0 ;
		for( i = 0 ; i < test ; i ++){
			for(j = 0 ; j < 1000 ; j ++);
		}
}
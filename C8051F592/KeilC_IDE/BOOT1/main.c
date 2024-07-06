#include <compiler_defs.h>             // Compiler declarations
#include <C8051F580.h>
//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------
#define SYSCLK       24000000        // SYSCLK frequency in Hz
SBIT(SW7,			P1, 4);
//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
U32 G_count = 0;
void SYSTEM_Init (void);
void PORT_Init (void);
U16 main1 (void);
//extern void START_APPLICATION_60(void);
//extern void START_APPLICATION_40(void);
//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------
void (*PTR_FUNCTION)() = 0;
U16 addr = 0 ;
void main (void)
{		
	SFRPAGE = ACTIVE_PAGE;
	PCA0MD &= ~(1 << 6);
	PORT_Init ();
	EA = 1;
		if(SW7==0){
			//START_APPLICATION_60();
			PTR_FUNCTION=0x6000;
		}
		else{
			//START_APPLICATION_40();
			PTR_FUNCTION=0x4000;
		}
	//PTR_FUNCTION = (void*)addr;
	PTR_FUNCTION();                    
}
U16 main1(void){
	SFRPAGE = ACTIVE_PAGE;
  PCA0MD &= ~(1 << 6);                   // Disable the watchdog timer   SYSTEM_Init();                 				// Configure system clock
  PORT_Init ();                       		// Initialize crossbar
	EA = 1;
	if(SW7==0){
			addr=0x6000;
		}
		else{
			addr=0x4000;
		}
		
	return addr;
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
		P1MDIN  |= (1<<4); 		// P1.4 input digital
		P1SKIP  |= (1<<4);		// Skip P1.4
		XBR2    |= (1<<6);   	// Enable crossbar and weak pull-ups
   SFRPAGE = SFRPAGE_save;
}

//void delay(U32 ms){
//		U32 i = 0, j = 0 ;
//		for( i = 0 ; i < ms ; i ++){
//			for(j = 0 ; j < 1000 ; j ++);
//		}
//}
//INTERRUPT(Timer2_ISR, INTERRUPT_TIMER2)
//{
//   TF2H = 0;                           // Clear Timer2 interrupt flag
//   G_count++;
//}




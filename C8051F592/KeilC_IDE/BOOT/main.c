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
//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------
void (*PTR_FUNCTION)() = 0;
U16 addr = 0 ;

void main (void)
{
  SFRPAGE = ACTIVE_PAGE;
  PCA0MD &= ~(1 << 6);                   // Disable the watchdog timer
  SYSTEM_Init();                 				// Configure system clock
  PORT_Init ();                       		// Initialize crossbar
	 EA = 1;                             		// Enable global interrupts
		if(SW7==0){
			PSW|= 0x02;
     	PTR_FUNCTION=0x4000;
		}
		else{
			PSW&=~ 0x02;
			PTR_FUNCTION=0x6000;
		}
		PTR_FUNCTION();   
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






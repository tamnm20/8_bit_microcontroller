#include <compiler_defs.h>
#include <C8051F580_defs.h>            // SFR declarations
SBIT (LED, SFR_P2, 0);                 // LED==1 means ON
SBIT (LED1, SFR_P2, 1);

void OSCILLATOR_Init (void);
void PORT_Init (void);
void TIMER0_Init (void);
void Delay(unsigned int t);

void main (void)
{
SFRPAGE = ACTIVE_PAGE;
   PCA0MD &= ~0x40;                    // Clear watchdog timer enable
   OSCILLATOR_Init ();                 // Initialize Oscillator
   TIMER0_Init ();                     // Initialize the Timer2
   PORT_Init ();                       // Initialize Ports
   EA = 1;                             // Enable global interrupts
  

     while (1){
   P2 = ~P2 ;

   Delay(500);
   }   
   TMOD &= 0xF0;
   TMOD  |= 0x10; 
}

void Delay(unsigned int t){
do{
         TL0 = 0x1F;
        TH0 = 0xD1;
      TR0=1; // bat dau dem 
      while(!TF0);
      TR0 = 0;// ngung dem 
      TF0 = 0;;
   t--;
   }
   while(t != 0);
}

void PORT_Init (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;

   XBR2 = 0x40;                        // Enable crossbar
   P2MDOUT = 0x03;                     // Set LED to push-pull

   SFRPAGE = SFRPAGE_save;
}

void OSCILLATOR_Init (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;

   OSCICN = 0x86;

   SFRPAGE = SFRPAGE_save;
}
void TIMER0_Init(void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = ACTIVE_PAGE;
   //OSCICN = 0x84;
   TMOD  = 0x01;                       // Timer0 in 16-bit mode
   //CKCON = 0x02;                       // Timer0 uses a 1:48 prescaler
   ET0   = 1;                          // Timer0 interrupt enabled
   TCON  = 0x10;                       // Timer0 ON

   SFRPAGE = SFRPAGE_save;
}
#include <compiler_defs.h>
#include <C8051F580_defs.h>            // SFR declarations

#define SYSCLK      24000000           // SYSCLK frequency in Hz
SBIT (LED, SFR_P2, 0);                 // LED==1 means ON
SBIT (LED1, SFR_P2, 1);

void OSCILLATOR_Init (void);
void PORT_Init (void);
void TIMER0_Init (void);
void Delay(unsigned int t);
void T0_Wait_ms (U8 ms);

void main (void)
{
SFRPAGE = ACTIVE_PAGE;
   PCA0MD &= ~0x40;                    // Clear watchdog timer enable
   OSCILLATOR_Init ();                 // Initialize Oscillator
   TIMER0_Init ();                     // Initialize the Timer2
   PORT_Init ();                       // Initialize Ports
   EA = 1;                             // Enable global interrupts
   P2 =0;

   while (1){
	   P2 = ~P2 ;

	   //Delay(50);
	   T0_Wait_ms(1);
   }   
   // TMOD &= 0xF0;
   // TMOD  |= 0x10; 
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

   //XBR2 = 0x40;                        // Enable crossbar
   P2MDOUT = 0x03;                     // Set LED to push-pull

   SFRPAGE = SFRPAGE_save;
}

void OSCILLATOR_Init (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;

   //OSCICN = 0x86;
   OSCICN |= 0x07;

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


// 16 bit C/T 
void T0_Wait_ms (U8 ms)
{
   // All registers are on all pages, so no need to set SFR page

   TCON &= ~0x30;                      // Stop Timer0; Clear TF0
   TMOD &= ~0x0f;                      // 16-bit free run mode
   TMOD |=  0x01;

   CKCON |= 0x04;                      // Timer0 counts SYSCLKs

   while (ms) {
      TR0 = 0;                         // Stop Timer0
      TH0 = -(S8)(SYSCLK/1000 >> 8);   // Overflow in 1ms
      TL0 = -(S8)(SYSCLK/1000);
      TF0 = 0;                         // Clear overflow indicator
      TR0 = 1;                         // Start Timer0
      while (!TF0);                    // Wait for overflow
      ms--;                            // Update ms counter
   }

   TR0 = 0;                            // Stop Timer0
}

// 8 bit C/T Auto reload
// void T0_Wait_ms (U8 ms)
// {
   // All registers are on all pages, so no need to set SFR page

   // TCON &= ~0x30;                      // Stop Timer0; Clear TF0
   // TMOD &= ~0x0f;                      // 16-bit free run mode
   // TMOD |=  0x01;

   // CKCON |= 0x04;                      // Timer0 counts SYSCLKs

   // while (ms) {
      // TR0 = 0;                         // Stop Timer0
      // TH0 = -(S8)(SYSCLK/1000 >> 8);   // Overflow in 1ms
      // TL0 = -(S8)(SYSCLK/1000);
      // TF0 = 0;                         // Clear overflow indicator
      // TR0 = 1;                         // Start Timer0
      // while (!TF0);                    // Wait for overflow
      // ms--;                            // Update ms counter
   // }

   // TR0 = 0;                            // Stop Timer0
// }


// void TIMER0_Init (void)
// {
   // No need to set SFRPAGE as all registers accessed in this function
   // are available on all pages

   // TH0 = 0x06;                         // Init Timer0 reload register
   // TL0 = TH0;                          // Set the intial Timer0 value

   // TMOD  = 0x02;                       // Timer0 in 8-bit reload mode
   // CKCON = 0x02;                       // Timer0 uses a 1:48 prescaler
   // ET0   = 1;                          // Timer0 interrupt enabled
   // TCON  = 0x10;                       // Timer0 ON
// }

// INTERRUPT(Timer0_ISR, INTERRUPT_TIMER0)
// {
   // The Timer0 interrupt flag is automatically cleared by vectoring to
   // the Timer0 ISR

   // static U8 count = 0;
   // count++;                            // Increment when an interrupt occurs

   // if (count == 250)
   // {
      // LED = !LED;                      // Change state of LED
      // count = 0;                       // Clear the counter
   // }
// }

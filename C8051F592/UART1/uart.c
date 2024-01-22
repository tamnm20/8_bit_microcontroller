//-----------------------------------------------------------------------------
// F580_UART1_STDIO.c
//-----------------------------------------------------------------------------
// Copyright 2008 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This program demonstrates how to configure the C8051F580 to use routines
// in STDIO.h to write to and read from the UART interface.  The program
// reads a character using the STDIO routine getkey(), outputs that character
// to the screen, and then outputs the ASCII hex value of that character.
//
//
// How To Test:
//
// 1) Ensure that jumpers are placed on J? of the C8051F580 target board
//    that connect P0.4 to the TX signal, and P0.5 to the RX field.
// 2) Connect USB cable from the development board to a PC
// 3) Specify the target baudrate in the constant <BAUDRATE>.
// 4) Open Hyperterminal, or a similar program, and connect to the target
//    board's USB port (virtual com port).
// 5) Download and execute code to an 'F580 target board.
//
//
// Target:         C8051F580
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
#include <stdio.h>

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------

#define SYSCLK      24000000           // SYSCLK frequency in Hz
#define BAUDRATE      115200           // Baud rate of UART in bps

//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------

void SYSCLK_Init (void);
void OSCILLATOR_Init (void);
void UART1_Init(void);
void PORT_Init (void);
void TIMER0_Init (void);
void T0_Wait_ms (U8 ms);
void UART1_SendByte(char data1);

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------

void main (void)
{

   SFRPAGE = ACTIVE_PAGE;

   PCA0MD &= ~0x40;                    // Disable watchdog timer
   PORT_Init();                        // Initialize Port I/O
   //OSCILLATOR_Init();
   
   SYSCLK_Init (); 
   TIMER0_Init ();  
   //T0_Wait_ms(1);

	UART1_Init();
   SFRPAGE = ACTIVE2_PAGE;             // Switch page for UART1 communication
   //P2 =0;
   while (1)
   {
		UART1_SendByte('a');
	   //P2 = ~P2 ;

	   	T0_Wait_ms(10);
		UART1_SendByte('b');
		T0_Wait_ms(10);
   }
}


void UART1_SendByte(char data1) {
    // // Chờ cho đến khi TX1 Ready
    
    
    // // Đặt TI1 về 0 để chuẩn bị cho lần gửi tiếp theo
    
    // Ghi dữ liệu vào thanh ghi truyền (SBUF1)
    // while (TI1 !=0);
	// SBUF1 = 'Q';

	// while (!TI1);
	// TI1 = 0;
	while (!TI1);
	TI1 = 0;
	SBUF1 = (U8)data1;
}



//-----------------------------------------------------------------------------
// Initialization Subroutines
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// PORT_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configure the Crossbar and GPIO ports.
//
// P0.4   digital   push-pull    UART1 TX
// P0.5   digital   open-drain   UART1 RX
//
//-----------------------------------------------------------------------------
// void PORT_Init (void)
// {
   // U8 SFRPAGE_save = SFRPAGE;
   // SFRPAGE = CONFIG_PAGE;

   // P0MDOUT |= 0x10;                    // Enable UART1 TX as push-pull output
   // P0SKIP  = 0x0F;                     // Skip to P0.4

   // XBR2    = 0x42;                     // Enable UART1 on P0.4(TX) and P0.5(RX)
										  //Enable crossbar and weak pull-ups
   // SFRPAGE = SFRPAGE_save;
// }

// void PORT_Init (void)
// {
   // U8 SFRPAGE_save = SFRPAGE;
   // SFRPAGE = CONFIG_PAGE;

    // P2MDOUT   = 0x07;
	 // P0SKIP    = 0xFF;
	 // P1SKIP    = 0xFF;

     // XBR2    = 0x42;                     // Enable UART1 on P0.4(TX) and P0.5(RX)
                                       // // Enable crossbar and weak pull-ups
   // SFRPAGE = SFRPAGE_save;
// }

void PORT_Init (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;

   //XBR2 = 0x40;                        // Enable crossbar
   P2MDOUT = 0x03;                     // Set LED to push-pull
    P0SKIP    = 0xFF;
    P1SKIP    = 0xFF;
    XBR2      = 0x42;	

   SFRPAGE = SFRPAGE_save;
}

//-----------------------------------------------------------------------------
// SYSCLK_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This routine initializes the system clock to use the internal oscillator
// at its maximum frequency.
// Also enables the Missing Clock Detector.
//-----------------------------------------------------------------------------

void SYSCLK_Init (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;

   OSCICN |= 0x87;                     // Configure internal oscillator for
                                       // its maximum frequency
   RSTSRC  = 0x04;                     // Enable missing clock detector

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

//-----------------------------------------------------------------------------
// UART1_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configure the UART1 using Timer1, for <BAUDRATE> and 8-N-1.
//-----------------------------------------------------------------------------

void UART1_Init (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = ACTIVE2_PAGE;

   SCON1 = 0x10;                       // SCON1: 8-bit variable bit rate
                                       //        level of STOP bit is ignored
                                       //        RX enabled
                                       //        ninth bits are zeros
                                       //        clear RI0 and TI0 bits

      TH1 = -(SYSCLK / BAUDRATE / 2);
      CKCON &= ~0x0B;                  // T1M = 1; SCA1:0 = xx
      CKCON |=  0x08;
 
   TL1 = TH1;                          // Init Timer1
   TMOD &= ~0xF0;                      // TMOD: timer 1 in 8-bit autoreload
   TMOD |=  0x20;
   TR1 = 1;                            // START Timer1

   TI1 = 1;                            // Indicate TX0 ready (SCON1)

   SFRPAGE = SFRPAGE_save;
}

void TIMER0_Init(void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = ACTIVE_PAGE;

   TMOD  |= 0x01;                       // Timer0 in 16-bit mode
   ET0   = 1;                          // Timer0 interrupt enabled
   TCON  |= 0x10;                       // Timer0 ON

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
#if 0
#ifdef SDCC

// SDCC does not include a definition for putchar(), which is used in printf()
// and so it is defined here.  The prototype does not need to be explicitly
// defined because it is provided in stdio.h

//-----------------------------------------------------------------------------
// putchar
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : character to send to UART
//
// This function outputs a character to the UART.
//-----------------------------------------------------------------------------
void putchar (char output)
{
   if (output == '\n')
   {
      while (!TI0);
      TI0 = 0;
      SBUF0 = 0x0D;
   }
   while (!TI0);
   TI0 = 0;
   SBUF0 = output;
}

// SDCC does not include a definition for getkey(), and so it is defined here

//-----------------------------------------------------------------------------
// getkey
//-----------------------------------------------------------------------------
//
// Return Value : character received from UART
// Parameters   : None
//
// This function returns a character received from the UART
// Assumes SFR page has been set correctly by the application
//-----------------------------------------------------------------------------
U8 getkey (void)
{
   U8 received;

   while (!RI0);                       // Wait for character to be received
   received = SBUF0;                   // Read it
   RI0 = 0;                            // Clear received data indicator

   return received;
}

#endif
#endif
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
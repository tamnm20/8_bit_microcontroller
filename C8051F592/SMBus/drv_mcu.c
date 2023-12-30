#include "compiler_defs.h"
#include "C8051F580_defs.h"
#include "drv_mcu.h"

void Osc_Init (void)
{
  	SFRPAGE   = CONFIG_PAGE;
  	OSCICN    = 0xC7U;
  	SFRPAGE   = ACTIVE_PAGE;
}

void Port_Init (void)
{
    // P0.0  -  Skipped,     Open-Drain, Digital
    // P0.1  -  Skipped,     Open-Drain, Digital
    // P0.2  -  Skipped,     Open-Drain, Digital
    // P0.3  -  Skipped,     Open-Drain, Digital
    // P0.4  -  Skipped,     Open-Drain, Digital
    // P0.5  -  Skipped,     Open-Drain, Digital
    // P0.6  -  CAN_TX (CAN0), Push-Pull,  Digital
    // P0.7  -  CAN_RX (CAN0), Open-Drain, Digital

    // P1.0  -  SCK  (SPI0), Push-Pull,  Digital
    // P1.1  -  MISO (SPI0), Open-Drain, Digital
    // P1.2  -  MOSI (SPI0), Push-Pull,  Digital
    // P1.3  -  NSS  (SPI0), Push-Pull,  Digital
    // P1.4  -  S_M_PP,	     Push-Pull,  Digital
    // P1.5  -  Skipped,     Open-Drain, Digital
    // P1.6  -  FRAME_SYNC,  Open-Drain, Digital
    // P1.7  -  Skipped,     Open-Drain, Digital

    // P2.0  -  SDA (SMBus), Open-Drain, Digital
    // P2.1  -  SCL (SMBus), Open-Drain, Digital
    // P2.2  -  V_STB, 		 Open-Drain, Digital
    // P2.3  VIDEO_SIG(ADC0) Open-Drain, Analog
    // P2.4  -  ISP_RESET,   Push-Pull,  Digital
    // P2.5  -  CLK_EN,		 Push-Pull,  Digital
    // P2.6  -  FRAME_SYC,   Open-Drain, Digital
    // P2.7  -  1.8V_Enable, Push-Pull,  Digital

    // P3.0  -  Unassigned,  Open-Drain, Digital

    SFRPAGE   = CONFIG_PAGE;
    P2MDIN    = 0xF7U;
    P0MDOUT   = 0x40U;
    P1MDOUT   = 0x1DU;
    P2MDOUT   = 0xB0U;
    P0SKIP    = 0x3FU;
    P1SKIP    = 0xF0U;
    XBR0      = 0x0EU;
    XBR2      = 0x40U;
    SFRPAGE   = ACTIVE_PAGE;
}

void Exinterrupt_Init(void)
{
	SFRPAGE   = CONFIG_PAGE;
	TCON	  = TCON | 0x05U;		// /INT0 and /INT1 are edge triggered
	//IT01CF	= 0x60U;		// INT0 = 1.7, INT1 = 1.6 Port
	EX1		= 0x01U;		// Enable /INT1 interrupts
	SFRPAGE   = ACTIVE_PAGE;
}
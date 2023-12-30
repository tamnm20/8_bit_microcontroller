/*_____ I N C L U D E __________________________________________*/
#include "compiler_defs.h"
#include "C8051F580_defs.h"
#include "Global_Define.h"
#include "drv_mcu.h"
#include "drv_timer.h"

/*--------------------------------------------------------------*/
static SEG_XDATA U8 g_FrameSync= 0x00U;

void Port_Init (void)
{
    // P0.0  -  Skipped,     Open-Drain, Digital
    // P0.1  -  Skipped,     Open-Drain, Digital
    // P0.2  -  SCK  (SPI0), Push-Pull,  Digital
    // P0.3  -  MISO (SPI0), Open-Drain, Digital
    // P0.4  -  MOSI (SPI0), Push-Pull,  Digital
    // P0.5  -  NSS  (SPI0), Push-Pull,  Digital
    // P0.6  -  CAN_TX (CAN0), Push-Pull,  Digital
    // P0.7  -  CAN_RX (CAN0), Open-Drain, Digital

    // P1.0  -  Skipped,     Open-Drain, Digital
    // P1.1  -  Skipped,     Open-Drain, Digital
    // P1.2  -  Skipped,     Open-Drain, Digital
    // P1.3  -  SDA (SMBus), Open-Drain, Digital
    // P1.4  -  SCL (SMBus), Open-Drain, Digital
    // P1.5  -  Unassigned,  Open-Drain, Digital
    // P1.6  -  Unassigned,  Open-Drain, Digital
    // P1.7  -  Unassigned,  Open-Drain, Digital

    // P2.0  -  Unassigned,  Push-Pull,  Digital
    // P2.1  -  Unassigned,  Push-Pull,  Digital
    // P2.2  -  Unassigned,  Open-Drain, Digital
    // P2.3  -  Unassigned,  Push-Pull,  Digital
    // P2.4  -  Unassigned,  Open-Drain, Digital
    // P2.5  -  Unassigned,  Open-Drain, Digital
    // P2.6  -  Unassigned,  Open-Drainl,Digital
    // P2.7  -  Unassigned,  Open-Drain, Digital

    // P3.0  -  Unassigned,  Open-Drain, Digital

    /*SFRPAGE   = CONFIG_PAGE;
    //P1MDIN    = 0xFDU;
	P1MDIN    = 0x7DU;
    P0MDOUT   = 0x74U;
    P2MDOUT   = 0x6CU;
    P0SKIP    = 0x03U;
    P1SKIP    = 0x07U;
    XBR0      = 0x0EU;
    XBR2      = 0x40U;
    SFRPAGE   = ACTIVE_PAGE;*/

    SFRPAGE   = CONFIG_PAGE;
    P0MDOUT   = 0x74;
    P2MDOUT   = 0x0B;
    P0SKIP    = 0x03;
    XBR0      = 0x06;
    XBR2      = 0x40;
    SFRPAGE   = ACTIVE_PAGE;

	LED_STATUS_ERROR = 0x00U;
	LED_STATUS_UPDOWNLOAD = 0x00U;
	MCU_F_ENABLE = 0x00U;
}


void Vdd_Monitor_Init(void)
{
#if defined(VDDMONITOR_ENABLE)
	#if defined(VDDMONITOR_HIGH)
	// High 2.30V VDD Monitor
	VDM0CN = 0x90U;			
	#endif

	#if defined(VDDMONITOR_LOW)
	// Low 1.75V VDD Monitor
	VDM0CN = 0x80U;			
	#endif
#else
	VDM0CN = 0x00U;
#endif
}

void Osc_Init (void)
{
  SFRPAGE   = CONFIG_PAGE;
  OSCICN    = 0xC7U;
  SFRPAGE   = ACTIVE_PAGE;
}

void Rstsrc_Init(void)
{
	RSTSRC   = 0x06U;   
}

void Exinterrupt_Init(void)
{
	SFRPAGE   = CONFIG_PAGE;
	TCON	  = TCON | 0x05U;		// /INT0 and /INT1 are edge triggered
	//IT01CF	= 0x60U;		// INT0 = 1.7, INT1 = 1.6 Port
	EX1		= 0x01U;		// Enable /INT1 interrupts
	SFRPAGE   = ACTIVE_PAGE;
}


void MCU_Reset(void)
{
   RSTSRC = 0x12U;    // Initiate software reset with vdd monitor enabled
}


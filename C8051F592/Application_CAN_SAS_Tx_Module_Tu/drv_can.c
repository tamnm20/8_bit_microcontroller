/*_____ I N C L U D E __________________________________________*/
#include "compiler_defs.h"
#include "C8051F580_defs.h"
#include "Global_Define.h"
#include "drv_can.h"
#include "drv_timer.h"
#include "drv_mcu.h"
#include "mgr_comm.h"
#include "mgr_diag.h"
#include "desc.h"
#include "nm_basic.h"
#include "il_inc.h"
#include <math.h>
#include "can_def.h"
/*--------------------------------------------------------------*/

static SEG_XDATA U8 g_HuType_Interrupt = FALSE;
static SEG_XDATA U8 g_LanguageInfo_Interrupt = FALSE;
SEG_DATA U8 Transfer_Mode = 0x00U;

bit CAN_Error = 0;                     // 0 = No Errors during transmission
U8 KeyData[4] = {0x00,};
            // 1 = Some error(s) occurred
extern SEG_XDATA U8 CAN_Rx_Complete_Flag; 

extern U8 download_type;
SEGMENT_VARIABLE (CAN_Rx_Buf[8], U8, SEG_XDATA);

SEGMENT_VARIABLE (CAN_Tx_Buf[8], U8, SEG_XDATA);
SEGMENT_VARIABLE (TGT_Info[TGT_Enum_End_Value], extern U8, SEG_XDATA);
//-----------------------------------------------------------------------------
// Function Prototypes (Local)
//-----------------------------------------------------------------------------

INTERRUPT_PROTO (CAN0_ISR, INTERRUPT_CAN0);

void CAN0_Send_Message (U8 *buf, U8 msg_obj);
void Mode_Complete(void);

void VCan_Init(void)
{
	EIE2 |= (U8)0x02;
	EA = 0U;

	CanInitPowerOn();
	IlInitPowerOn();
	TpInitPowerOn();
	NmBasicInitPowerOn();
	DescInitPowerOn(0);

	EA = 1U;
}

void VCan_Start(void)
{
	NmBasicStart();
	IlTxStart();
	IlRxStart();
}

void VCan_Task(void)
{
	IlRxTask();
	IlTxTask();
	TpRxTask();
	DescTask();
	TpTxTask();
	NmBasicTask();
}

void ApplNmBasicSwitchTransceiverOn(NMBASIC_CHANNEL_APPLTYPE_ONLY)
{
}
void ApplNmBasicEnabledCom(NMBASIC_CHANNEL_APPLTYPE_ONLY)
{
#if defined (VGEN_ENABLE_IL_VECTOR)
	IlRxStart();
	IlTxStart();
#endif

}
void ApplNmBasicBusOffEnd(NMBASIC_CHANNEL_APPLTYPE_ONLY)
{
#if defined (VGEN_ENABLE_IL_VECTOR)
//#if (no timeout detection during BusOff )
	IlRxRelease();
	IlTxRelease();
//#endif
#endif
}
void ApplNmBasicBusOffRestart(NMBASIC_CHANNEL_APPLTYPE_ONLY)
{	
}
void ApplNmBasicBusOffStart(NMBASIC_CHANNEL_APPLTYPE_ONLY)
{
#if defined (VGEN_ENABLE_IL_VECTOR)
//#if (no timeout detection during BusOff )
	IlTxWait();
	IlRxWait();
//#endif
#endif
}
void ApplNmBasicDisabledCom(NMBASIC_CHANNEL_APPLTYPE_ONLY)
{
#if defined (VGEN_ENABLE_IL_VECTOR)
	IlRxStop();
	IlTxStop();
#endif	
}
void ApplNmBasicFirstBusOffSlow(NMBASIC_CHANNEL_APPLTYPE_ONLY)
{
	U8 lFlgCanStatus;
	
	lFlgCanStatus = (CanGetStatus() & kCanTxOn);
	CanOffline();
	CanPartOffline(C_SEND_GRP_NONE);
	if ( lFlgCanStatus == kCanTxOn)
	{
		CanOnline();
	}
}

void ApplIlFatalError(vuint8 errorNumber)
{
	errorNumber = 0U;
}

vuint8 ApplNmBasicSwitchTransceiverOff(NMBASIC_CHANNEL_APPLTYPE_ONLY)
{
	vuint8 ret = 0U;
	return ret;
}

void TP_API_CALLBACK_TYPE ApplTpFatalError(canuint8 errorNumber)
{
	errorNumber = 0U;
}

void ISR_SAS(CanReceiveHandle rcvObject)
{
}

/* CODE CATEGORY 1 START */
void ISR_HuType(CanReceiveHandle rcvObject)
{
}
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
void ISR_NaviOnOff(CanReceiveHandle rcvObject)
{
}
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
void ISR_CountryCfg(CanReceiveHandle rcvObject)
{
}
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
void ISR_LanguageInfo(CanReceiveHandle rcvObject)
{
}
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
void ISR_MdpsType(CanReceiveHandle rcvObject)
{
}

void ApplHU_MON_PE_01MsgTimeout(void){}

void ApplHU_TYPERxSigTimeout(void){}
void ApplCGW4MsgTimeout(void){}
void ApplCF_Gway_Navi_On_OffRxSigTimeout(void){}
void ApplCGW2MsgTimeout(void){}
void ApplCF_Gway_CountryCfgRxSigTimeout(void){}
void ApplCLU15MsgTimeout(void){}
void ApplCF_Clu_LanguageInfoRxSigTimeout(void){}
void ApplMDPS11MsgTimeout(void){}
void ApplCF_Mdps_TypeRxSigTimeout(void){}
void ApplCF_Mdps_Type_1RxSigTimeout(void){}
void ApplSAS1MsgTimeout(void){}
void ApplSAS_AngleRxSigTimeout(void)
{
}


void Can_Init()
{
	U8 SFRPAGE_save = SFRPAGE;
	SFRPAGE  = CAN0_PAGE;               // All CAN register are on page 0x0C

	CAN0CN |= 0x01;                     // Start Intialization mode

	//---------Initialize general CAN peripheral settings

	CAN0CN |= 0x4E;                     // Enable Error and Module
	                                   // Enable access to bit timing register

	// See the CAN Bit Timing Spreadsheet for how to calculate this value
	//   CAN0BT = 0x1402;                    // Based on 24 Mhz CAN clock, set the
	                                   // CAN bit rate to 1 Mbps
	CAN0BT  = 0x3A02U; //bit14-12:
	                 //010 - TSEG1-1, (the time segment before the sample point) 
	                 //bit11-8:
	                 //0011 - TSEG2-1, (the time segment after the sample point)
	                 //bit7-6:
	                 //00 - SJW-1, ((Re)synchronisation jump width)
	                 //bit5-0:
	                 //00101 - BRP-1, (boud rate prescaler)

	//---------Initialize settings for Transmit Message Object 1

	// Command Mask Register
	CAN0IF1CM = 0x00F0;                 // Write Operation
	                                   // Transfer ID Mask, MDir, MXtd
	                                   // Transfer ID, Dir, Xtd, MsgVal
	                                   // Transfer Control Bits
	                                   // Don't set TxRqst or transfer data

	// Mask Registers
	CAN0IF1M1 = 0x0000;                 // Mask Bits 15-0 not used for filtering
	CAN0IF1M2 = 0x5FFC;                 // Ignore Extended Identifier for
	                                   // filtering
	                                   // Used Direction bit for filtering
	                                   // Use ID bits 28-18 for filtering

	// Message Control Registers
	CAN0IF1MC = 0x0080 | MESSAGE_SIZE;  // Disable Transmit Interrupt
	                                   // Message Object is a Single Message
	                                   // Message Size set by #define
	// Arbitration Registers
	CAN0IF1A1 = 0x0000;                 // 11-bit ID, so lower 16-bits not used

	// Arbitration Registers
	CAN0IF1A2 = 0xA000 | (MSG_ID_TX_BL_CMD << 2);   // Set MsgVal to valid
	                                               // Set Direction to write
	                                               // Set 11-bit Identifier

	CAN0IF1CR = MO_TX_BL_CMD;           // Start command request

	while (CAN0IF1CRH & 0x80) {}        // Poll on Busy bit

	//---------Initialize settings for Transmit Message Object 2

	// Can use the same settings for this transmit object, so no need reinitalize
	// the first five CAN registers again

	// Command Mask Register
	// CAN0IF1CM = 0x00F0;

	// Mask Registers
	// CAN0IF1M1 = 0x0000;
	// CAN0IF1M2 = 0x5FFC;

	// Message Control Registers
	// CAN0IF1MC = 0x0080 | MESSAGE_SIZE;

	// Arbitration Registers
	// CAN0IF1A1 = 0x0000;

	// Arbitration Registers
	CAN0IF1A2 = 0xA000 | (MSG_ID_TX_BL_WRITE8 << 2);   // Set MsgVal to valid
	                                                  // Set Direction to write
	                                                  // Set 11-bit Identifier

	CAN0IF1CR = MO_TX_BL_WRITE8;        // Start command request

	while (CAN0IF1CRH & 0x80) {}        // Poll on Busy bit

	//---------Initialize settings for Receive Message Object

	// Can use the same settings for Receive object, so no need reinitalize the
	// first four CAN registers again

	// Command Mask Register
	//   CAN0IF1CM = 0x00F0;

	// Mask Registers
	//  CAN0IF1M1 = 0x0000;
	//  CAN0IF1M2 = 0x5FFC;

	// Arbitration Registers
	//  CAN0IF1A1 = 0x0000;


	// Arbitration Registers
	CAN0IF1A2 = 0xA000 | (MSG_ID_TX_SAS << 2);   // Set MsgVal to valid
	                                               // Set Object Direction to read
	                                               // Set 11-bit Identifier

	CAN0IF1CR = MO_TX_SAS_ID;              // Start command request

	while (CAN0IF1CRH & 0x80) {}           // Poll on Busy bit

	//---------Initialize settings for Receive Message Object

	// Can use the same settings for Receive object, so no need reinitalize the
	// first four CAN registers again

	// Command Mask Register
	//   CAN0IF1CM = 0x00F0;

	// Mask Registers
	//  CAN0IF1M1 = 0x0000;
	//  CAN0IF1M2 = 0x5FFC;

	// Arbitration Registers
	//  CAN0IF1A1 = 0x0000;


	// Arbitration Registers
	CAN0IF1A2 = 0xA000 | (MSG_ID_TX_CLU << 2);   // Set MsgVal to valid
	                                               // Set Object Direction to read
	                                               // Set 11-bit Identifier

	CAN0IF1CR = MO_TX_CLU_ID;              // Start command request

	while (CAN0IF1CRH & 0x80) {}           // Poll on Busy bit
	//---------Initialize settings for Receive Message Object

	// Can use the same settings for Receive object, so no need reinitalize the
	// first four CAN registers again

	// Command Mask Register
	//   CAN0IF1CM = 0x00F0;

	// Mask Registers
	//  CAN0IF1M1 = 0x0000;
	//  CAN0IF1M2 = 0x5FFC;

	// Arbitration Registers
	//  CAN0IF1A1 = 0x0000;


	// Arbitration Registers
	CAN0IF1A2 = 0x8000 | (MSG_ID_RX_BL_RSP << 2);   // Set MsgVal to valid
	                                               // Set Object Direction to read
	                                               // Set 11-bit Identifier

	CAN0IF1CR = MO_RX_BL_RSP;              // Start command request

	while (CAN0IF1CRH & 0x80) {}           // Poll on Busy bit

	//diagnostic
	// CAN TX

	CAN0IF1A2 = 0xA000U | (MSG_ID_FUNCTION_REQ << 2U);  // Set MsgVal to valid

	CAN0IF1CR = MO_FUNCTION_REQ;                // Start command request

	while (CAN0IF1CRH & 0x80) {}           // Poll on Busy bit


	CAN0IF1A2 = 0xA000U | (MSG_ID_PGS_PHYS_ID << 2U);  // Set MsgVal to valid

	CAN0IF1CR = MO_PGS_PHYS_ID;                // Start command request

	while (CAN0IF1CRH & 0x80) {}           // Poll on Busy bit

	// --------------------------------FPM CONGIG-------------------------------------

	CAN0IF1A2 = 0xA000U | (MSG_ID_TX_GST << 2U);  // Set MsgVal to valid

	CAN0IF1CR = MO_TX_GST_ID;                // Start command request

	while (CAN0IF1CRH & 0x80) {}           // Poll on Busy bit


	CAN0IF1A2 = 0xA000U | (MSG_ID_TX_LED << 2U);  // Set MsgVal to valid

	CAN0IF1CR = MO_TX_LED_ID;                // Start command request

	while (CAN0IF1CRH & 0x80) {}           // Poll on Busy bit

	CAN0IF1MC = 0x1480U; // RX CONFIG--------------------------------------------------------------
	// Arbitration Registers
	CAN0IF1A2 = 0x8000 | (MSG_ID_RECEIVE_ID << 2);   // Set MsgVal to valid
	                                               // Set Object Direction to read
	                                               // Set 11-bit Identifier
	CAN0IF1CR = MO_RECEIVE_ID;              // Start command request

	while (CAN0IF1CRH & 0x80) {}           // Poll on Busy bit
	
//--------------------------------FPM CONFIG--------------------------------------
	CAN0IF1A2 = 0x8000 | (MSG_ID_RECEIVE_GST << 2u);   // Set MsgVal to valid
	                                               // Set Object Direction to read
	                                               // Set 11-bit Identifier
	CAN0IF1CR = MO_RX_GST_ID;              // Start command request

	while (CAN0IF1CRH & 0x80) {}           // Poll on Busy bit


	CAN0IF1A2 = 0x8000 | (MSG_ID_RECEIVE_NM << 2u);   // Set MsgVal to valid
	                                               // Set Object Direction to read
	                                               // Set 11-bit Identifier
	CAN0IF1CR = MO_RX_NM_ID;              // Start command request

	while (CAN0IF1CRH & 0x80) {}           // Poll on Busy bit

	CAN0IF1A2 = 0x8000 | (MSG_ID_RECEIVE_07 << 2u);   // Set MsgVal to valid
	                                               // Set Object Direction to read
	                                               // Set 11-bit Identifier
	CAN0IF1CR = MO_RX_07_ID;              // Start command request

	while (CAN0IF1CRH & 0x80) {}           // Poll on Busy bit

	CAN0IF1A2 = 0x8000 | (MSG_ID_RECEIVE_08 << 2u);   // Set MsgVal to valid
	                                               // Set Object Direction to read
	                                               // Set 11-bit Identifier
	CAN0IF1CR = MO_RX_08_ID;              // Start command request

	while (CAN0IF1CRH & 0x80) {}           // Poll on Busy bit

	//--------- CAN Initalization is complete

	CAN0CN &= ~0x41;                    // Return to Normal Mode and disable
	                                   // access to bit timing register


	//CAN0CN |= 0x80U;//Test Mode Enable
	//CAN0TST = 0x10U;//Loop Back Mode |= 0x10U;     //bit1:

	EIE2 |= 0x02;                       // Enable CAN interupts

	SFRPAGE = SFRPAGE_save;
}

void CAN0_Send_Message (U8 *buf, U8 msg_obj)
{
	U16 i;
   // This function assumes that the message object is fully initialized
   // in CAN0_Init and so all it has to do is fill the data registers and
   // initiate transmission

   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE  = CAN0_PAGE;               // All CAN register are on page 0x0C
   //for( i = 0; i < 45000; i++);
   CAN0IF1DA1H = *buf;                 // Initialize data registers
   CAN0IF1DA1L = *(buf + 1);
   CAN0IF1DA2H = *(buf + 2);
   CAN0IF1DA2L = *(buf + 3);
   CAN0IF1DB1H = *(buf + 4);
   CAN0IF1DB1L = *(buf + 5);
   CAN0IF1DB2H = *(buf + 6);
   CAN0IF1DB2L = *(buf + 7);

   CAN0IF1CM = 0x0087;                 // Set Direction to Write
                                       // Write TxRqst, all 8 data bytes

   CAN0IF1CR = msg_obj;                // Start command request

   while (CAN0IF1CRH & 0x80) {}        // Poll on Busy bit

   SFRPAGE = SFRPAGE_save;             // Restore SFRPAGE
}

//-----------------------------------------------------------------------------
U8 TGT_Enter_Diagnostic_Mode (U8 request_response, U8 CAN_dev_addr)
{
	U8 SFRPAGE_save = SFRPAGE;
	SFRPAGE = CAN0_PAGE;

	// Command Format:
	// [0] Command
	// [1] CAN Device Address

	Tx_Standard_Mode();
	//Cur_Mode = 
	Tx_SWVersion_Req();
	
	CAN_Tx_Buf[0] = TGT_CMD_ENTER_BL_MODE;
	CAN_Tx_Buf[1] = CAN_dev_addr;
	
	//CAN_Tx_Buf[1] = 0x01;   // CAN Device Addr = 0x01
	// Other bytes of the message are "don't care".

	CAN_Rx_Complete_Flag = 0;
	CAN0_Send_Message (CAN_Tx_Buf, MO_TX_BL_CMD);

	SFRPAGE = SFRPAGE_save;

	return CAN_Rx_Buf[0];
}
//-----------------------------------------------------------------------------
// TGT_Get_Info
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
//
//
//-----------------------------------------------------------------------------
U8 TGT_Get_Info (U8 *target_info)
{
   U8 packet_num;
   U8 index;

   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CAN0_PAGE;

   // Command Format:
   // [0] Command

   CAN_Tx_Buf[0] = TGT_CMD_GET_INFO;
   // Other bytes of the message are "don't care".

   for (packet_num = 0; packet_num < 3; packet_num++)
   {
      CAN_Rx_Complete_Flag = 0;
      CAN0_Send_Message (CAN_Tx_Buf, MO_TX_BL_CMD);

//      while (CAN_Rx_Complete_Flag == 0);  // Wait till a response is received

      // Response:
      // [0] Return code (ACK/ERROR etc)
      // [1] Packet Number
      // [2] InfoBlock byte (0 + (packetnum*6))
      // [3] InfoBlock byte (1 + (packetnum*6))
      // [4] ...
      // [5] 
      // [6] 
      // [7]
/*
      if (CAN_Rx_Buf[0] != TGT_RSP_OK)
         break;

      if (CAN_Rx_Buf[1] != packet_num)
      {
         CAN_Rx_Buf[0] = TGT_RSP_ERROR;
         break;
      }

      for (index = 0; index < (MESSAGE_SIZE-2); index++)
      {
         target_info[index + (packet_num*6)] = CAN_Rx_Buf[index + 2];
      }
	  */
   }

   SFRPAGE = SFRPAGE_save;

   return CAN_Rx_Buf[0];
}

//-----------------------------------------------------------------------------
// TGT_Set_Flash_Keys
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
//
//
//-----------------------------------------------------------------------------
U8 TGT_Set_Flash_Keys (U8 flash_key0, U8 flash_key1)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CAN0_PAGE;

   // Command Format:
   // [0] Command
   // [1] Flash Key byte 0
   // [2] Flash Key byte 1

   CAN_Tx_Buf[0] = TGT_CMD_SET_FLASH_KEYS;
   CAN_Tx_Buf[1] = flash_key0;
   CAN_Tx_Buf[2] = flash_key1;
   // Other bytes of the message are "don't care".

   CAN_Rx_Complete_Flag = 0;
   CAN0_Send_Message (CAN_Tx_Buf, MO_TX_BL_CMD);

//   while (CAN_Rx_Complete_Flag == 0);  // Wait till a response is received

   // Response:
   // [0] Return code (ACK/ERROR etc)

   SFRPAGE = SFRPAGE_save;

   return CAN_Rx_Buf[0];
}

//-----------------------------------------------------------------------------
// TGT_Set_Addr
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
//
//

//-----------------------------------------------------------------------------
// TGT_Erase_Page
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
//
//
//-----------------------------------------------------------------------------
U8 TGT_Erase_Page (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CAN0_PAGE;

   // Command Format:
   // [0] Command

   CAN_Tx_Buf[0] = TGT_CMD_ERASE_PAGE;
   // Other bytes of the message are "don't care".

   CAN_Rx_Complete_Flag = 0;
   CAN0_Send_Message (CAN_Tx_Buf, MO_TX_BL_CMD);

//   while (CAN_Rx_Complete_Flag == 0);  // Wait till a response is received

   // Response:
   // [0] Return code (ACK/ERROR etc)

   SFRPAGE = SFRPAGE_save;

   return CAN_Rx_Buf[0];
}

//-----------------------------------------------------------------------------
// TGT_Write_Flash
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
//
//
//-----------------------------------------------------------------------------
U8 TGT_Write_Flash (U8 *buf, U16 index, U8 numbytes,U8 Page_Num)
{
	U8 i;
	static SEG_XDATA U8 cnt = 0,page = 0xFF;
	SEG_XDATA U8 last_byte = 0x00U;
	U8 SFRPAGE_save = SFRPAGE;
	SFRPAGE = CAN0_PAGE;

	// numbytes needs to be 8 because this message is preconfigured for 8 bytes

	// Command Format: [No command byte because this uses a unique message ID]
	// [0] Flash byte 0
	// [1] Flash byte 1
	// [2] Flash byte 2
	// [3] Flash byte 3
	// [4] Flash byte 4
	// [5] Flash byte 5
	// [6] Flash byte 6
	// [7] Flash byte 7


	if ( page != Page_Num )
	{
		page = Page_Num;
		CAN_Tx_Buf[0] = 0xFF;
		CAN_Tx_Buf[1] = 0x10;
		CAN_Tx_Buf[2] = Page_Num+1;
		CAN_Tx_Buf[3] = 0x36;
		CAN_Tx_Buf[4] = *(buf+1);
		CAN_Tx_Buf[5] = *(buf+0);
		CAN_Tx_Buf[6] = *(buf+3);
		CAN_Tx_Buf[7] = *(buf+2);
		cnt = 0;
	}
	else
	{
		if ( cnt == 16 )
		{
			CAN_Tx_Buf[0] = *(buf+index +0);
			CAN_Tx_Buf[1] = 0x20;
			CAN_Tx_Buf[2] = *(buf+index +2);
			CAN_Tx_Buf[3] = *(buf+index +1);
			CAN_Tx_Buf[4] = *(buf+index +4);
			CAN_Tx_Buf[5] = *(buf+index +3);
			CAN_Tx_Buf[6] = *(buf+index +6);
			CAN_Tx_Buf[7] = *(buf+index +5);
			cnt = 0;	

		}
		else
		{	
			CAN_Tx_Buf[0] = *(buf+index +0);
			CAN_Tx_Buf[1] = cnt+0x20;
			CAN_Tx_Buf[2] = *(buf+index +2);
			CAN_Tx_Buf[3] = *(buf+index +1);
			CAN_Tx_Buf[4] = *(buf+index +4);
			CAN_Tx_Buf[5] = *(buf+index +3);
			CAN_Tx_Buf[6] = *(buf+index +6);
			CAN_Tx_Buf[7] = *(buf+index +5);
		}

		if ( numbytes == 4 )
		{
			CAN_Tx_Buf[0] = *(buf+index +0);
			CAN_Tx_Buf[1] = cnt+0x20;
			CAN_Tx_Buf[2] = *(buf+index +2);
			CAN_Tx_Buf[3] = *(buf+index +1);
			CAN_Tx_Buf[4] = 0x55U;
			CAN_Tx_Buf[5] = *(buf+index +3);
			CAN_Tx_Buf[6] = 0x55U;
			CAN_Tx_Buf[7] = 0x55U;
		}

	}	
	last_byte++;
	cnt++;	
	// Other bytes of the message are "don't care".
	
	CAN_Rx_Complete_Flag = 0;
	CAN0_Send_Message (CAN_Tx_Buf, MO_PGS_PHYS_ID);

		
	//   while (CAN_Rx_Complete_Flag == 0);  // Wait till a response is received

	// Response:
	// [0] Return code (ACK/ERROR etc)

	SFRPAGE = SFRPAGE_save;

	return CAN_Rx_Buf[0];
}

//-----------------------------------------------------------------------------
// TGT_Get_Page_CRC
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
//
//
//-----------------------------------------------------------------------------
U8 TGT_Get_Page_CRC (U16 *target_page_crc)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CAN0_PAGE;

   // Command Format:
   // [0] Command

   CAN_Tx_Buf[0] = TGT_CMD_GET_PAGE_CRC;
   // Other bytes of the message are "don't care".

   CAN_Rx_Complete_Flag = 0;
   CAN0_Send_Message (CAN_Tx_Buf, MO_TX_BL_CMD);

//   while (CAN_Rx_Complete_Flag == 0);  // Wait till a response is received

   // Response:
   // [0] Return code (ACK/ERROR etc)
   // [1] CRC byte 0
   // [2] CRC byte 1

   *target_page_crc = (U16)((CAN_Rx_Buf[2] << 8) | CAN_Rx_Buf[1]);

   SFRPAGE = SFRPAGE_save;

   return CAN_Rx_Buf[0];
}

//-----------------------------------------------------------------------------
// TGT_Write_Signature
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
//
//
//-----------------------------------------------------------------------------
U8 TGT_Write_Signature (U8 sig_byte0, U8 sig_byte1, U8 sig_byte2, U8 sig_byte3)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CAN0_PAGE;

   // Command Format:
   // [0] Command
   // [1] Signature byte 0
   // [2] Signature byte 1
   // [3] Signature byte 2
   // [4] Signature byte 3

   CAN_Tx_Buf[0] = TGT_CMD_WRITE_SIGNATURE;
   CAN_Tx_Buf[1] = sig_byte0;
   CAN_Tx_Buf[2] = sig_byte1;
   CAN_Tx_Buf[3] = sig_byte2;
   CAN_Tx_Buf[4] = sig_byte3;
   // Other bytes of the message are "don't care".

   CAN_Rx_Complete_Flag = 0;
   CAN0_Send_Message (CAN_Tx_Buf, MO_TX_BL_CMD);

//   while (CAN_Rx_Complete_Flag == 0);  // Wait till a response is received

   // Response:
   // [0] Return code (ACK/ERROR etc)


   SFRPAGE = SFRPAGE_save;

   return CAN_Rx_Buf[0];
}

//-----------------------------------------------------------------------------
// TGT_SW_Reset
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
//
//
//-----------------------------------------------------------------------------
void TGT_SW_Reset (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;

   // Command Format:
   // [0] Command

   CAN_Tx_Buf[0] = TGT_CMD_SW_RESET;
   // Other bytes of the message are "don't care".

   CAN_Rx_Complete_Flag = 0;
   CAN0_Send_Message (CAN_Tx_Buf, MO_TX_BL_CMD);


   // No response should be expected for this command

   /*
   while (CAN_Rx_Complete_Flag == 0);  // Wait till a response is received
   */

   // Response:
   // [0] Return code (ACK/ERROR etc)


   SFRPAGE = SFRPAGE_save;
}

//-----------------------------------------------------------------------------
// TGT_Set_Flash_Keys
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
//
//
//-----------------------------------------------------------------------------
/*U8 Transfer_SAS_Data (U8 SAS_Low, U8 SAS_High)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CAN0_PAGE;

   // Command Format:
   // [0] Command
   // [1] Flash Key byte 0
   // [2] Flash Key byte 1

   CAN_Tx_Buf[0] = SAS_Low;
   CAN_Tx_Buf[1] = SAS_High;
   CAN_Tx_Buf[2] = 0U;
   CAN_Tx_Buf[3] = 0U;
   CAN_Tx_Buf[4] = 0U;
   CAN_Tx_Buf[5] = 0U;
   CAN_Tx_Buf[6] = 0U;
   CAN_Tx_Buf[7] = 0U;
   // Other bytes of the message are "don't care".

   CAN_Rx_Complete_Flag = 0;
   CAN0_Send_Message (CAN_Tx_Buf, MO_TX_SAS_ID);

//   while (CAN_Rx_Complete_Flag == 0);  // Wait till a response is received

   // Response:
   // [0] Return code (ACK/ERROR etc)

   SFRPAGE = SFRPAGE_save;

   return CAN_Rx_Buf[0];
}*/

U8 SEND_7DF(U8 mode)
{
	U8 SFRPAGE_save = SFRPAGE;
	
	EIE2 &= ~(0x02U);
	SFRPAGE  = CAN0_PAGE;               // All CAN register are on page 0x0C
	CAN_Rx_Complete_Flag = 0x00U;
	switch(mode)
	{
		case STANDARD_MODE:
			CAN0IF1DA1L = 0x02;          // on message object used
			CAN0IF1DA1H = 0x10;              // Initialize data registers based
			CAN0IF1DA2L = 0x81;
			CAN0IF1DA2H = 0x55;
			CAN0IF1DB1L = 0x55;
			CAN0IF1DB1H = 0x55;
			CAN0IF1DB2L = 0x55;
			CAN0IF1DB2H = 0x55;
			CAN0IF1CM = 0x0087;                 // Set Direction to Write
			                                   // Write TxRqst, all 8 data bytes
			CAN0IF1CR = MO_FUNCTION_REQ;            // Start command request
			while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit
		break;
		case EXTENDED_MODE:			
			CAN0IF1DA1L = 0x02;          // on message object used
			CAN0IF1DA1H = 0x10;              // Initialize data registers based
			CAN0IF1DA2L = 0x90;
			CAN0IF1DA2H = 0x55;
			CAN0IF1DB1L = 0x55;
			CAN0IF1DB1H = 0x55;
			CAN0IF1DB2L = 0x55;
			CAN0IF1DB2H = 0x55;
			CAN0IF1CM = 0x0087;                 // Set Direction to Write
			                                   // Write TxRqst, all 8 data bytes
			CAN0IF1CR = MO_FUNCTION_REQ;            // Start command request
			while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit
		break;
		case CONTROLDTC_OFF:			
			CAN0IF1DA1L = 0x02;          // on message object used
			CAN0IF1DA1H = 0x85;              // Initialize data registers based
			CAN0IF1DA2L = 0x82;
			CAN0IF1DA2H = 0x55;
			CAN0IF1DB1L = 0x55;
			CAN0IF1DB1H = 0x55;
			CAN0IF1DB2L = 0x55;
			CAN0IF1DB2H = 0x55;
			CAN0IF1CM = 0x0087;                 // Set Direction to Write
			                                   // Write TxRqst, all 8 data bytes
			CAN0IF1CR = MO_FUNCTION_REQ;            // Start command reques
			while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit
		break;
		case COMM_CONTROL_DISABLE:
			CAN0IF1DA1L = 0x02;          // on message object used
			CAN0IF1DA1H = 0x28;              // Initialize data registers based
			CAN0IF1DA2L = 0x02;
			CAN0IF1DA2H = 0x55;
			CAN0IF1DB1L = 0x55;
			CAN0IF1DB1H = 0x55;
			CAN0IF1DB2L = 0x55;
			CAN0IF1DB2H = 0x55;

			CAN0IF1CM = 0x0087;                 // Set Direction to Write
			                                   // Write TxRqst, all 8 data bytes

			CAN0IF1CR = MO_FUNCTION_REQ;            // Start command request

			while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit
		break;
		case COMM_CONTROL_ENABLE:			
			CAN0IF1DA1L = 0x02;          // on message object used
			CAN0IF1DA1H = 0x29;              // Initialize data registers based
			CAN0IF1DA2L = 0x02;
			CAN0IF1DA2H = 0x55;
			CAN0IF1DB1L = 0x55;
			CAN0IF1DB1H = 0x55;
			CAN0IF1DB2L = 0x55;
			CAN0IF1DB2H = 0x55;
			CAN0IF1CM = 0x0087;                 // Set Direction to Write
			                                   // Write TxRqst, all 8 data bytes
			CAN0IF1CR = MO_FUNCTION_REQ;            // Start command reques
			while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit

		case COMM_CONTROL_DISABLE2:			
			CAN0IF1DA1L = 0x02;          // on message object used
			CAN0IF1DA1H = 0x3E;              // Initialize data registers based
			CAN0IF1DA2L = 0x80;
			CAN0IF1DA2H = 0x55;
			CAN0IF1DB1L = 0x55;
			CAN0IF1DB1H = 0x55;
			CAN0IF1DB2L = 0x55;
			CAN0IF1DB2H = 0x55;
			CAN0IF1CM = 0x0087;                 // Set Direction to Write
			                                   // Write TxRqst, all 8 data bytes
			CAN0IF1CR = MO_FUNCTION_REQ;            // Start command reques
			while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit

		break;
		default:
		break;
	}
	
	//CAN0IF1CM
	SFRPAGE = SFRPAGE_save;
	EIE2 |= 0x02U;

}

void SEND_796(U8 mode)
{
	U8 SFRPAGE_save = SFRPAGE;
	
	EIE2 &= ~(0x02U);
	SFRPAGE  = CAN0_PAGE;               // All CAN register are on page 0x0C
	CAN_Rx_Complete_Flag = 0x00U;
	switch(mode)
	{
		case SWVERSION:
			CAN0IF1DA1L = 0x03;          // on message object used
			CAN0IF1DA1H = 0x22;              // Initialize data registers based
			CAN0IF1DA2L = 0xF1;
			CAN0IF1DA2H = 0x95;
			CAN0IF1DB1L = 0x55;
			CAN0IF1DB1H = 0x55;
			CAN0IF1DB2L = 0x55;
			CAN0IF1DB2H = 0x55;

			CAN0IF1CM = 0x0087;                 // Set Direction to Write
			                                   // Write TxRqst, all 8 data bytes

			CAN0IF1CR = MO_PGS_PHYS_ID;            // Start command request

			while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit
		break;
		case EXTENDED_SESSION:
			CAN0IF1DA1L = 0x02;          // on message object used
			CAN0IF1DA1H = 0x10;              // Initialize data registers based
			CAN0IF1DA2L = 0x03;
			CAN0IF1DA2H = 0x55;
			CAN0IF1DB1L = 0x55;
			CAN0IF1DB1H = 0x55;
			CAN0IF1DB2L = 0x55;
			CAN0IF1DB2H = 0x55;

			CAN0IF1CM = 0x0087;                 // Set Direction to Write
			                                   // Write TxRqst, all 8 data bytes

			CAN0IF1CR = MO_PGS_PHYS_ID;            // Start command request

			while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit
		break;
		case PROGRAMMING_SESSION:
			CAN0IF1DA1L = 0x02;          // on message object used
			CAN0IF1DA1H = 0x10;              // Initialize data registers based
			CAN0IF1DA2L = 0x02;
			CAN0IF1DA2H = 0x00;
			CAN0IF1DB1L = 0x00;
			CAN0IF1DB1H = 0x00;
			CAN0IF1DB2L = 0x00;
			CAN0IF1DB2H = 0x00;

			CAN0IF1CM = 0x0087;                 // Set Direction to Write
			                                   // Write TxRqst, all 8 data bytes
			CAN0IF1CR = MO_PGS_PHYS_ID;            // Start command request
			while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit
			
		break;
		case REQUEST_SEED:
			CAN0IF1DA1L = 0x02;          // on message object used
			CAN0IF1DA1H = 0x27;              // Initialize data registers based
			CAN0IF1DA2L = 0x01;
			CAN0IF1DA2H = 0x55;
			CAN0IF1DB1L = 0x55;
			CAN0IF1DB1H = 0x55;
			CAN0IF1DB2L = 0x55;
			CAN0IF1DB2H = 0x55;

			CAN0IF1CM = 0x0087;                 // Set Direction to Write
			                                   // Write TxRqst, all 8 data bytes
			CAN0IF1CR = MO_PGS_PHYS_ID;            // Start command request
			while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit
		break;
		case SEND_KEY:
			CAN0IF1DA1L = 0x06;          // on message object used
			CAN0IF1DA1H = 0x27;              // Initialize data registers based
			CAN0IF1DA2L = 0x02;
			CAN0IF1DA2H = KeyData[0];//0x00;
			CAN0IF1DB1L = KeyData[1];//0x00;
			CAN0IF1DB1H = KeyData[2];//0x00;
			CAN0IF1DB2L = KeyData[3];//0x00;
			CAN0IF1DB2H = 0x55;

			CAN0IF1CM = 0x0087;                 // Set Direction to Write
			                                   // Write TxRqst, all 8 data bytes
			CAN0IF1CR = MO_PGS_PHYS_ID;            // Start command request
			while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit

		break;
		case ROUTINE_BINARY_UPDATE:
			CAN0IF1DA1L = 0x05;          // on message object used
			CAN0IF1DA1H = 0x31;              // Initialize data registers based
			CAN0IF1DA2L = 0x01;
			CAN0IF1DA2H = 0xFF;
			CAN0IF1DB1L = 0x00;
			CAN0IF1DB1H = download_type;
			//CAN0IF1DB1H = 0x02;
			CAN0IF1DB2L = 0x55;
			CAN0IF1DB2H = 0x55;

			CAN0IF1CM = 0x0087;                 // Set Direction to Write
			                                   // Write TxRqst, all 8 data bytes
			CAN0IF1CR = MO_PGS_PHYS_ID;            // Start command request
			while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit
		break;
		case REQUEST_DOWNLOAD_1:
			
			CAN0IF1DA1L = 0x10;          // on message object used
			CAN0IF1DA1H = 0x09;              // Initialize data registers based
			CAN0IF1DA2L = 0x34;
			CAN0IF1DA2H = 0x00;
			CAN0IF1DB1L = 0x33;
			CAN0IF1DB1H = 0x00;
			CAN0IF1DB2L = 0x40;
			CAN0IF1DB2H = 0x00;

			CAN0IF1CM = 0x0087;                 // Set Direction to Write
			                                   // Write TxRqst, all 8 data bytes
			CAN0IF1CR = MO_PGS_PHYS_ID;            // Start command request
			while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit
		break;
		case REQUEST_DOWNLOAD_2:
			CAN0IF1DA1L = 0x21;          // on message object used
			CAN0IF1DA1H = TGT_Info[14];  // Initialize data registers based
			CAN0IF1DA2L = TGT_Info[13];
			CAN0IF1DA2H = TGT_Info[12];
			CAN0IF1DB1L = 0x55;
			CAN0IF1DB1H = 0x55;
			CAN0IF1DB2L = 0x55;
			CAN0IF1DB2H = 0x55;

			CAN0IF1CM = 0x0087;                 // Set Direction to Write
			                                   // Write TxRqst, all 8 data bytes
			CAN0IF1CR = MO_PGS_PHYS_ID;            // Start command request
			while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit

		break;
		case REQUEST_TRANSFER_EXIT:
			
			CAN0IF1DA1L = 0x01;          // on message object used
			CAN0IF1DA1H = 0x37;              // Initialize data registers based
			CAN0IF1DA2L = 0x55;
			CAN0IF1DA2H = 0x55;
			CAN0IF1DB1L = 0x55;
			CAN0IF1DB1H = 0x55;
			CAN0IF1DB2L = 0x55;
			CAN0IF1DB2H = 0x55;

			CAN0IF1CM = 0x0087;                 // Set Direction to Write
			                                   // Write TxRqst, all 8 data bytes
			CAN0IF1CR = MO_PGS_PHYS_ID;            // Start command request
			while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit
		break;
		case ECU_RESET:
			CAN0IF1DA1L = 0x02;          // on message object used
			CAN0IF1DA1H = 0x11;  // Initialize data registers based
			CAN0IF1DA2L = 0x01;
			CAN0IF1DA2H = 0x55;
			CAN0IF1DB1L = 0x55;
			CAN0IF1DB1H = 0x55;
			CAN0IF1DB2L = 0x55;
			CAN0IF1DB2H = 0x55;

			CAN0IF1CM = 0x0087;                 // Set Direction to Write
			                                   // Write TxRqst, all 8 data bytes
			CAN0IF1CR = MO_PGS_PHYS_ID;            // Start command request
			while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit

		break;

		default:
		break;
	}
	//CAN0IF1CM
	SFRPAGE = SFRPAGE_save;
	EIE2 |= 0x02U;
}

void SEND_2B0(U8 SAS_Low, U8 SAS_High)
{
	U8 SFRPAGE_save = SFRPAGE;
	
	EIE2 &= ~(0x02U);
	SFRPAGE  = CAN0_PAGE;               // All CAN register are on page 0x0C
	CAN_Rx_Complete_Flag = 0x00U;

	CAN0IF1DA1L = SAS_Low;          // on message object used
	CAN0IF1DA1H = SAS_High;              // Initialize data registers based
	CAN0IF1DA2L = 0x00;
	CAN0IF1DA2H = 0x00;
	CAN0IF1DB1L = 0x00;
	CAN0IF1DB1H = 0x00;
	CAN0IF1DB2L = 0x00;
	CAN0IF1DB2H = 0x00;

	CAN0IF1CM = 0x0087;                 // Set Direction to Write
	                                   // Write TxRqst, all 8 data bytes

	CAN0IF1CR = MO_TX_SAS_ID;            // Start command request

	while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit

	//CAN0IF1CM
	SFRPAGE = SFRPAGE_save;
	EIE2 |= 0x02U;
}
// ---------------- CHANGE
void SEND_GST(U8 TX_DATA[])
{
	U8 SFRPAGE_save = SFRPAGE;
	
	EIE2 &= ~(0x02U);
	SFRPAGE  = CAN0_PAGE;               // All CAN register are on page 0x0C
	CAN_Rx_Complete_Flag = 0x00U;

	CAN0IF1DA1L = TX_DATA[0];          // on message object used
	CAN0IF1DA1H = TX_DATA[1];              // Initialize data registers based
	CAN0IF1DA2L = TX_DATA[2];
	CAN0IF1DA2H = TX_DATA[3];
	CAN0IF1DB1L = TX_DATA[4];
	CAN0IF1DB1H = TX_DATA[5];
	CAN0IF1DB2L = TX_DATA[6];
	CAN0IF1DB2H = TX_DATA[7];

	CAN0IF1CM = 0x0087;                 // Set Direction to Write
	                                   // Write TxRqst, all 8 data bytes

	CAN0IF1CR = MO_TX_GST_ID;            // Start command request

	while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit

	//CAN0IF1CM
	SFRPAGE = SFRPAGE_save;
	EIE2 |= 0x02U;
}

void SEND_LED(U8 TX_DATA[])
{
	U8 SFRPAGE_save = SFRPAGE;
	
	EIE2 &= ~(0x02U);
	SFRPAGE  = CAN0_PAGE;               // All CAN register are on page 0x0C
	CAN_Rx_Complete_Flag = 0x00U;

	CAN0IF1DA1L = TX_DATA[0];          // on message object used
	CAN0IF1DA1H = TX_DATA[1];              // Initialize data registers based
	CAN0IF1DA2L = TX_DATA[2];
	CAN0IF1DA2H = TX_DATA[3];
	CAN0IF1DB1L = TX_DATA[4];
	CAN0IF1DB1H = TX_DATA[5];
	CAN0IF1DB2L = TX_DATA[6];
	CAN0IF1DB2H = TX_DATA[7];

	CAN0IF1CM = 0x0087;                 // Set Direction to Write
	                                   // Write TxRqst, all 8 data bytes

	CAN0IF1CR = MO_TX_LED_ID;            // Start command request

	while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit

	//CAN0IF1CM
	SFRPAGE = SFRPAGE_save;
	EIE2 |= 0x02U;
}

void SEND_52A(U8 LANG_Info)
{
	U8 SFRPAGE_save = SFRPAGE;
	
	EIE2 &= ~(0x02U);
	SFRPAGE  = CAN0_PAGE;               // All CAN register are on page 0x0C
	CAN_Rx_Complete_Flag = 0x00U;

	CAN0IF1DA1L = 0x00;          // on message object used
	CAN0IF1DA1H = 0x00;              // Initialize data registers based
	CAN0IF1DA2L = 0x00;
	CAN0IF1DA2H = 0x00;
	CAN0IF1DB1L = (U8)((LANG_Info << 1U) & 0xFFU);
	CAN0IF1DB1H = 0x00;
	CAN0IF1DB2L = 0x00;
	CAN0IF1DB2H = 0x00;

	CAN0IF1CM = 0x0087;                 // Set Direction to Write
	                                   // Write TxRqst, all 8 data bytes

	CAN0IF1CR = MO_TX_CLU_ID;            // Start command request

	while ((CAN0IF1CRH & 0x80U) == 0x80U);          // Poll on Busy bit

	//CAN0IF1CM
	SFRPAGE = SFRPAGE_save;
	EIE2 |= 0x02U;
}
//=============================================================================
// Interrupt Service Routines
//=============================================================================

//-----------------------------------------------------------------------------
// CAN0_ISR
//-----------------------------------------------------------------------------
//
// The ISR is triggered upon any CAN errors or upon a complete reception.
//
// If an error occurs, a global flag is updated
//
//-----------------------------------------------------------------------------

INTERRUPT(CAN0_ISR, INTERRUPT_CAN0)
{
   static volatile U16 status = 0, Interrupt_ID = 0;
   static volatile U8 reg_val = 0;
   static U8	can_data[8] = {0,0,0,0,0,0,0,0};

   SFRPAGE  = CAN0_PAGE;

   Interrupt_ID = (U16)CAN0IID;          //Read interrupt ID

   if(Interrupt_ID != END)
   {
      if(Interrupt_ID != STATUS_CHANGE)
      {
         // Interrupt handling - status check

		 switch(Interrupt_ID)
		 {
		 	case MO_TX_BL_CMD:
			case MO_TX_BL_WRITE8:
			case MO_TX_SAS_ID: 
			case MO_TX_CLU_ID:
				CAN0IF2CML = 0x18U;  //Clear message interrupt by clearing the Message
	                                 //Object's IntPnd bit
	            CAN0IF2CR = Interrupt_ID;  //Read message to IF1 registers 
	            while( 1 ){
					reg_val = (U8)CAN0IF2CRH;
					if( (reg_val & 0x80U) != 0x80U ){
						break;
					}
				} //Poll on Busy bit
				break;

			case MO_RX_NM_ID: //54F
				status = RX_Mes(MO_RX_NM_ID);
            	ID_54F_function(); // THIS FUNCTION TO TEST SLEEP
				break;

			case MO_RX_BL_RSP:	//2B1
				status = RX_Mes(MO_RX_BL_RSP);
				break;

			case MO_RECEIVE_ID:		//79E
				status = RX_Mes(MO_RECEIVE_ID);
				Mode_Complete();
				break;
			
			case MO_RX_GST_ID:	// 7AA
				status = RX_Mes(MO_RX_GST_ID);
				ID_7AA_function();
			case MO_RX_07_ID:	// 19F
				status = RX_Mes(MO_RX_07_ID);
				ID_19F_function();
			case MO_RX_08_ID:	// 2F2
				status = RX_Mes(MO_RX_08_ID);
				ID_2F2_function();
			
			default: break;

		 } //end of switch
		 //-------------------------------------------------------------------------------------
		 
      }//end of if
      // Status change interrup handling 
      status = (U16)CAN0STAT;

      if( (status & TxOk) == TxOk )
      {
         CAN0STAT &= (U8)(~TxOk);   //Clear TxOk
      }
      if( (status & RxOk) == RxOk )                  
      {
         CAN0STAT &= (U8)(~RxOk);   //Clear TxOk
      }
   }

   SFRPAGE  = ACTIVE_PAGE;
}
U16 RX_Mes(U16 Interrupt_ID)
{
	static volatile U16 status = 0;
   	static volatile U8 reg_val = 0;
	CAN0IF1CML = 0x7FU;   //Set Command Mask to read, transfer Control
                                 //bits, clear pending interrupt bit and NewDat
                                 //bit, trnsfer data bytes 
    CAN0IF1CR = Interrupt_ID;  //Read message to IF1 registers 
    while( 1 ){
		reg_val = (U8)CAN0IF1CRH;
		if( (reg_val & 0x80U) != 0x80U ){
			break;
		}
	} //Poll on Busy bit
 
    status = (U16)CAN0IF1MC;

    if( (status&NEWDATA) == NEWDATA )
    {
		CAN_Rx_Buf[0] = CAN0IF1DA1L;
		CAN_Rx_Buf[1] = CAN0IF1DA1H;
		CAN_Rx_Buf[2] = CAN0IF1DA2L;
		CAN_Rx_Buf[3] = CAN0IF1DA2H;
		CAN_Rx_Buf[4] = CAN0IF1DB1L;
		CAN_Rx_Buf[5] = CAN0IF1DB1H;
		CAN_Rx_Buf[6] = CAN0IF1DB2L;
		CAN_Rx_Buf[7] = CAN0IF1DB2H;
		
		CAN_Rx_Complete_Flag = 1;       // Indicate Rx Complete
		
		
		status = (U16)CAN0IF1A2;
		
    }
	return status;
}

extern U8 State_machine;
extern U8 SW;
U32 Pre_time = 0;

void ID_2F2_function()
{
	if(SW == 0x02)
	{
		if(CAN_Rx_Buf[0] == 0x02 && CAN_Rx_Buf[1] == 0x11 &&CAN_Rx_Buf[2] == 0x11&&CAN_Rx_Buf[3] == 0x11&&CAN_Rx_Buf[4] == 0x11&&CAN_Rx_Buf[5] == 0x11&&CAN_Rx_Buf[6] == 0x11&&CAN_Rx_Buf[7] == 0x11)
		{
			if((Get_Time() - Pre_time) <500)
			{
				LED_STATUS_UPDOWNLOAD = 0x01u;
				LED_STATUS_ERROR = 0x00u;
			}
			else
			{
				LED_STATUS_ERROR = 0x01u;
				LED_STATUS_UPDOWNLOAD = 0x00u;
			}
		}
	
	}
}
U8 ECU_info_flag = 0x00;
void ID_7AA_function()
{
	switch(SW)
	{
		case 0x01:
			if(CAN_Rx_Buf[3] == 0xB0 && CAN_Rx_Buf[4] == 0x0C)
			{
				State_machine = 0x04;
			}

			if(CAN_Rx_Buf[0] == 0x21)
			{
				if(CAN_Rx_Buf[2] > 0 && CAN_Rx_Buf[2] <= 100)
				LED_STATUS_UPDOWNLOAD = 0x01u;
				else LED_STATUS_ERROR = 0x01u;
			}
			break;
		
		case 0x03:
			if(CAN_Rx_Buf[0] == 0x04)
			{
				State_machine = 0x02;
			}
			if(CAN_Rx_Buf[0] == 0x21)
			{
				if(CAN_Rx_Buf[2] >= 50 && CAN_Rx_Buf[2] <= 100)
				{
					LED_STATUS_UPDOWNLOAD = 0x01;
				}
				else
				{
					LED_STATUS_ERROR = 0x01u;					
				}
			}
			break;
		case 0x04:
			if(CAN_Rx_Buf[0] == 0x23)
			{
				if(CAN_Rx_Buf[4] == 0x00)
				{
					LED_STATUS_UPDOWNLOAD = 0x01;
				}
				else
				{
					LED_STATUS_ERROR = 0x01;
				}
	
			}
			break;

		case 0x06:
			if(CAN_Rx_Buf[2] == 0xF1 && CAN_Rx_Buf[3] == 0x8B)
			{
				if(CAN_Rx_Buf[4] == 0x20 && CAN_Rx_Buf[5] == 0x23 && CAN_Rx_Buf[6] == 0x03 && CAN_Rx_Buf[7] == 0x31)
				{
					ECU_info_flag |=0x01;
				}
			}
			if(CAN_Rx_Buf[3] == 0xF1 && CAN_Rx_Buf[4] == 0x8C)
			{
				if(CAN_Rx_Buf[5] == 0x32 && CAN_Rx_Buf[6] == 0x30 && CAN_Rx_Buf[7] == 0x32)
				{
					ECU_info_flag |=0x02;
				}

			}
			if(CAN_Rx_Buf[2] == 0xF1 && CAN_Rx_Buf[3] == 0x93)
			{
				if(CAN_Rx_Buf[4] == 0x42 && CAN_Rx_Buf[5] == 0x2E && CAN_Rx_Buf[6] == 0x30 && CAN_Rx_Buf[7] == 0x30)
				{
					ECU_info_flag |=0x04;
				}
			}

			if(CAN_Rx_Buf[2] == 0xF1 && CAN_Rx_Buf[3] == 0xA0)
			{
				if(CAN_Rx_Buf[4] == 0x42 && CAN_Rx_Buf[5] == 0x2E && CAN_Rx_Buf[6] == 0x32 && CAN_Rx_Buf[7] == 0x30)
				{
					ECU_info_flag |=0x08;
				}
			}

			if(CAN_Rx_Buf[2] == 0xF1 && CAN_Rx_Buf[3] == 0xA1)
			{
				if(CAN_Rx_Buf[4] == 0x44 && CAN_Rx_Buf[5] == 0x2B && CAN_Rx_Buf[6] == 0x39 && CAN_Rx_Buf[7] == 0x43)
				{
					ECU_info_flag |=0x10;
				}
			}
			
			if(CAN_Rx_Buf[2] == 0xF1 && CAN_Rx_Buf[3] == 0xB0)
			{
				if(CAN_Rx_Buf[4] == 0x01)
				{
					ECU_info_flag |=0x20;
				}
			}

			if(CAN_Rx_Buf[2] == 0xF1 && CAN_Rx_Buf[3] == 0xB1)
			{
				if(CAN_Rx_Buf[4] == 0x42 && CAN_Rx_Buf[5] == 0x2E && CAN_Rx_Buf[6] == 0x32 && CAN_Rx_Buf[7] == 0x30)
				{
					ECU_info_flag |=0x40;
				}
			}
			break;

			if(CAN_Rx_Buf[3] == 0xF1 && CAN_Rx_Buf[4] == 0x87)
			{
				if(CAN_Rx_Buf[5] == 0x39 && CAN_Rx_Buf[6] == 0x35 && CAN_Rx_Buf[7] == 0x35)
				{
					State_machine = 0x02;
					//ECU_info_flag |=0x80;
				}
			}
			if(CAN_Rx_Buf[0] == 0x21 && State_machine == 0x02)
			{
				if(CAN_Rx_Buf[1] == 0x43 && CAN_Rx_Buf[2] == 0x30 && CAN_Rx_Buf[3] == 0x4E&& CAN_Rx_Buf[4] == 0x39&& 
					CAN_Rx_Buf[5] == 0x31&& CAN_Rx_Buf[6] == 0x30&& CAN_Rx_Buf[7] == 0x30)
				{
					ECU_info_flag |=0x80;
				}
			}
			if(State_machine == 0x02)
			{
				if(ECU_info_flag == 0xFF)
				{
					LED_STATUS_UPDOWNLOAD = 0x01u;
					LED_STATUS_ERROR = 0x00u;
				}
				else
				{
					LED_STATUS_UPDOWNLOAD = 0x00u;
					LED_STATUS_ERROR = 0x01u;
				}
			}
			break;
		case 0x07:
			if(CAN_Rx_Buf[3] == 0xB0 && CAN_Rx_Buf[4] == 0x0C)
			{
				State_machine = 0x04;
			}

			if(CAN_Rx_Buf[0] == 0x21)
			{
				if(CAN_Rx_Buf[2] == 0xFF)
				LED_STATUS_UPDOWNLOAD = 0x01u;
				else LED_STATUS_ERROR = 0x01u;
			}
			break;
		default: break;		

	}
	
} 


U8 Pre_print = 0;
void ID_19F_function() // this function to add FP and  registration check
{
	if(SW == 0x01)
	{
		if(CAN_Rx_Buf[3] > Pre_print && State_machine == 0x01)
		{
			Pre_print = CAN_Rx_Buf[3];
			LED_STATUS_UPDOWNLOAD = ~LED_STATUS_UPDOWNLOAD;
		}

		if((CAN_Rx_Buf[2] & 0x04) == 0x04 && State_machine == 0x01)
		{
			LED_STATUS_UPDOWNLOAD = 0x00;
			State_machine = 0x02;
		}
	}
} 

U8  Sleep_flag = 0;
void ID_54F_function() // this function to test sleep
{
	if(SW == 0x00)
	{
		if( (CAN_Rx_Buf[1]&0x10) == 0x00 && Sleep_flag == 0)
		{
			LED_STATUS_ERROR = 0x00u;
			LED_STATUS_UPDOWNLOAD = 0x00u;
			Sleep_flag = 1;
			Pre_time = Get_Time();
		}
		else if( (CAN_Rx_Buf[1] & 0x10) == 0x10)
		{
			//LED_STATUS_ERROR = 0x00u;
			Sleep_flag = 0;

			if((Get_Time() - Pre_time) >= 10000 && ((Get_Time() - Pre_time) <= 14000))
			{
				LED_STATUS_UPDOWNLOAD = 0x01u;
				LED_STATUS_ERROR = 0x00u;
			}
			else
			{
				LED_STATUS_ERROR = 0x01u;
				LED_STATUS_UPDOWNLOAD = 0x00u;
			}
		}
	}
	
}

void Mode_Complete(void)
{
	switch(Transfer_Mode)
	{
		case SWVERSION:
			if ( CAN_Rx_Buf[0] == 0x62 && CAN_Rx_Buf[3] == 0xF1 )
			{
				CAN_Rx_Complete_Flag = 1;       // Indicate Rx Complete
			}	
		break;
		case EXTENDED_SESSION:
			if ( CAN_Rx_Buf[0] == 0x50 && CAN_Rx_Buf[3] == 0x03 )
			{
				CAN_Rx_Complete_Flag = 1;       // Indicate Rx Complete
			}	
		break;
		case PROGRAMMING_SESSION:
			if ( CAN_Rx_Buf[0] == 0x50 && CAN_Rx_Buf[3] == 0x02 )
			{
				CAN_Rx_Complete_Flag = 1;       // Indicate Rx Complete
			}	
		break;
		case CONTROLDTC_OFF:
			if ( CAN_Rx_Buf[0] == 0xC5 && CAN_Rx_Buf[3] == 0x02 )
			{
				CAN_Rx_Complete_Flag = 1;       // Indicate Rx Complete
			}	
		break;
		case REQUEST_SEED:
			if ( CAN_Rx_Buf[0] == 0x67 && CAN_Rx_Buf[3] == 0x01 )
			{
				KeyData[0] = CAN_Rx_Buf[2]+0x10;       // Indicate Rx Complete
				KeyData[1] = CAN_Rx_Buf[5]+0x10;       // Indicate Rx Complete
				KeyData[2] = CAN_Rx_Buf[4]+0x10;       // Indicate Rx Complete
				KeyData[3] = CAN_Rx_Buf[7]+0x10;       // Indicate Rx Complete
				CAN_Rx_Complete_Flag = 1;       // Indicate Rx Complete
			}	
		break;
		case REQUEST_DOWNLOAD_1:
		case REQUEST_DOWNLOAD_2:
			//if ( CAN_Rx_Buf[0] == 0x76 || CAN_Rx_Buf[1] == 0x08 )
			//{
				CAN_Rx_Complete_Flag = 1;       // Indicate Rx Complete
			//}	
		break;
		case SEND_KEY:
			if ( CAN_Rx_Buf[0] == 0x67 && CAN_Rx_Buf[3] == 0x02 )
			{
				CAN_Rx_Complete_Flag = 1;       // Indicate Rx Complete
			}	
		break;
		case ROUTINE_BINARY_UPDATE:
			if ( CAN_Rx_Buf[0] == 0x71 && CAN_Rx_Buf[3] == 0x01 )
			{
				CAN_Rx_Complete_Flag = 1;       // Indicate Rx Complete
			}	
		break;

		default:
			CAN_Rx_Complete_Flag = 0;
		break;
	}
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------

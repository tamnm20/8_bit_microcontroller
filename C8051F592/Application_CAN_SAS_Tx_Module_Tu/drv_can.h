#include "mgr_comm.h"
#include "nm_basic.h"
/* ----- Global Define -------------------------------*/

/*----------------------------------------------------*/

/* ----- Function ------------------------------------*/
void VCan_Init(void);
void VCan_Start(void);
void VCan_Task(void);
void ISR_HuType(CanReceiveHandle rcvObject);
void ISR_NaviOnOff(CanReceiveHandle rcvObject);
void ISR_CountryCfg(CanReceiveHandle rcvObject);
void ISR_LanguageInfo(CanReceiveHandle rcvObject);
void ISR_MdpsType(CanReceiveHandle rcvObject);
void ApplHU_MON_PE_01MsgTimeout(void);
void ApplHU_TYPERxSigTimeout(void);
void ApplCGW4MsgTimeout(void);
void ApplCF_Gway_Navi_On_OffRxSigTimeout(void);
void ApplCGW2MsgTimeout(void);

void ApplCF_Gway_CountryCfgRxSigTimeout(void);
void ApplCLU15MsgTimeout(void);
void ApplCF_Clu_LanguageInfoRxSigTimeout(void);
void ApplMDPS11MsgTimeout(void);
void ApplCF_Mdps_TypeRxSigTimeout(void);
void ApplCF_Mdps_Type_1RxSigTimeout(void);
void ApplSAS1MsgTimeout(void);
void ApplSAS_AngleRxSigTimeout(void);

void ApplNmBasicSwitchTransceiverOn(NMBASIC_CHANNEL_APPLTYPE_ONLY);
void ApplNmBasicEnabledCom(NMBASIC_CHANNEL_APPLTYPE_ONLY);
void ApplNmBasicBusOffEnd(NMBASIC_CHANNEL_APPLTYPE_ONLY);
void ApplNmBasicBusOffRestart(NMBASIC_CHANNEL_APPLTYPE_ONLY);
void ApplNmBasicBusOffStart(NMBASIC_CHANNEL_APPLTYPE_ONLY);
void ApplNmBasicDisabledCom(NMBASIC_CHANNEL_APPLTYPE_ONLY);
void ApplNmBasicFirstBusOffSlow(NMBASIC_CHANNEL_APPLTYPE_ONLY);

enum Target_Info_Rsp
{
   TGT_Info_Rsp_Length = 0,
   TGT_BL_FW_Ver_Low,
   TGT_BL_FW_Ver_High,
   TGT_MCU_Code,
   TGT_BL_Type,
   TGT_Flash_Page_Size_Code,
   TGT_BL_Buffer_Size_Code,
   TGT_CRC_Type,
   TGT_Encryption_Type,
   TGT_App_FW_Start_Addr0,
   TGT_App_FW_Start_Addr1,
   TGT_App_FW_Start_Addr2,
   TGT_App_FW_End_Addr0,
   TGT_App_FW_End_Addr1,
   TGT_App_FW_End_Addr2,
   TGT_CAN_Device_Addr,
   TGT_App_FW_Ver_Low,
   TGT_App_FW_Ver_High,
   TGT_Enum_End_Value
} ;

enum Source_Info_Rsp
{
   SRC_Info_Rsp_Length = 0,
   SRC_MCU_Code,
   SRC_BL_Type,
   SRC_Flash_Page_Size_Code,
   SRC_App_FW_Ver_Low,
   SRC_App_FW_Ver_High,
   SRC_CAN_Device_Addr,
   SRC_App_FW_Start_Addr0,
   SRC_App_FW_Start_Addr1,
   SRC_App_FW_Start_Addr2,
   SRC_App_FW_End_Addr0,
   SRC_App_FW_End_Addr1,
   SRC_App_FW_End_Addr2,
   SRC_Enum_End_Value
} ;

enum PC_Program_Info_Rsp
{
   PCP_Start_Flag = 0,
   PCP_Enum_End_Value = 2
} ;

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------
// Target MCU Sizes
#define PAGE_SIZE               512
#define FLASH_PAGE_SIZE         253

// Signature Bytes
#define SIG_BYTE0             0x3D
#define SIG_BYTE1             0xC2
#define SIG_BYTE2             0xA5
#define SIG_BYTE3             0x1B

// Data Source Commands
#define SRC_CMD_GET_INFO         0x80
#define SRC_CMD_GET_PAGE_INFO    0x81
#define SRC_CMD_GET_PAGE         0x82
#define SRC_CMD_DISP_TGT_INFO    0x83
#define SRC_CMD_DISP_INFO_CODE   0x84
#define SRC_CMD_GET_PAGE2         0x85

// Data Source Response Sizes
#define SRC_CMD_GET_INFO_RX_SZ       14
#define SRC_CMD_GET_PAGE_INFO_RX_SZ  6
#define SRC_CMD_GET_PAGE_RX_SZ       (PAGE_SIZE+2)
#define SRC_CMD_GET_PAGE2_RX_SZ       (FLASH_PAGE_SIZE+2)
#define SRC_CMD_DISP_TGT_INFO_RX_SZ  1
#define SRC_CMD_DISP_INFO_CODE_RX_SZ 1

// Data Source Response Codes
#define SRC_RSP_OK               0x70
#define SRC_RSP_ERROR            0x71
#define SRC_RSP_DATA_END         0x72
#define SRC_RSP_UNKNOWN_CMD      0x73

// Target MCU Commands
#define TGT_CMD_ENTER_BL_MODE    0x90
#define TGT_CMD_GET_INFO         0x91
#define TGT_CMD_SET_FLASH_KEYS   0x92
#define TGT_CMD_SET_ADDR         0x93
#define TGT_CMD_ERASE_PAGE       0x94
#define TGT_CMD_WRITE_FLASH      0x95
#define TGT_CMD_GET_PAGE_CRC     0x96
#define TGT_CMD_WRITE_SIGNATURE  0x97
#define TGT_CMD_SW_RESET         0x98

// Target MCU Response Codes
#define TGT_RSP_OK               0x60
#define TGT_RSP_ERROR            0x61
#define TGT_RSP_BL_MODE          0x62
#define TGT_RSP_APP_MODE         0x63

// PC Program Response Codes
#define PCP_CMD_GET_FLAG         0x50

// PC Program Response Codes Size
#define PCP_CMD_GET_FLAG_RX_SZ      2

//---------------------------------------------
// Error Codes
//---------------------------------------------
#define ERR_TGT_INFO_MISMATCH    0x01
#define ERR_TGT_BL_MODE          0x02
#define ERR_TGT_UNEXPECTED_RSP   0x03
#define ERR_TGT_CRC_MISMATCH     0x04

#define ERR_SRC_INFO_MISMATCH    0x10
#define ERR_SRC_CRC_MISMATCH     0x11
#define ERR_SRC_UNEXPECTED_RSP   0x12

#define ERR_TGT_SRC_INFO_MISMATCH   0x20
#define ERR_NUM_PAGES_MISMATCH      0x21

//---------------------------------------------
// CAN-specific Constants
//---------------------------------------------

// Size of CAN Messages
#define MESSAGE_SIZE   8            // Range is 2-8 bytes
#define TGT_MAX_BYTES_PER_WRITE MESSAGE_SIZE

// Note: The master and target message IDs need to be mirrored (TX vs RX)


// Message Objects to use (range 0-31)
#define MO_TX_BL_CMD    0x10
#define MO_TX_BL_WRITE8 0x11
#define MO_RX_BL_RSP    0x12

#define MO_FUNCTION_REQ 0x13
#define MO_PGS_PHYS_ID  0x14
#define MO_RECEIVE_ID   0x15

#define MO_TX_SAS_ID    0x16
#define MO_TX_CLU_ID    0x17

#define MO_TX_GST_ID    0x18
#define MO_TX_LED_ID    0x19

#define MO_RX_GST_ID    0x1A
#define MO_RX_NM_ID     0x1B
#define MO_RX_07_ID     0x1C
#define MO_RX_08_ID     0x1D
// 11-bit Arbitration Message IDs
#define MSG_ID_TX_BL_CMD      0x0B1 // Transmitted by Master MCU for all BL commands, except:
#define MSG_ID_TX_BL_WRITE8   0x1B1 // Transmitted by Master MCU for the 8-byte Write command
#define MSG_ID_RX_BL_RSP      0x2B1 // Received by Master MCU (responses from target MCU)

#define MSG_ID_FUNCTION_REQ   0x7DF // Transmitted by Master MCU for the 8-byte Write command
#define MSG_ID_PGS_PHYS_ID    0x796 // Received by Master MCU (responses from target MCU)
#define MSG_ID_RECEIVE_ID	  0x79E // Received by Master MCU (responses from target MCU)

#define MSG_ID_TX_SAS         0x2B0 // Transmitted by Master MCU for the 8-byte Write command
#define MSG_ID_TX_CLU         0x52A // Transmitted by Master MCU for the 8-byte Write command

#define MSG_ID_TX_GST         0x7A2 // Transmitted by Master MCU for the 8-byte Write command
#define MSG_ID_TX_LED         0x2DF // Transmitted by Master MCU for the 8-byte Write command

#define MSG_ID_RECEIVE_GST	  0x7AA // Received by Master MCU (responses from target MCU)
#define MSG_ID_RECEIVE_NM	  0x54F // Received by Master MCU (responses from target MCU)
#define MSG_ID_RECEIVE_07	  0x19F
#define MSG_ID_RECEIVE_08	  0x2F2
//diagnostic

#define DEFAULT_MODE 		 	0x00
#define STANDARD_MODE 		 	0x01
#define SWVERSION	  		 	0x02
#define EXTENDED_MODE 		 	0x03
#define EXTENDED_SESSION 	 	0x04
#define CONTROLDTC_OFF 		 	0x05
#define COMM_CONTROL_DISABLE 	0x06
#define PROGRAMMING_SESSION  	0x07
#define REQUEST_SEED		 	0x08
#define SEND_KEY			 	0x09
#define ROUTINE_BINARY_UPDATE	0x0A
#define REQUEST_DOWNLOAD_1		0x0B
#define REQUEST_DOWNLOAD_2		0x0C
#define REQUEST_TRANSFER_EXIT	0x0D
#define COMM_CONTROL_ENABLE		0x0E
#define ECU_RESET				0x0F
#define COMM_CONTROL_DISABLE2	0x10
//-----------------------------------------------------------------------------
// Header File Preprocessor Directive
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------

/*----------------------------------------------------*/


/* ----- Global Value --------------------------------*/

/*----------------------------------------------------*/


/* ----- Extern Function -----------------------------*/

/*----------------------------------------------------*/

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------

// "request_response" parameter values (for TGT_Enter_BL_Mode function)
#define IGNORE_RESPONSE 0x00
#define REQUEST_RESPONSE 0x01

//------------------------
// Bit Definition Masks
//------------------------

// CAN0STAT
#define BOff  0x80                     // Busoff Status
#define EWarn 0x40                     // Warning Status
#define EPass 0x20                     // Error Passive
#define RxOk  0x10                     // Receive Message Successfully
#define TxOk  0x08                     // Transmitted Message Successfully
#define LEC   0x07                     // Last Error Code

// CAN0INTERRUPT
#define  STATUS_CHANGE  0x8000U
#define  END            0

// CAN0MESSAGECONTROL MASK
#define  NEWDATA        0x8000U
#define  EOB            0x0080U

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
void CAN_Init (void);

U8 TGT_Enter_BL_Mode (U8 request_response, U8 CAN_dev_addr);
U8 TGT_Get_Info (U8 *target_info);
U8 TGT_Set_Flash_Keys (U8 flash_key0, U8 flash_key1);
U8 TGT_Erase_Page (void);
U8 TGT_Write_Flash (U8 *buf, U16 index, U8 numbytes,U8 Page_Num);
U8 TGT_Get_Page_CRC (U16 *target_page_crc);
U8 TGT_Write_Signature (U8 sig_byte0, U8 sig_byte1, U8 sig_byte2, U8 sig_byte3);
void TGT_SW_Reset (void);
//U8 Transfer_SAS_Data (U8 SAS_Low, U8 SAS_High);
void Usr_Can0_Isr();

U8 SEND_7DF(U8 mode);
void SEND_796(U8 mode);
void SEND_2B0(U8 SAS_Low, U8 SAS_High);
void SEND_52A(U8 LANG_Info);
void SEND_GST(U8* TX_DATA[8]);
void ID_54F_function();
void ID_19F_function();
void ID_7AA_function();
void ID_2F2_function();
U16 RX_Mes(U16 Interrupt_ID);
void SEND_LED(U8 TX_DATA[]);
//-----------------------------------------------------------------------------
// Header File Preprocessor Directive










/*_____ I N C L U D E __________________________________________*/
#include "compiler_defs.h"
#include "C8051F580_defs.h"
#include "global_define.h"
#include "mgr_mcu.h"
#include "drv_mcu.h"
#include "drv_timer.h"
#include "drv_mem.h"
#include "drv_spi.h"
#include "mgr_diag.h"
#include "string.h"
#include "desc.h"
#include "nm_basic.h"
#include "il_inc.h"
#include "can_def.h"
#include "v_inc.h"
/*--------------------------------------------------------------*/
static SEG_XDATA volatile U8 g_DiagMode;
SEG_XDATA volatile tMsg_Update tMsg_Update_s;
static SEG_XDATA volatile U32 Update_Type = 0x00U;
static SEG_XDATA volatile U32 gAddr = 0x00U;
static SEG_XDATA volatile U8 IGN_ON_Status = 0x00;
static SEG_XDATA volatile U8 DTC_Set_Off = FALSE;
static SEG_XDATA volatile U32 Update_size_addr = 0x00;
static SEG_XDATA volatile U8 DTC_Write_Set = FALSE;
extern SEG_XDATA U8 EEPROM_Update_Mode;

void Init_DiagTask(void)
{	
	SEG_XDATA volatile U8 Read_DTC_Buf[6];
	SEG_XDATA volatile U8 ret=FALSE;
	SEG_XDATA volatile U8 i;

	tMsg_Update_s.update_set = (U8)0x00U;
	tMsg_Update_s.erase_set = (U8)0x00U;
	tMsg_Update_s.write_cnt = (U32)0x00U;
	tMsg_Update_s.total_write_cnt = (U32)0x00U;
	tMsg_Update_s.size = (U32)0x00U;

	memset(tMsg_Update_s.Write_Buf,0x00,sizeof(tMsg_Update_s.Write_Buf));

	g_DiagMode = OPERATE_STANDBY;
}


void Operate_DiagTask()
{
	SEG_XDATA U8 *pErr;
	switch(g_DiagMode)
	{
		case OPERATE_STANDBY:
			Diag_StandBy(pErr);
			//if ( *pErr == 0x01 ) {Diag_Reset();}
			//else {g_CiuMode = OPERATE_INTERINIT;}
			g_DiagMode = OPERATE_INTERINIT;
		break;
		case OPERATE_INTERINIT:
			Diag_InterInit(pErr);
			//if ( *pErr == 0x01 ) {Diag_Reset();}
			//else {g_CiuMode = OPERATE_IDLE;}
			g_DiagMode = OPERATE_IDLE;
		break;
		case OPERATE_IDLE:
			Diag_Idle(pErr);
			//if ( *pErr == 0x01 ) {Diag_Reset();}
			//else {g_CiuMode = OPERATE_RUNNING;}
			g_DiagMode = OPERATE_RUNNING;
		break;
		case OPERATE_RUNNING:
			Diag_Running(pErr);
			//if ( *pErr == 0x01 ) {Diag_Reset();}
			//else {g_CiuMode = OPERATE_RUNNING;}
			g_DiagMode = OPERATE_RUNNING;
		break;
	}
}

void Diag_StandBy(U8 *pError)
{
	*pError = 0x00U;
}

void Diag_InterInit(U8 *pError)
{
	*pError = 0x00U;
}

void Diag_Idle(U8 *pError)
{
	*pError = 0x00U;
}

void Diag_Running(U8 *pError)
{
	SEG_XDATA U8 ID = SYS_MANU_DATE;
	SEG_XDATA U8 On_Time,j;
	U8 Write_temp_Cnt = 0x00;
	U8 EA_SAVE = EA;
	SEG_XDATA U32 i;
	static SEG_XDATA U8 mode = 0x00U;
}

#define FIRMWARE_SIZE_ADDR			0x2E000U
#define TUNING_SIZE_ADDR			0x2D000U
void Diag_Ecu_Reset(void)
{
	SEG_XDATA U8 Buf[4] = {0x00U,0x00U,0x00U,0x00U};
	static SEG_XDATA volatile U8 Write_Buf[256];
	if ( EEPROM_Update_Mode == TRUE)
	{
		EEPROM_Update_Mode = FALSE;
		Buf[0] = (U8)(gAddr >> 24U);
		Buf[1] = (U8)(gAddr >> 16U);
		Buf[2] = (U8)(gAddr >> 8U);
		Buf[3] = (U8)gAddr;

		Flash_EraseSector(Update_size_addr);	
		Flash_Write(Update_size_addr,Buf,(U16)4);
	}
	

	//Delay_Time_Set(TID_DIAG_ECU_RESET,DT_DIAG_ECU_RESET);
	LED_STATUS_UPDOWNLOAD = 0x01U;
}

void Firmware_Update(void)
{
	Delay_Time_Set(TID_FRAME_COUNT,DT_FRAME_COUNT);
	LED_STATUS_UPDOWNLOAD = 0x01U;
	EEPROM_Update_Mode = TRUE;
	MCU_F_ENABLE = 0x01U;
	Update_size_addr = FIRMWARE_SIZE_ADDR;
	Update_Type = FIRMWARE;
	EIE1 &= (U8)(~0x04U);                       // Enable ADC0 conversion complete int.
	EIE1 &= (U8)(~0x01U);
}

void Diag_Eeprom_Update(void)
{
	Delay_Time_Set(TID_FRAME_COUNT,DT_FRAME_COUNT);
	LED_STATUS_UPDOWNLOAD = 0x01U;
	EEPROM_Update_Mode = TRUE;
	MCU_F_ENABLE = 0x01U;
	Update_size_addr = TUNING_SIZE_ADDR;
	Update_Type = TUNING;
	EIE1 &= (U8)(~0x04U);                       // Enable ADC0 conversion complete int.
	EIE1 &= (U8)(~0x01U);
}

void Diag_Write_Transfer_Data(U8 *Buf)
{
	SEG_XDATA U32	 address = 0x00U;
	static SEG_XDATA U32 cnt   = 0U;
	static SEG_XDATA U32 erase_cnt   = 0U;
	static SEG_XDATA U32 lotation = 0x01U;
	static SEG_XDATA volatile U8 Buf1[256] = {0,};
	static SEG_XDATA volatile U8 Buf2[256] = {0,};
	static SEG_XDATA volatile U8 buf1_index = 253U;
	static SEG_XDATA volatile U8 buf2_index = 3U;
	static SEG_XDATA volatile U8 loop_index = 0U;
	SEG_XDATA U8 Write_Buf[256];
	SEG_XDATA volatile U8 On_Time;

	On_Time = Delay_Time_Get(TID_FRAME_COUNT);
	if ( On_Time == TRUE)
	{
		if (EEPROM_Update_Mode == TRUE)
		{
			if (LED_STATUS_UPDOWNLOAD == 0x00U)
			{
				LED_STATUS_UPDOWNLOAD = 0x01U;
			}
			else
			{
				LED_STATUS_UPDOWNLOAD = 0x00U;
			}
		}
	}

	if ((cnt % (U32)16) == (U32)0)
	{
		Flash_EraseSector((erase_cnt*(U32)0x1000U)+Update_Type);	
		erase_cnt++;
		Wait_ms(100U);
	}
	if ( cnt == 0x00U)
	{
		memset(Buf1, (char)0xFFU ,256U);	
		memset(Buf2, (char)0xFFU ,256U);	
		memcpy(Buf1,&Buf[1U],253U);
	}
	else
	{
		if ( loop_index == 0U)
		{
			if ( buf1_index == 1U)
			{
				memcpy(&Buf1[buf1_index],&Buf[1U],253U);
				//memcpy(Buf1,Buf,256U);
				buf1_index = 254U;
				buf2_index = 2U;
				loop_index = 1U;
				lotation++;
			}
			else
			{
				memcpy(Buf2,&Buf[1U],253U);
				memcpy(&Buf1[buf1_index],Buf2,buf2_index);
				
				address = ((cnt-lotation)*(U32)256) + Update_Type;
				memcpy(Write_Buf,Buf1,256U);

				Flash_Write(address,Write_Buf,(U16)256);

				memset(Buf1, (char)0xFFU ,256U);	
				memcpy(Buf1,&Buf2[buf2_index],buf1_index);
				memset(Buf2, (char)0xFFU ,256U);	
				buf1_index-=3U;
				buf2_index+=3U;
			}
		}
		
		else if ( loop_index == 1U)
		{
			if ( buf1_index == 2U)
			{
				memcpy(&Buf1[buf1_index],(Buf+1U),253U);
				buf1_index = 255U;
				buf2_index = 1U;
				loop_index = 2U;
				lotation++;
			}
			else
			{	
				memcpy(Buf2,&Buf[1U],253U);
				memcpy(&Buf1[buf1_index],Buf2,buf2_index);
				
				address = ((cnt-lotation)*(U32)256) + Update_Type;
				memcpy(Write_Buf,Buf1,256U);

				Flash_Write(address,Write_Buf,(U16)256);

				memset(Buf1, (char)0xFFU ,256U);	
				memcpy(Buf1,&Buf2[buf2_index],buf1_index);
				memset(Buf2, (char)0xFFU ,256U);	
				buf1_index-=3U;
				buf2_index+=3U;
			}
				
		}
		else if ( loop_index == 2U )
		{
			if ( buf1_index == 0U)
			{
				memcpy(&Buf1[buf1_index],&Buf[1U],253U);
				buf1_index = 253U;
				buf2_index = 3U;
				loop_index = 0U;
				lotation++;
			}
			else
			{
				memcpy(Buf2,&Buf[1U],253U);
				memcpy(&Buf1[buf1_index],Buf2,buf2_index);
				
				address = ((cnt-lotation)*(U32)256) + Update_Type;
				memcpy(Write_Buf,Buf1,256U);

				Flash_Write(address,Write_Buf,(U16)256);

				memset(Buf1, (char)0xFFU ,256U);	
				memcpy(Buf1,&Buf2[buf2_index],buf1_index);
				memset(Buf2, (char)0xFFU ,256U);	
				buf1_index-=3U;
				buf2_index+=3U;
			}
		}
		else
		{
		}
		
	}
	cnt++;
	gAddr++;
}



void Diag_Read_Sys(U8 ID, U8 *Buf,U8 Length)
{
}

void Diag_Request_Download(U8 *Buf,U8 Length)
{
	U8 erase_buf[8];
	tMsg_Update_s.erase_set = 0x01;
	tMsg_Update_s.size = Buf[5] << 16U | Buf[6] << 8U | Buf[7] ;
}

void Diag_Exit_Update(void)
{
}

void Diag_Check_Programming(void)
{
	FLASH_PageErase(SIGNITURE_1_ADDR);
	FLASH_ByteWrite(SIGNITURE_1_ADDR,SIGNITURE_1_BYTE);
	FLASH_ByteWrite(SIGNITURE_2_ADDR,SIGNITURE_2_BYTE);
	FLASH_ByteWrite(SIGNITURE_3_ADDR,SIGNITURE_3_BYTE);
	FLASH_ByteWrite(SIGNITURE_4_ADDR,SIGNITURE_4_BYTE);
}

void SYS_Flash_Read(U8 ID,U8 *Read_Buf,U8 Length)
{
	SEG_XDATA volatile U8 i,Cs;
	SEG_XDATA volatile U8 Buf[SYS_CODE_SIZE+1U] = {0,};

	memset(Buf, (char)0x00U ,Length);

	FLASH_Read_Buf(Buf,(FLADDR)SYSINFO_ADDRESS,sizeof(Buf),BANK1);

	for (i = 0; i < SYS_CODE_SIZE; i++)
	{
		Cs ^= Buf[i];
	}
	Cs = Buf[SYS_CODE_SIZE];
	if ( Cs == Buf[SYS_CODE_SIZE])
	{
		switch(ID)
		{
			case SYS_HMC_SPEC:
				memcpy(Read_Buf,&Buf[0U],Length);
			break;
			case SYS_PART_NUMBER:
				memcpy(Read_Buf,&Buf[SYS_PART_NUMBER_L],Length);
			break;
			case SYS_MANU_DATE:
				memcpy(Read_Buf,&Buf[SYS_MANU_DATE_L],Length);
			break;
			case SYS_HW_VERSION:
				memcpy(Read_Buf,&Buf[SYS_HW_VERSION_L],Length);
			break;
			case SYS_SW_VERSION:
				memcpy(Read_Buf,&Buf[SYS_SW_VERSION_L],Length);
			break;
			case SYS_CAN_VERSION:
				memcpy(Read_Buf,&Buf[SYS_CAN_VERSION_L],Length);
			break;
			default:
			break;
		}
	}
}

U16   Diag_Get_Time(void)
{
	U16 Cur_Time;
	Cur_Time = Get_Time();
	return Cur_Time;
}

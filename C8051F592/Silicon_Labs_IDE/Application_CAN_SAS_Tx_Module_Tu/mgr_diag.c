/*_____ I N C L U D E __________________________________________*/
#include "compiler_defs.h"
#include "C8051F580_defs.h"
#include "global_define.h"
#include "drv_mcu.h"
#include "drv_timer.h"
#include "drv_spi.h"
#include "drv_mem.h"
#include "drv_spi.h"
#include "mgr_diag.h"
#include "mgr_comm.h"
#include "mgr_mcu.h"
#include "string.h"

#include "desc.h"
#include "nm_basic.h"
#include "il_inc.h"
#include "main.h"
/*--------------------------------------------------------------*/

static SEG_XDATA volatile U8 IGN_ON_Status = 0x00;
static SEG_XDATA volatile U8 DTC_Set_Off = FALSE;
static SEG_XDATA volatile U32 Update_size_addr = 0x00;
static SEG_XDATA volatile U8 DTC_Write_Set = FALSE;
extern SEG_XDATA U8 EEPROM_Update_Mode;
static SEG_XDATA volatile U32 Update_Type = 0x00U;
static SEG_XDATA volatile U32 gAddr = 0x00U;

void Init_DiagTask(void)
{	
}

void Clear_DTC_Struct(void)
{
}

void Operate_DiagTask(void)
{
	SEG_XDATA U8 ID = SYS_MANU_DATE;
	SEG_XDATA U8 On_Time,ret;
	U8 Reserved_Address;

	On_Time = Delay_Time_Get(TID_DIAG_ECU_RESET);
	if ( On_Time == TRUE)
	{
		MCU_Reset();
	}
	On_Time = Delay_Time_Get(TID_FIRME_UPDATE);
	if ( On_Time == TRUE)
	{
		PSBANK = 0x30;
		Reserved_Address = *(U8 SEG_CODE*)(0xFC00U);
	}

}
void Record_DTC_Error(U8 ID)
{
}

void Record_DTC_Clear(U8 ID)
{
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
	

	Delay_Time_Set(TID_DIAG_ECU_RESET,DT_DIAG_ECU_RESET);
	
}

void Diag_Clear_DTC(void)
{	
}

U8 Diag_Read_Dtc(U8 index)
{
}

void Diag_Read_Sys(U8 ID, U8 *Buf,U8 Length)
{

}

void Firmware_Update(void)
{
	EEPROM_Update_Mode = TRUE;
	MCU_F_ENABLE = 0x01U;
	Update_size_addr = FIRMWARE_SIZE_ADDR;
	Update_Type = FIRMWARE;
	EIE1 &= (U8)(~0x04U);                       // Enable ADC0 conversion complete int.
	EIE1 &= (U8)(~0x01U);
}

void Diag_Eeprom_Update(void)
{
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


void Diag_Sensor_Reset(void)
{
}

void Diag_Guid_OnOff(U8 OnOff)
{
}

void Diag_Exit_Update(void)
{
	//MCU_Reset();
}

void Diag_DTC_Set_On(void)
{
}

void Diag_DTC_Set_Off(void)
{
}

void Flash_DTC_Write(void)
{
}
void Flash_DTC_Read(void)
{
}

void Diag_Write_Sys(U8 *Write_Buf,U8 Length)
{
}

void Diag_Extra_Data_Process(U8 *Write_Buf)
{
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

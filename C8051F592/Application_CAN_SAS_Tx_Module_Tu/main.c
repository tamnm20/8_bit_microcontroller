/****************************************************************************
* NAME: main.c
*----------------------------------------------------------------------------
* Copyright (c) MCNEX Inc.
*----------------------------------------------------------------------------
* CREATED_BY: Jung Gu Seo
* CREATION_DATE: 2011/03/14
* $Author: dglee $
* $Revision: 1.0 $
* $Date: 2011/03/14 $
*----------------------------------------------------------------------------
* PURPOSE:
* - 
*****************************************************************************/

/*_____ I N C L U D E __________________________________________*/

#include "compiler_defs.h"
#include "C8051F580_defs.h"
#include "Global_Define.h"
#include "mgr_mcu.h"
#include "mgr_comm.h"
#include "mgr_diag.h"
#include "drv_can.h"
#include "drv_mcu.h"
#include "drv_timer.h"
#include "string.h"
#include "main.h"

static SEG_XDATA U8 AMUX_INPUT = 1U;
extern SEG_XDATA volatile U8 Timeout;
U8 main(void);

INTERRUPT_PROTO (TIMER2_ISR, INTERRUPT_TIMER2);

extern SEG_XDATA tMsg_Global_Tick g_Global_Tick_Msg;

SEG_XDATA U8 EEPROM_Update_Mode = FALSE;

/*****************************************************************************
FUNCTION:
  - main

Purpose:
  - 
*****************************************************************************/

U8 main(void)
{ 
	SEG_XDATA U8 On_Time=0x00U;
	Init_McuTask();
	Init_CommTask();

	Delay_Time_Set(TID_10ms_TIMER, DT_10ms_TIMER);
	Delay_Time_Set(TID_100ms_TIMER, DT_100ms_TIMER);
	Delay_Time_Set(TID_200ms_TIMER, DT_200ms_TIMER);
	Delay_Time_Set(TID_500ms_TIMER, DT_500ms_TIMER);
	Delay_Time_Set(TID_2000ms_TIMER, DT_2000ms_TIMER);

	while(1)
	{
		if ( EEPROM_Update_Mode == FALSE)
		{
			Operate_CommTask();
			Operate_McuTask();
			Operate_DiagTask();
		}
	}
}

INTERRUPT(TIMER2_ISR, INTERRUPT_TIMER2)
{
	SEG_XDATA U8 i = 0x00U;
	static SEG_XDATA volatile U16 vcan_count = 0x00U;
	TF2H = 0x00U;

	g_Global_Tick_Msg.Tick_1ms++;
		
	if (Timeout == 1)
	{
		vcan_count++;
		if ( vcan_count >= 10000U )
		{
			vcan_count = 0x00U;
			//LED_STATUS_ERROR = 0x01U;
		}
	}
	else
	{
		//LED_STATUS_ERROR = 0x00U;
		vcan_count = 0;
	}

	if ( g_Global_Tick_Msg.Over_Set == FALSE)
	{
		if ( g_Global_Tick_Msg.Tick_1ms >= 0xFFFFU )
		{
			if ( g_Global_Tick_Msg.Tick_1ms >= g_Global_Tick_Msg.Limit )
			{
				g_Global_Tick_Msg.Tick_1ms = (U32)0;
				for ( i = (U8)0; i <= TID_COUNT; i++)
				{
					ga_tCAN_Time_Msg[i].End_Time = (U32)0;
				}				
			}
			else
			{
				g_Global_Tick_Msg.Over_Set = TRUE;
				g_Global_Tick_Msg.Limit = (volatile U32)(g_Global_Tick_Msg.Limit - 0xFFFFU);
			}
		}
	}
	else
	{
		g_Global_Tick_Msg.Limit--;
		if ( g_Global_Tick_Msg.Limit <= (U8)0 )
		{
			g_Global_Tick_Msg.Tick_1ms = (U16)0;
			g_Global_Tick_Msg.Over_Set = FALSE;
			for ( i = 0; i <= TID_COUNT; i++)
			{
				ga_tCAN_Time_Msg[i].End_Time -= ga_tCAN_Time_Msg[i].Cur_Time;
			}
		}
	}
}

/* end of file */

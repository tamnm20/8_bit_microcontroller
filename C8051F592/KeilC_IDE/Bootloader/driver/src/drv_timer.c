#include "drv_timer.h"


xdata U32 num = 0;

SEG_XDATA tMsg_Global_Tick g_Global_Tick_Msg;
SEG_XDATA tMsg_Time_s	ga_tCAN_Time_Msg[16];

void TIMER2_Init (U16 counts)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = ACTIVE_PAGE;

   TMR2CN  = 0x00;                     // Stop Timer2; Clear TF2;
                                       // use SYSCLK/12 as timebase
   CKCON  &= ~0x60;                    // Timer2 clocked based on T2XCLK;

   TMR2RL  = -counts;                  // Init reload values
   TMR2    = 0xFFFF;                   // Set to reload immediately
   ET2     = 1;                        // Enable Timer2 interrupts
   TR2     = 1;                        // Start Timer2

   SFRPAGE = SFRPAGE_save;
}

void Delay_Time_Set(U8 ID, U16 Delay_Time)
{
	//xdata volatile U8 Set_Delay_Time = 0x00U;
	
	ga_tCAN_Time_Msg[ID].Cur_Time = g_Global_Tick_Msg.Tick_1ms;
	ga_tCAN_Time_Msg[ID].Delay_Time = (U32)Delay_Time;
	ga_tCAN_Time_Msg[ID].Set = TRUE;
	
	ga_tCAN_Time_Msg[ID].End_Time = (ga_tCAN_Time_Msg[ID].Cur_Time + ga_tCAN_Time_Msg[ID].Delay_Time);
	
	if ( (g_Global_Tick_Msg.Over_Set == FALSE) && (g_Global_Tick_Msg.Limit <= ga_tCAN_Time_Msg[ID].End_Time) )
	{
		g_Global_Tick_Msg.Limit = ga_tCAN_Time_Msg[ID].End_Time;
	}
}

//U16 Get_Time(void)
//{
//	return (U16)g_Global_Tick_Msg.Tick_1ms;
//}

U8 Delay_Time_Get(U8 ID)
{
	U8 ret = (U8)0;
	U8 i   = (U8)0;
	U8 cnt = (U8)0;

	ga_tCAN_Time_Msg[ID].Cur_Time = g_Global_Tick_Msg.Tick_1ms;
	if (ga_tCAN_Time_Msg[ID].Set == TRUE )
	{
		if( ga_tCAN_Time_Msg[ID].Cur_Time >= ga_tCAN_Time_Msg[ID].End_Time )
		{
			Delay_Time_Set(ID,(U16)ga_tCAN_Time_Msg[ID].Delay_Time);
			ret = TRUE;
		}
	}
	return ret;
}

//void delayms(int time)
//{
//	num = 0;
//	while(num < time);
//}

INTERRUPT(Timer2_ISR, INTERRUPT_TIMER2)
{
	xdata U8 i = 0x00u;
//	static xdata volatile U16 vcan_count = 0x00u;
   TF2H = 0;                           // Clear Timer2 interrupt flag
   num++;
	g_Global_Tick_Msg.Tick_1ms++;
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
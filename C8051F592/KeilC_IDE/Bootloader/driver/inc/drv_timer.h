#ifndef DRV_TIMER_H
#define DRV_TIMER_H

#include <C8051F580.h> 
#include <compiler_defs.h>
#include "Global.h"

#define TID_COUNT					0x0EU

typedef struct {
	U8	Set;
	U32 Delay_Time;
	U32 Cur_Time;
	U32 End_Time;
}tMsg_Time_s;

typedef struct {
	U32 Tick_1ms;
	U32	Limit;
	U8	Over_Set;
}tMsg_Global_Tick;



void TIMER2_Init (U16 counts);
void Delay_Time_Set(U8 ID, U16 Delay_Time);
U16 Get_Time(void);
U8 Delay_Time_Get(U8 ID);
extern SEG_XDATA tMsg_Global_Tick g_Global_Tick_Msg;

#endif 

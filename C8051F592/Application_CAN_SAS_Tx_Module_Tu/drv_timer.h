#ifndef DRV_TIMER_H
#define DRV_TIMER_H

/* ----- Global Define -------------------------------*/

#define TID_10ms_TIMER				0x01U
#define TID_50ms_TIMER				0x02U
#define TID_100ms_TIMER				0x03U
#define TID_200ms_TIMER				0x04U
#define TID_500ms_TIMER				0x05U
#define TID_1000ms_TIMER			0x06U
#define TID_2000ms_TIMER		   	0x07U
#define TID_DIAG_ECU_RESET			0x08U
#define TID_FIRME_UPDATE			0x09U
#define TID_SENSOR_RESET			0x0AU
#define TID_CHECKSTATUS_LOOP		0x0BU
#define TID_ADC_CHANGE_TIMER		0x0CU
#define TID_I2C_BUSY_CHECK			0x0DU
#define TID_COUNT					0x0EU

/*----------TIMER DELAY-------------*/
#define DT_10ms_TIMER				 10U
#define DT_50ms_TIMER				 50U
#define DT_100ms_TIMER				100U
#define DT_200ms_TIMER	    		200U
#define DT_500ms_TIMER		    	500U
#define DT_1000ms_TIMER	     	   1000U
#define DT_2000ms_TIMER		       300U
#define DT_DIAG_ECU_RESET		    500U
#define DT_FIRME_UPDATE				 30U
#define DT_SENSOR_RESET				500U
#define DT_SENSOR_IDLE_PERIOD		300U
#define DT_CHECKSTATUS_LOOP			 30U
#define DT_ADC_CHANGE_TIMER		     10U
#define DT_I2C_COMM_CHECK		     10U
#define DT_I2C_BUSY_CHECK			 50U
/*----------------------------------------------------*/
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

/* ----- Function ------------------------------------*/
void Timer0_Init(void);
void Timer1_Init(void);
#if defined(TIMER2)
void Timer2_Init(void);
#endif
void Timer3_Init(void);
void Timer4_Init(void);
void Timer5_Init(void);
void TIMER1__Init (void);
void Wait_ms (U16 ms);
void Global_Timer_Init(void);
void Delay_Time_Set(U8 ID, U16 Delay_Time);
U8   Delay_Time_Get(U8 ID);
void Delay_Time_Expire(U8 ID);
U16 Get_Time(void);
/*----------------------------------------------------*/

/* ----- Extern Function -----------------------------*/
extern SEG_XDATA tMsg_Global_Tick g_Global_Tick_Msg;
extern SEG_XDATA tMsg_Time_s	ga_tCAN_Time_Msg[TID_COUNT];
/*----------------------------------------------------*/

/* ----- Global Value --------------------------------*/
/*----------------------------------------------------*/

#endif

/*_____ I N C L U D E __________________________________________*/
#include "compiler_defs.h"
#include "C8051F580_defs.h"
#include "Global_Define.h"
#include "drv_timer.h"
#include "drv_can.h"
#include "drv_mcu.h"
#include "mgr_comm.h"
#include "desc.h"
#include "nm_basic.h"
#include "il_inc.h"
typedef vuint8_least DescSvcInstIndex;
extern DescSetState(DescSvcInstIndex svcInstHandle);
/*--------------------------------------------------------------*/
SEG_XDATA volatile U8 g_CommMode;
extern DescOemCommControlInfo  g_descCommControlInfo;
void Init_CommTask(void)
{	
	Delay_Time_Set(TID_VCAN,DT_VCAN);
	g_CommMode = OPERATE_STANDBY;
}

void Operate_CommTask()
{
	SEG_XDATA U8 *pErr;
	switch(g_CommMode)
	{
		case OPERATE_STANDBY:
			Comm_StandBy(pErr);
			//if ( *pErr == 0x01 ) {MCU_Reset();}
			//else {g_CommMode = OPERATE_INTERINIT;}
			g_CommMode = OPERATE_INTERINIT;
		break;
		case OPERATE_INTERINIT:
			Comm_InterInit(pErr);
			//if ( *pErr == 0x01 ) {MCU_Reset();}
			//else {g_CommMode = OPERATE_IDLE;}
			g_CommMode = OPERATE_IDLE;
		break;
		case OPERATE_IDLE:
			Comm_Idle(pErr);
			//if ( *pErr == 0x01 ) {MCU_Reset();}
			//else {g_CommMode = OPERATE_RUNNING;}
			g_CommMode = OPERATE_RUNNING;
		break;
		case OPERATE_RUNNING:
			Comm_Running(pErr);
			//if ( *pErr == 0x01 ) {MCU_Reset();}
			//else {g_CommMode = OPERATE_RUNNING;}
			g_CommMode = OPERATE_RUNNING;
		break;
	}
}


void Comm_StandBy(U8 *pError)
{
	VCan_Init();
	*pError = 0x00U;
}

void Comm_InterInit(U8 *pError)
{

	VCan_Start();
	//Delay_Time_Set(TID_SESSION_C_COUNT,DT_SESSION_C_COUNT);	
	*pError = 0x00U;
}

void Comm_Idle(U8 *pError)
{

	*pError = 0x00U;
}

void Comm_Running(U8 *pError)
{	
	static SEG_XDATA U16 Count = 0x00;
	DescStateGroup          checkSessionState;
	DescSvcInstIndex        reqSvcInstHandle;

	SEG_XDATA U8 On_Time;

	On_Time = Delay_Time_Get(TID_VCAN);
	if ( On_Time == TRUE )
	{	
		VCan_Task();
		ApplNmBasicDisabledCom(NMBASIC_CHANNEL_APPLPARA_ONLY);
	}
	
	//On_Time = Delay_Time_Get(TID_SESSION_C_COUNT);
	if ( On_Time == TRUE)
	{
		checkSessionState = kDescStateSessionExtendedDiagnosticMode;
		DescSetStateSession(checkSessionState);
		checkSessionState = kDescStateSessionECUProgrammingMode;
		DescSetStateSession(checkSessionState);
		checkSessionState = kDescStateSecurityAccessUnlockedL1;
		DescSetStateSecurityAccess(checkSessionState);
	}
	
	*pError = 0x00U;
}

void VCan_Restart(void)
{
	Delay_Time_Expire(TID_VCAN);
	VCan_Init();
	VCan_Start();
	Delay_Time_Set(TID_VCAN);
	//Init_CommTask();

}
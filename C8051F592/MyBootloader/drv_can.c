/*_____ I N C L U D E __________________________________________*/
#include "compiler_defs.h"
#include "C8051F580_defs.h"
#include "Global_Define.h"
#include "drv_can.h"
#include "drv_timer.h"
#include "drv_mcu.h"
#include "mgr_comm.h"
#include "desc.h"
#include "nm_basic.h"
#include "il_inc.h"
#include <math.h>
#include "can_def.h"
/*--------------------------------------------------------------*/
SEG_XDATA U8 checking_bus_off  = 0x00U;

void VCan_Init(void)
{
	EIE2 |= 0x02U;
	EA = (U8)0;

	NmBasicInitPowerOn();
	CanInitPowerOn();
	IlInitPowerOn();
	TpInitPowerOn();
	DescInitPowerOn(0);

	EA = (U8)1;
}

void VCan_Start(void)
{
//	IlTxStart();
	IlRxStart();
	NmBasicStart();

	//IlPutTxCAM_RearCameraReq(0x03U);
	VCan_Task();
}

void VCan_Task()
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
}
void ApplNmBasicBusOffEnd(NMBASIC_CHANNEL_APPLTYPE_ONLY)
{
}
void ApplNmBasicBusOffRestart(NMBASIC_CHANNEL_APPLTYPE_ONLY)
{	
}
void ApplNmBasicBusOffStart(NMBASIC_CHANNEL_APPLTYPE_ONLY)
{
}
void ApplNmBasicDisabledCom(NMBASIC_CHANNEL_APPLTYPE_ONLY)
{
}
void ApplNmBasicFirstBusOffSlow(NMBASIC_CHANNEL_APPLTYPE_ONLY)
{
}

void ApplIlFatalError(vuint8 errorNumber){}

vuint8 ApplNmBasicSwitchTransceiverOff(NMBASIC_CHANNEL_APPLTYPE_ONLY){}

void TP_API_CALLBACK_TYPE ApplTpFatalError(canuint8 errorNumber){}

void ISR_SAS(CanReceiveHandle rcvObject){}

/* CODE CATEGORY 1 START */
void ISR_HuType(CanReceiveHandle rcvObject){}
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
void ISR_NaviOnOff(CanReceiveHandle rcvObject){}
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
void ISR_CountryCfg(CanReceiveHandle rcvObject){}
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
void ISR_LanguageInfo(CanReceiveHandle rcvObject){}
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
void ISR_MdpsType(CanReceiveHandle rcvObject){}

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
void ApplSAS_AngleRxSigTimeout(void){}
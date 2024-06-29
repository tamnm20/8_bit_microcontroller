//#include "drv_i2c.h"
#ifndef MGR_DIAG_H
#define MGR_DIAG_H
/* ----- Global Define -------------------------------*/
//DTC INFO
#define DTC_MCU_WT_ERR		 		0x00U
#define DTC_MCU_MC_ERR		 		0x01U
#define DTC_SENSOR_FV_ERR	 		0x02U
#define DTC_SENSOR_FC_ERR	 		0x03U
#define DTC_SENSOR_ISPSTAT_ERR		0x04U
#define DTC_VIDEO_OUT_CUT_ERR		0x07U
#define DTC_VIDEO_OVER_VOL_ERR 		0x08U
#define DTC_CODE_COUNT		 		0x09U

#define DTC_CODE_INTERNAL_ERROR		0x00U
#define DTC_CODE_SENSOR_ERROR 		0x01U
#define DTC_CODE_OUTPUT_ERROR 		0x02U


#define DTC_MCU_WD_ERROR			Record_DTC_Error(DTC_MCU_WT_ERR)
#define DTC_MCU_WD_CLEAR			Record_DTC_Clear(DTC_MCU_WT_ERR)
#define DTC_MCU_MC_ERROR			Record_DTC_Error(DTC_MCU_MC_ERR)
#define DTC_MCU_MC_CLEAR			Record_DTC_Clear(DTC_MCU_MC_ERR)
#define DTC_ISP_FV_ERROR	 		Record_DTC_Error(DTC_SENSOR_FV_ERR)
#define DTC_ISP_FV_CLEAR	 		Record_DTC_Clear(DTC_SENSOR_FV_ERR)
#define DTC_ISP_FC_ERROR	 		Record_DTC_Error(DTC_SENSOR_FC_ERR)
#define DTC_ISP_FC_CLEAR	 		Record_DTC_Clear(DTC_SENSOR_FC_ERR)
#define DTC_ISP_IS_ERROR			Record_DTC_Error(DTC_SENSOR_ISPSTAT_ERR)
#define DTC_ISP_IS_CLEAR			Record_DTC_Clear(DTC_SENSOR_ISPSTAT_ERR)
#define DTC_VID_OC_ERROR			Record_DTC_Error(DTC_VIDEO_OUT_CUT_ERR)
#define DTC_VID_OC_CLEAR			Record_DTC_Clear(DTC_VIDEO_OUT_CUT_ERR)
#define DTC_VID_VO_ERROR 			Record_DTC_Error(DTC_VIDEO_OVER_VOL_ERR)
#define DTC_VID_VO_CLEAR	 		Record_DTC_Clear(DTC_VIDEO_OVER_VOL_ERR)
	

#define DTC_CURRENT_ERROR	 		0x09U
#define DTC_CONFIRM_ERROR	 		0x08U
#define DTC_CLEAR			 		0xFFU

//SYSTEM INFO
#define SYS_HMC_SPEC		 		0x02U
#define SYS_HMC_SPEC_L	 			0x03U

#define SYS_PART_NUMBER		 		0x87U
#define SYS_PART_NUMBER_L 			0x00U
#define SYS_MANU_DATE		 		0x8BU
#define SYS_MANU_DATE_L	 			(U8)SYS_PART_NUMBER_L+0x0aU
#define SYS_HW_VERSION		 		0x93U
#define SYS_HW_VERSION_L	 		(U8)SYS_MANU_DATE_L + 0x08U
#define SYS_SW_VERSION		 		0x95U
#define SYS_SW_VERSION_L	 		(U8)SYS_HW_VERSION_L + 0x03U
#define SYS_CAN_VERSION				0x00U
#define SYS_CAN_VERSION_L			(U8)SYS_SW_VERSION_L + 0x03U
#define SYS_CODE_COUNT				0x07U
#define SYS_CODE_SIZE				0x25U
#define SYS_WRITE_CODE_SIZE			0x27U
//ROUTINE CONTROL 

#define RTN_CTRL_ERASE_MEMORY		0xFF00U
#define RTN_CTRL_CHECK_PRG_DEPEND	0xFF01U
#define RTN_CTRL_SENSOR_RESET		0xF1F0U
#define RTN_CTRL_GUIDE_ONOFF		0xF1F1U
#define RTN_CTRL_WARNING_ONOFF		0xF1F2U

#define RTN_CTRL_DEFAULT			0x00U
#define RTN_CTRL_FIMR_UPDATE		0x01U //only RTN_CTRL_ERASE_MEMORY
#define RTN_CTRL_BINARY_UPDATE		0x02U //only RTN_CTRL_ERASE_MEMORY 

#define HMC_SPEC_OPTIC_X_HIGH_PID			 4U
#define HMC_SPEC_OPTIC_X_LOW_PID			 5U
#define HMC_SPEC_OPTIC_Y_HIGH_PID			 6U
#define HMC_SPEC_OPTIC_Y_LOW_PID			 7U
#define HMC_SPEC_COUNTRY_CFG_PID			 8U
#define HMC_SPEC_TEMPERATURE_PID			 9U
#define HMC_SPEC_SAS_ANGLE_HIGH_PID			10U
#define HMC_SPEC_SAS_ANGLE_LOW_PID	 	 	11U
#define HMC_SPEC_DTC_CURRENT_HIGH_PID		12U
#define HMC_SPEC_DTC_CURRENT_LOW_PID		13U
#define HMC_SPEC_DTC_CONFIRM_HIGH_PID		14U
#define HMC_SPEC_DTC_CONFIRM_LOW_PID		15U
#define HMC_SPEC_TOTAL_COUNT				16U

#define OPTIC_X_HIGH_PID_1			 0x80U
#define OPTIC_X_LOW_PID_2			 0x40U
#define OPTIC_Y_HIGH_PID_3			 0x20U
#define OPTIC_Y_LOW_PID_4			 0x10U
#define COUNTRY_CFG_PID_5			 0x08U
#define TEMPERATURE_PID_6			 0x04U
#define SAS_ANGLE_HIGH_PID_7		 0x02U
#define SAS_ANGLE_LOW_PID_8	 		 0x01U
#define DTC_CURRENT_HIGH_PID_9		 0x80U
#define DTC_CURRENT_LOW_PID_A		 0x40U
#define DTC_CONFIRM_HIGH_PID_B		 0x20U
#define DTC_CONFIRM_LOW_PID_C		 0x10U

#define USE_CASE_1BYTE				 0xFFU	
#define USE_CASE_2BYTE				 0xF0U
#define USE_CASE_3BYTE				 0x00U
#define USE_CASE_4BYTE				 0x00U

#define SAS_CLEAR					 0x00U
#define SAS_ON						 0x01U
#define SAS_PRE_ON					 0x02U

#define OPTIC_SETTING				0x00U
#define ERASE_ONESPEC				0x01U
#define ERASE_FLASH_ALL				0x02U

#define SIGNITURE_1_ADDR			0xF000U
#define SIGNITURE_2_ADDR			0xF001U
#define SIGNITURE_3_ADDR			0xF002U
#define SIGNITURE_4_ADDR			0xF003U
#define SIGNITURE_1_BYTE			0xAAU
#define SIGNITURE_2_BYTE			0xBBU
#define SIGNITURE_3_BYTE			0xCCU
#define SIGNITURE_4_BYTE			0xDDU

#define FIRMWARE_SIZE_ADDR			0x2E000U
#define TUNING_SIZE_ADDR			0x2D000U
#define FIRMWARE					0x30000U
#define TUNING						0x00000U
/*----------------------------------------------------*/

/* ----- Function ------------------------------------*/
void Reset_Diag(void);
void Init_DiagTask(void);
void Operate_DiagTask();
void Diag_StandBy(U8 *pError);
void Diag_InterInit(U8 *pError);
void Diag_Idle(U8 *pError);
void Diag_Running(U8 *pError);

void Diag_Ecu_Reset(void);
void Diag_Clear_DTC(void);
U8 Diag_Read_Dtc(U8 index);
void Diag_DTC_Error_WT(void);

void Clear_DTC_Struct(void);
void Record_DTC_Error(U8 ID);
void Record_DTC_Clear(U8 ID);
void Diag_Read_Sys(U8 ID, U8 *Buf,U8 Length);
void Diag_Write_Sys(U8 ID, U8 *Buf,U8 Length);
void Diag_Check_Programming(void);
void Firmware_Update(void);
void Diag_Eeprom_Update(void);
void Diag_Request_Download(U8 *Buf,U8 Length);
void Diag_Write_Transfer_Data(U8 *Buf);

/*----------------------------------------------------*/

/* ----- Extern Function -----------------------------*/
//extern U16 i2c_master_read(U8 slave_addr, U16 addr);
/*----------------------------------------------------*/

/* ----- Global Value --------------------------------*/
typedef struct {
	U8 update_set;
	U8 erase_set;
	U8 write_count;
	U32 total_write_cnt;	
	U32 write_cnt;
	U32 size;
	U8 Write_Buf[256];
	
} tMsg_Update;

#endif
/*----------------------------------------------------*/





#include "compiler_defs.h"
#include "C8051F580_defs.h"
#include "Global_Define.h"
#include "mgr_mcu.h"
#include "drv_mcu.h"
#include "drv_timer.h"
#include "drv_i2c.h"

#define  INIT		      		0x00U           // (MR) data byte received
#define  RX			      		0x01U           // (MR) data byte received
#define  TX			      		0x02U           // (MR) data byte received
#define		CMD_REGISTER_ADDR			(0x0040U)
#define SENSOR_INIT						0x01U
#define SENSOR_RUNNING				 	0x02U
#define SENSOR_STATE_STREAMING		 	0x3100U

INTERRUPT_PROTO (TIMER2_ISR, INTERRUPT_TIMER2);

extern SEG_XDATA tMsg_Global_Tick 	g_Global_Tick_Msg;
extern SEG_XDATA tMsg_Time_s		ga_tCAN_Time_Msg[TID_COUNT];

typedef struct {
	U8  Slave;
	U8  Length;
	U8  TRX_Flag;
	U16 Addr;
	U16 TxData;
	U16 RxData;
}tMsg_I2C_Tx_Data_s;

static SEG_XDATA tMsg_I2C_Tx_Data_s tI2C_Tx_Msg;

void Comm_I2C_Tx(U8 Slave_Addr,U8 Length,U16 Addr, U16 TData,U16 RData )
{
	tI2C_Tx_Msg.Slave  		= Slave_Addr;
	tI2C_Tx_Msg.Length 		= Length;
	tI2C_Tx_Msg.Addr 		= Addr;
	tI2C_Tx_Msg.TxData 		= TData;
	tI2C_Tx_Msg.RxData 		= RData;
	tI2C_Tx_Msg.TRX_Flag	= TX;
	
	i2c_master_write(tI2C_Tx_Msg.Slave,tI2C_Tx_Msg.Addr,tI2C_Tx_Msg.TxData,tI2C_Tx_Msg.Length);
	//Comm_I2C_Tx_Data();
}

U16 Comm_I2C_Rx(U8 Slave_Addr,U8 Length,U16 Addr, U16 TData,U16 RData )
{
	SEG_XDATA U16 ret = 0x0000U;

	tI2C_Tx_Msg.Slave  		= Slave_Addr;
	tI2C_Tx_Msg.Length 		= Length;
	tI2C_Tx_Msg.Addr 		= Addr;
	tI2C_Tx_Msg.TxData 		= TData;
	tI2C_Tx_Msg.RxData 		= RData;
	tI2C_Tx_Msg.TRX_Flag	= RX;
	
	tI2C_Tx_Msg.RxData = i2c_master_read(tI2C_Tx_Msg.Slave,tI2C_Tx_Msg.Addr,tI2C_Tx_Msg.Length);
	//Comm_I2C_Tx_Data();
	ret = tI2C_Tx_Msg.RxData;

	return ret;		
}

U8 Check_Isp_InitState(void)
{
	SEG_XDATA U16 chk_data = 0x00U;
	SEG_XDATA U8 ret = 0x00U;
	chk_data = Comm_I2C_Rx(ISP_SLAVE_ADDRESS,I2C_2BYTE_RW,(U16)CMD_REGISTER_ADDR,(U16)0x00,(U16)0x00);
	if(chk_data == SENSOR_STATE_STREAMING)//chk_data == 0x3100U
	{
		ret = TRUE;
	}
	else
	{
		ret = FALSE;
	}
	return ret;
}

U8 mtam[]  = "OKAY";
U8 mtam2[] = "OFF";
U8 tam_check =0;

int main() {
	SEG_XDATA U8 On_Time = 0x00U;
	
	Init_McuTask();
	SMBUS0_Init();					// Configure and enable SMBus
	Delay_Time_Set(TID_BLINK_TIMER, DT_BLINK_TIMER);
	
	// lcd_init();
	// lcd_goto_XY(1, 0);
	// lcd_send_string("     MCNEX Vina     ");
	// Wait_ms(10);
	// lcd_goto_XY(2, 0);
	// lcd_send_string(" HAPPY NEW YEAR 2024");
	// Wait_ms(10);
	// lcd_goto_XY(3, 0);
	// lcd_send_string("         Ninh Binh  ");
	// Wait_ms(10);
	// lcd_goto_XY(4, 0);
	// lcd_send_string("         01/01/2024 ");
	Wait_ms(200);
	
	while(1) {
		tam_check = Check_Isp_InitState();
		if(tam_check){
			i2c_master_write_tam(ISP_SLAVE_ADDRESS, &mtam,  sizeof(mtam)-1);
		}
		else{
			i2c_master_write_tam(ISP_SLAVE_ADDRESS, &mtam2, sizeof(mtam2)-1);
		}
		Wait_ms(10);
		// On_Time = Delay_Time_Get(TID_BLINK_TIMER);
		// if(On_Time == TRUE) {
			// if(tam_check){
				// i2c_master_write_tam(ISP_SLAVE_ADDRESS, &mtam, 4);
			// }
			// else{
				// i2c_master_write_tam(ISP_SLAVE_ADDRESS, &mtam2, 1);
			// }
		// }
	}

	return 0;
}

INTERRUPT(TIMER2_ISR, INTERRUPT_TIMER2)
{
	SEG_XDATA U8 i = 0x00U;
	TF2H = 0x00U;

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
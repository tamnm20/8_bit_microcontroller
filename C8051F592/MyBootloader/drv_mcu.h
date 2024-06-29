/* ----- Global Define -------------------------------*/
//#define  SYSCLK						(24000000)	// System clock frequency in Hz
/*----------------------------------------------------*/

/* ----- Global Value --------------------------------*/
/* Pin Name Set */
SBIT (SW2_UPDATE_START,	 		SFR_P1, 2);
SBIT (SW6_UPDOWN_MODE_SEL,	 	SFR_P1, 3);
SBIT (SW7_FIRMTUNING_MODE_SEL, 	SFR_P1, 4);
SBIT (LED_STATUS_ERROR,			SFR_P2, 0);
SBIT (LED_STATUS_UPDOWNLOAD,	SFR_P2, 1);
SBIT (MCU_F_ENABLE,	 			SFR_P2, 3);
/*----------------------------------------------------*/

/* ----- Function ------------------------------------*/
void Vdd_Monitor_Init(void);
void Osc_Init(void);
void Port_Init(void);
void Rstsrc_Init(void);
void Exinterrupt_Init(void);
void MCU_Reset(void);


/*----------------------------------------------------*/

/* ----- Extern Function -----------------------------*/

/*----------------------------------------------------*/












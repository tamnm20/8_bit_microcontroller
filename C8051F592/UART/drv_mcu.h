#ifndef __DRV_MCU_H__
#define __DRV_MCU_H__

/********************** Macros **********************/

SBIT (SDA, SFR_P2, 0);
SBIT (SCL, SFR_P2, 1);
SBIT (BUTTON,	 				SFR_P1, 2);

/********************** Function Prototypes **********************/
void Osc_Init(void);
void Port_Init(void);
void Exinterrupt_Init(void);

#endif
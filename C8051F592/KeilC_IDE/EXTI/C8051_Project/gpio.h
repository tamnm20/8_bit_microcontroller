#ifndef GPIO_H
#define GPIO_H

#include <compiler_defs.h>
#include <C8051F580_defs.h>

SBIT (LED_GREEN, SFR_P2, 1);
SBIT (LED_YELLOW, SFR_P2, 0);

SBIT (SW2_Button, SFR_P1, 2);
SBIT (SW7_Button, SFR_P1, 4);

SFR(status_sw2, SFR_P1); 

void PORT_Init (void);
U8 State_SW2();



#endif
#ifndef TIMER_H
#define TIMER_H


#include <compiler_defs.h>
#include <C8051F580_defs.h>

void TIMER2_Init (void);
void TIMER2_Interrupt_Init (void);
void Delay_ms(U32 time);
void Delay_IT_ms(U32 time);

#endif
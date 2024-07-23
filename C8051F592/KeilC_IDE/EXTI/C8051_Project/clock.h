#ifndef CLOCK_H
#define CLOCK_H

#include <compiler_defs.h>
#include <C8051F580_defs.h>
#include <stdio.h>

#define SYSCLK       24000000/12       // SYSCLK frequency in Hz


//-----------------------------------------------------------------------------
// OSCILLATOR_Init
//-----------------------------------------------------------------------------
// 
// Return Value:  None
// Parameters:    None
//
// Configure the internal oscillator to maximum internal frequency / 8
//
//-----------------------------------------------------------------------------
void RCC_Init (void);


#endif   
//-----------------------------------------------------------------------------
// F580_FlashUtils.h
//-----------------------------------------------------------------------------
// Copyright 2008 Silicon Laboratories, Inc.
//
// This program contains several useful utilities for writing and updating
// FLASH memory.
//
// Target:         C8051F580
// Tool chain:     Raisonance / Keil / SDCC
// Command Line:   None
//
// Release 1.2 / 15 JAN 2015 (TP)
//    -Removed SFLE bit
//    -Updated FlashPrimitives functions to work if the functions are located
//        in code banks other than Bank 0.
//
// Release 1.1 / 11 MAR 2010 (GP)
//    -Tested with Raisonance
//
// Release 1.0 / 23 OCT 2008 (GP)
//    -Initial Revision
//

#ifndef F580_FLASHUTILS_H
#define F580_FLASHUTILS_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include "compiler_defs.h"
#include "F580_FlashPrimitives.h"

//-----------------------------------------------------------------------------
// Structures, Unions, Enumerations, and Type Definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Exported Function Prototypes
//-----------------------------------------------------------------------------

// FLASH read/write/erase routines
extern void FLASH_Write (FLADDR dest, U8 *src, U16 numbytes);
extern U8 * FLASH_Read  (U8 *dest, FLADDR src, U16 numbytes);
extern void FLASH_Clear (FLADDR addr, U16 numbytes);

// FLASH update/copy routines
extern void FLASH_Update (FLADDR dest, U8 *src, U16 numbytes);
extern void FLASH_Copy   (FLADDR dest, FLADDR src, U16 numbytes);

// FLASH test routines
extern void FLASH_Fill (FLADDR addr, U32 length, U8 fill);

#endif // F580_FLASHUTILS_H


//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
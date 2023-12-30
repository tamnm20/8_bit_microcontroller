/* ----- Global Define -------------------------------*/

/*----------------------------------------------------*/

/* ----- Global Value --------------------------------*/

/*----------------------------------------------------*/

/* ----- Function ------------------------------------*/

/*----------------------------------------------------*/

/* ----- Extern Function -----------------------------*/

/*----------------------------------------------------*/
#ifndef DRV_MEM_H_
#define DRV_MEM_H_

#include "compiler_defs.h"
#include "mgr_diag.h"
#include "mgr_comm.h"
//-----------------------------------------------------------------------------
// Open Header #define
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Structures, Unions, Enumerations, and Type Definitions
//-----------------------------------------------------------------------------
//BANK1
#define DTCCODE_ADDRESS					0xF800U
#define ONESPEC_ADDRESS					0xFA00U
#define SYSINFO_ADDRESS					0xFC00U
#define OPTIC_ADDRESS					0xFE00U
#define PAGE_SIZE						0x100

typedef U16 FLADDR;

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

#ifndef FLASH_PAGESIZE
#define FLASH_PAGESIZE (512)
#endif

#ifndef FLASH_TEMP
#define FLASH_TEMP 0x7800L             // For 32K Flash devices
//#define FLASH_TEMP 0x3C00L           // For 16K Flash devices
#endif

#ifndef FLASH_LAST
#define FLASH_LAST 0x7A00L             // For 32K Flash devices
//#define FLASH_LAST 0x3E00L           // For 16K Flash devices
#endif

//-----------------------------------------------------------------------------
// Exported Function Prototypes
//-----------------------------------------------------------------------------

// FLASH read/write/erase routines

// FLASH update/copy routines
void FLASH_Update (FLADDR dest, U8 *src, U16 numbytes);
void FLASH_Copy (FLADDR dest, FLADDR src, U16 numbytes);

// FLASH test routines
void F560_FLASH_Fill (FLADDR addr, U16 length, U8 fill);
//-----------------------------------------------------------------------------
// Close Header #define
//-----------------------------------------------------------------------------

void  FLASH_ByteWrite (FLADDR addr, U8 byte);
U8  FLASH_ByteRead  (FLADDR addr);
void  FLASH_PageErase (FLADDR addr,U8 BANK);
void FLASH_Write_Buf (FLADDR dest, U8 *src, U16 numbytes,U8 BANK);
void FLASH_Read_Buf (U8 *dest, FLADDR src, U16 numbytes,U8 BANK);

#endif    // _F560_FLASHPRIMITIVES_H_

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
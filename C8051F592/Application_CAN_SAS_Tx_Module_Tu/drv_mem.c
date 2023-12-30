/*_____ I N C L U D E __________________________________________*/
#include "compiler_defs.h"
#include "C8051F580_defs.h"
#include "Global_Define.h"
#include "drv_mem.h"
#include "drv_timer.h"

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// F560_FLASH_ByteWrite
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   :
//   1) FLADDR addr - address of the byte to write to
//                    valid range is 0x0000 to 0x7BFF for 32K Flash devices
//                    valid range is 0x0000 to 0x3FFF for 16K Flash devices
//   2) U8 byte - byte to write to Flash.
//
// This routine writes <byte> to the linear FLASH address <addr>.
//
// This routine conforms to the recommendations in the C8051F56x data sheet
// 
// If the MCU is operating from the internal voltage regulator, the VDD
// monitor should be set threshold and enabled as a reset source only when
// writing or erasing Flash. Otherwise, it should be set to the low threshold.
//
// If the MCU is operating from an external voltage regulator powering VDD
// directly, the VDD monitor can be set to the high threshold permanently.
//-----------------------------------------------------------------------------

void FLASH_ByteWrite (FLADDR addr, U8 byte)
{

#ifndef __PST_PolySpace__
   bit EA_SAVE = EA;                   // Preserve EA
#else
   U8 EA_SAVE = (U8)EA;
#endif                  // Preserve EA
   U8 xdata * data pwrite;             // FLASH write pointer
   U8 ret = 0x00U;
   U8 i;

   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = ACTIVE_PAGE;

   EA = 0U;                             // Disable interrupts

   RSTSRC = 0x00U | 0x04U;                      // 1. Disable VDD monitor as a reset source

   VDM0CN = 0xA0U;                      // 2. Enable VDD monitor and high threshold

   for (i = 0U; i < 20U; i++) {}        // 3. Wait for VDD monitor to stabilize

   if ( (VDM0CN & 0x40U) == 0x00U)               // 4. If the VDD voltage is not high
   {
      ret = 0U;                        //    enough don't write to Flash
   	  VDM0CN = 0x80U;         
	  for (i = 0U; i < 20U; i++) {}        // 3. Wait for VDD monitor to stabilize
  	  RSTSRC = 0x02U | 0x04U;
   }
   else
   {
	   ret = 1U;   
	   RSTSRC = 0x02U | 0x04U;                      // 5. Safe to enable VDD Monitor as a 
	                                       //    reset source

	   pwrite = (U8 xdata *) addr;

	                                       // 6. Enable Flash Writes

	   FLKEY  = 0xA5U;                      // Key Sequence 1
	   FLKEY  = 0xF1U;                      // Key Sequence 2
	   PSCTL |= 0x01U;                      // PSWE = 1 which enables writes

	   VDM0CN = 0xA0U;                      // 7. Enable VDD monitor and high threshold

	   RSTSRC = 0x02U | 0x04U;                      // 8. Enable VDD monitor as a reset source

	   *pwrite = byte;                     // 9. Write the byte

	   RSTSRC = 0x00U | 0x04U;                      // 10. Disable the VDD monitor as reset 
	                                       //     source
	   VDM0CN = 0x80U;                      // 11. Change VDD Monitor to low threshold
      for (i = 0U; i < 20U; i++) {}        // 3. Wait for VDD monitor to stabilize
	   RSTSRC = 0x02U | 0x04U;                      // 12. Re-enable the VDD monitor as a 
	                                       //     reset source

	   PSCTL &= ~0x01U;                     // PSWE = 0 which disable writes

	   EA = EA_SAVE;                       // Restore interrupts

	   SFRPAGE = SFRPAGE_save;
   }
                         // Write completed successfully
}

//-----------------------------------------------------------------------------
// F560_FLASH_ByteRead
//-----------------------------------------------------------------------------
//
// Return Value :
//      U8 - byte read from Flash
// Parameters   :
//   1) FLADDR addr - address of the byte to read to
//                    valid range is 0x0000 to 0x7BFF for 32K Flash devices
//                    valid range is 0x0000 to 0x3FFF for 16K Flash devices
//
// This routine reads a <byte> from the linear FLASH address <addr>.
//-----------------------------------------------------------------------------

U8 FLASH_ByteRead (FLADDR addr)
{
#ifndef __PST_PolySpace__
   bit EA_SAVE = EA;                   // Preserve EA
#else
   U8 EA_SAVE = (U8)EA;
#endif                  // Preserve EA
   U8 code * data pread;               // FLASH read pointer
   U8 byte;

   EA = 0U;                             // Disable interrupts

   pread = (U8 code *) addr;

   byte = *pread;                      // Read the byte

   EA = EA_SAVE;                       // Restore interrupts

   return byte;
}

//-----------------------------------------------------------------------------
// F560_FLASH_PageErase
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   :
//   1) FLADDR addr - address of any byte in the page to erase
//                    valid range is 0x0000 to 0x79FF for 32K Flash devices
//                    valid range is 0x0000 to 0x3DFF for 16K Flash devices
//
// This routine erases the FLASH page containing the linear FLASH address
// <addr>.  Note that the page of Flash containing the Lock Byte cannot be
// erased from application code.
//
//// This routine conforms to the recommendations in the C8051F56x data sheet
//
// If the MCU is operating from the internal voltage regulator, the VDD
// monitor should be set threshold and enabled as a reset source only when
// writing or erasing Flash. Otherwise, it should be set to the low threshold.
//
// If the MCU is operating from an external voltage regulator powering VDD
// directly, the VDD monitor can be set to the high threshold permanently.
//-----------------------------------------------------------------------------

void FLASH_PageErase (FLADDR addr,U8 BANK)
{
#ifndef __PST_PolySpace__
   bit EA_SAVE = EA;                   // Preserve EA
#else
   U8 EA_SAVE = (U8)EA;
#endif                  // Preserve EA
   U8 xdata * data pwrite;             // FLASH write pointer
   U8 ret = 0x00U;
   U8 i;
   U8 Save_Bank = PSBANK;

   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = ACTIVE_PAGE;
   PSBANK = BANK;
   EA = 0U;                             // Disable interrupts

   RSTSRC = 0x00U | 0x04U;                      // 1. Disable VDD monitor as a reset source

   VDM0CN = 0xA0U;                      // 2. Enable VDD monitor and high threshold

   for (i = 0U; i < 20U; i++) {}        // 3. Wait for VDD monitor to stabilize

   if ( (VDM0CN & 0x40U) == 0x00U )               // 4. If the VDD voltage is not high enough
   {
      ret = 0U;                        //    don't attempt to write to Flash
   	  VDM0CN = 0x80U;         
	  for (i = 0U; i < 20U; i++) {}        // 3. Wait for VDD monitor to stabilize
  	  RSTSRC = 0x02U | 0x04U;
   }
   else
   {	
   	  ret = 1U;
   
	   RSTSRC = 0x02U | 0x04U;                      // 5. Safe to enable VDD Monitor as a reset 
	                                       //    source

	   pwrite = (U8 xdata *) addr;

	                                       // 6. Enable Flash Writes

	   FLKEY  = 0xA5U;                      // Key Sequence 1
	   FLKEY  = 0xF1U;                      // Key Sequence 2
	   PSCTL |= 0x03U;                      // PSWE = 1; PSEE = 1

	   VDM0CN = 0xA0U;                      // 7. Enable VDD monitor and high threshold

	   RSTSRC = 0x02U | 0x04U;                      // 8. Enable VDD monitor as a reset source

	   *pwrite = 0U;                        // 9. Initiate page erase

	   RSTSRC = 0x00U | 0x04U;                      // 10. Disable the VDD monitor as a reset
	                                       //     source
	   VDM0CN = 0x80U;                      // 11. Change VDD Monitor to low threshold
      for (i = 0U; i < 20U; i++) {}        // 3. Wait for VDD monitor to stabilize
	   RSTSRC = 0x02U | 0x04U;                      // 12. Re-enable the VDD monitor as a reset 
	                                       //     source

	   PSCTL &= ~0x03U;                     // PSWE = 0; PSEE = 0

	   EA = EA_SAVE;                       // Restore interrupts

	   SFRPAGE = SFRPAGE_save;
   }
   PSBANK = Save_Bank;
}

void FLASH_Write_Buf (FLADDR dest, U8 *src, U16 numbytes,U8 BANK)
{
   FLADDR i;
   SEG_XDATA U8 index = 0x00U;
   U8 Save_Bank = PSBANK;
   PSBANK = BANK;
   for (i = dest; i < (dest+numbytes); i++) 
   {
      FLASH_ByteWrite (i,src[index]);
	  index++;
   }
   PSBANK = Save_Bank;
}

void FLASH_Read_Buf (U8 *dest, FLADDR src, U16 numbytes,U8 BANK)
{
   FLADDR i;
   SEG_XDATA U8 index = 0x00U;
   U8 Save_Bank = PSBANK;
   PSBANK = BANK;

   for (i = 0; i < numbytes; i++) 
   {
      dest[index] = FLASH_ByteRead (src+i);
	  index++;
   }
   PSBANK = Save_Bank;
}


//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------

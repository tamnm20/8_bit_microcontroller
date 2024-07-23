//-----------------------------------------------------------------------------
// C8051F560_defs.h
//-----------------------------------------------------------------------------
// Copyright 2008, Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// Register/bit definitions for the C8051F55x/56x/57x family.
// **Important Note**: The compiler_defs.h header file should be included
// before including this header file.
//
// Target:         C8051F550/1/2/3/4/5/6/7
//                 C8051F560/1/2/3/4/5/6/7/8/9
//                 C8051F570/1/2/3/4/5
// Tool chain:     Generic
// Command Line:   None
//
// Release 0.2 - 01 APR 2009 (GP)
//    -Added SN0-SN3
//
// Release 0.1 - 22 AUG 2008 (GP)
//    -Initial release
//

//-----------------------------------------------------------------------------
// Header File Preprocessor Directive
//-----------------------------------------------------------------------------

#ifndef C8051F560_DEFS_H
#define C8051F560_DEFS_H

#include "compiler_defs.h"

#ifndef __PST_PolySpace__
//-----------------------------------------------------------------------------
// Page 0 and Page F Registers
//-----------------------------------------------------------------------------

SFR (P0, 0x80U);                        // Port 0 Latch
SFR (SP, 0x81U);                        // Stack Pointer
SFR (DPL, 0x82U);                       // Data Pointer Low
SFR (DPH, 0x83U);                       // Data Pointer High
SFR (SFR0CN, 0x84U);                    // SFR Page Control
SFR (SFRNEXT, 0x85U);                   // SFR stack next page
SFR (SFRLAST, 0x86U);                   // SFR stack last page
SFR (PCON, 0x87U);                      // Power Control
SFR (TCON, 0x88U);                      // Timer/Counter Control
SFR (TMOD, 0x89U);                      // Timer/Counter Mode
SFR (TL0, 0x8AU);                       // Timer/Counter 0 Low
SFR (TL1, 0x8BU);                       // Timer/Counter 1 Low
SFR (TH0, 0x8CU);                       // Timer/Counter 0 High
SFR (TH1, 0x8DU);                       // Timer/Counter 1 High
SFR (CKCON, 0x8EU);                     // Clock Control
SFR (PSCTL, 0x8FU);                     // Program Store R/W Control
SFR (CLKSEL, 0x8FU);                    // System clock select
SFR (P1, 0x90U);                        // Port 1 Latch
SFR (TMR3CN, 0x91U);                    // Timer/Counter 3 Control
SFR (TMR3RLL, 0x92U);                   // Timer/Counter 3 Reload Low
SFR (TMR3RLH, 0x93U);                   // Timer/Counter 3 Reload High
SFR (TMR3L, 0x94U);                     // Timer/Counter 3 Low
SFR (TMR3H, 0x95U);                     // Timer/Counter 3 High
SFR (CLKMUL, 0x97U);                    // Clock Multiplier
SFR (SCON0, 0x98U);                     // UART0 Control
SFR (SBUF0, 0x99U);                     // UART0 Data Buffer
SFR (CPT0CN, 0x9AU);                    // Comparator 0 Control
SFR (CPT0MD, 0x9BU);                    // Comparator 0 Mode
SFR (CPT0MX, 0x9CU);                    // Comparator 0 Mux
SFR (CPT1CN, 0x9DU);                    // Comparator 1 Control
SFR (CPT1MD, 0x9EU);                    // Comparator 0 Mode
SFR (OSCIFIN, 0x9EU);                   // Internal Oscillator Fine Control
SFR (CPT1MX, 0x9FU);                    // Comparator 1 Mux
SFR (OSCXCN, 0x9FU);                    // External Oscillator Control
SFR (P2, 0xA0U);                        // Port 2 Latch
SFR (SPI0CFG, 0xA1U);                   // SPI0 Configuration
SFR (OSCICN, 0xA1U);                    // Internal Oscillator Control
SFR (SPI0CKR, 0xA2U);                   // SPI0 Clock rate control
SFR (OSCICRS, 0xA2U);                   // Internal Oscillator Coarse Control
SFR (SPI0DAT, 0xA3U);                   // SPI0 Data Buffer
SFR (P0MDOUT, 0xA4U);                   // Port 0 Output Mode
SFR (P1MDOUT, 0xA5U);                   // Port 1 Output Mode
SFR (P2MDOUT, 0xA6U);                   // Port 2 Output Mode
SFR (SFRPAGE, 0xA7U);                   // SFR Page Select
SFR (IE, 0xA8U);                        // Interrupt Enable
SFR (SMOD0, 0xA9U);                     // Serial Port 0 Control
SFR (EMI0CN, 0xAAU);                    // EMIF control
SFR (EMI0TC, 0xAAU);                    // EMIF Timing control
SFR (SBCON0, 0xABU);                    // UART0 Baud Rate Generator Control
SFR (SBRLL0, 0xACU);                    // UART0 Baud Rate Generator Low
SFR (SBRLH0, 0xADU);                    // UART0 Baud Rate Generator High
SFR (P3MAT, 0xAEU);                     // Port 3 Match
SFR (P3MDOUT, 0xAEU);                   // Port 3 Mode
SFR (P3MASK, 0xAFU);                    // Port 3 Mask
SFR (P4MDOUT, 0xAFU);                   // Port 4 Mode
SFR (P3, 0xB0U);                        // Port 3 Latch
SFR (P2MAT, 0xB1U);                     // Port 2 Match
SFR (P2MASK, 0xB2U);                    // Port 2 Mask
SFR (EMI0CF, 0xB2U);                    // EMIF Configuration
SFR (P4, 0xB5U);                        // Port 4 Latch
SFR (FLSCL, 0xB6U);                     // Flash Scale
SFR (FLKEY, 0xB7U);                     // Flash access limit
SFR (IP, 0xB8U);                        // Interrupt Priority
SFR (SMB0ADR, 0xB9U);                   // SMBus0 Slave address
SFR (ADC0TK, 0xBAU);                    // ADC0 Tracking Mode Select
SFR (SMB0ADM, 0xBAU);                   // SMBus0 Address Mask
SFR (ADC0MX, 0xBBU);                    // AMUX0 Channel select
SFR (ADC0CF, 0xBCU);                    // AMUX0 Channel configuration
SFR (ADC0L, 0xBDU);                     // ADC0 Data Low
SFR (ADC0H, 0xBEU);                     // ADC0 Data High
SFR (SMB0CN, 0xC0U);                    // SMBus0 Control
SFR (SMB0CF, 0xC1U);                    // SMBus0 Configuration
SFR (SMB0DAT, 0xC2U);                   // SMBus0 Data
SFR (ADC0GTL, 0xC3U);                   // ADC0 Greater-Than Compare Low
SFR (ADC0GTH, 0xC4U);                   // ADC0 Greater-Than Compare High
SFR (ADC0LTL, 0xC5U);                   // ADC0 Less-Than Compare Word Low
SFR (ADC0LTH, 0xC6U);                   // ADC0 Less-Than Compare Word High
SFR (XBR2, 0xC7U);                      // Port I/O Crossbar Control 2
SFR (TMR2CN, 0xC8U);                    // Timer/Counter 2 Control
SFR (REG0CN, 0xC9U);                    // Regulator Control
SFR (LIN0CF, 0xC9U);                    // LIN 0 Configuration
SFR (TMR2RLL, 0xCAU);                   // Timer/Counter 2 Reload Low
SFR (TMR2RLH, 0xCBU);                   // Timer/Counter 2 Reload High
SFR (TMR2L, 0xCCU);                     // Timer/Counter 2 Low
SFR (TMR2H, 0xCDU);                     // Timer/Counter 2 High
SFR (PCA0CPL5, 0xCEU);                  // PCA0 Capture 5 Low
SFR (PCA0CPH5, 0xCFU);                  // PCA0 Capture 5 High
SFR (PSW, 0xD0U);                       // Program Status Word
SFR (REF0CN, 0xD1U);                    // Voltage Reference Control
SFR (LIN0DAT, 0xD2U);                   // LIN0 Data
SFR (LIN0ADR, 0xD3U);                   // LIN0 Address
SFR (P0SKIP, 0xD4U);                    // Port 0 Skip
SFR (P1SKIP, 0xD5U);                    // Port 1 Skip
SFR (P2SKIP, 0xD6U);                    // Port 2 Skip
SFR (P3SKIP, 0xD7U);                    // Port 3 Skip
SFR (PCA0CN, 0xD8U);                    // PCA0 Control
SFR (PCA0MD, 0xD9U);                    // PCA0 Mode
SFR (PCA0PWM, 0xD9U);                   // PCA0 PWM Control
SFR (PCA0CPM0, 0xDAU);                  // PCA0 Module 0 Mode Register
SFR (PCA0CPM1, 0xDBU);                  // PCA0 Module 1 Mode Register
SFR (PCA0CPM2, 0xDCU);                  // PCA0 Module 2 Mode Register
SFR (PCA0CPM3, 0xDDU);                  // PCA0 Module 3 Mode Register
SFR (PCA0CPM4, 0xDEU);                  // PCA0 Module 4 Mode Register
SFR (PCA0CPM5, 0xDFU);                  // PCA0 Module 5 Mode Register
SFR (ACC, 0xE0U);                       // Accumulator
SFR (XBR0, 0xE1U);                      // Port I/O Crossbar Control 0
SFR (XBR1, 0xE2U);                      // Port I/O Crossbar Control 1
SFR (CCH0CN, 0xE3U);                    // Cache control
SFR (IT01CF, 0xE4U);                    // INT0/INT1 Configuration
SFR (EIE1, 0xE6U);                      // Extended Interrupt Enable 2
SFR (EIE2, 0xE7U);                      // Extended Interrupt Enable 2
SFR (ADC0CN, 0xE8U);                    // ADC0 Control
SFR (PCA0CPL1, 0xE9U);                  // PCA0 Capture 2 Low
SFR (PCA0CPH1, 0xEAU);                  // PCA0 Capture 2 High
SFR (PCA0CPL2, 0xEBU);                  // PCA0 Capture 3 Low
SFR (PCA0CPH2, 0xECU);                  // PCA0 Capture 3 High
SFR (PCA0CPL3, 0xEDU);                  // PCA0 Capture 4 Low
SFR (PCA0CPH3, 0xEEU);                  // PCA0 Capture 4 High
SFR (RSTSRC, 0xEFU);                    // Reset Source Configuration/Status
SFR (B, 0xF0U);                         // B Register
SFR (P0MAT, 0xF1U);                     // Port 0 Match
SFR (P0MDIN, 0xF1U);                    // Port 0 Input Mode
SFR (P0MASK, 0xF2U);                    // Port 0 Mask
SFR (P1MDIN, 0xF2U);                    // Port 1 Input Mode
SFR (P1MAT, 0xF3U);                     // Port 1 Match
SFR (P2MDIN, 0xF3U);                    // Port 2 Input Mode
SFR (P1MASK, 0xF4U);                    // Port 1 Mask
SFR (P3MDIN, 0xF4U);                    // Port 3 Input Mode
SFR (EIP1, 0xF6U);                      // External Interrupt Priority 1
SFR (EIP2, 0xF7U);                      // External Interrupt Priority 2
SFR (SPI0CN, 0xF8U);                    // SPI0 Control
SFR (PCA0L, 0xF9U);                     // PCA0 Counter Low
SFR (SN0, 0xF9U);                       // Serial Number 0
SFR (PCA0H, 0xFAU);                     // PCA0 Counter High
SFR (SN1, 0xFAU);                       // Serial Number 1
SFR (PCA0CPL0, 0xFBU);                  // PCA0 Capture 0 Low
SFR (SN2, 0xFBU);                       // Serial Number 2
SFR (PCA0CPH0, 0xFCU);                  // PCA0 Capture 0 High
SFR (SN3, 0xFCU);                       // Serial Number 3
SFR (PCA0CPL4, 0xFDU);                  // PCA0 Capture 4 Low
SFR (PCA0CPH4, 0xFEU);                  // PCA0 Capture 4 High
SFR (VDM0CN, 0xFFU);                    // VDD Monitor Control

//-----------------------------------------------------------------------------
// Page C (CAN0) Registers
//-----------------------------------------------------------------------------

SFR (CAN0CFG, 0x92U);                   // CAN0 Clock Configuration
SFR (CAN0STAT, 0x94U);                  // Status Register Low Byte
SFR (CAN0ERRL, 0x96U);                  // Error Counter Low Byte
SFR (CAN0ERRH, 0x97U);                  // Error Counter High Byte
SFR (CAN0BTL, 0x9AU);                   // Bit Timing Register Low Byte
SFR (CAN0BTH, 0x9BU);                   // Bit Timing Register High Byte
SFR (CAN0IIDL, 0x9CU);                  // Interrupt Register Low Byte
SFR (CAN0IIDH, 0x9DU);                  // Interrupt Register High Byte
SFR (CAN0TST, 0x9EU);                   // Test Register Low Byte
SFR (CAN0BRPE, 0xA1U);                  // BRP Extension Register Low Byte
SFR (CAN0TR1L, 0xA2U);                  // Transmission Request 1 Low Byte
SFR (CAN0TR1H, 0xA3U);                  // Transmission Request 1 High Byte
SFR (CAN0TR2L, 0xA4U);                  // Transmission Request 2 Low Byte
SFR (CAN0TR2H, 0xA5U);                  // Transmission Request 2 High Byte
SFR (CAN0ND1L, 0xAAU);                  // New Data 1 Low Byte
SFR (CAN0ND1H, 0xABU);                  // New Data 1 High Byte
SFR (CAN0ND2L, 0xACU);                  // New Data 2 Low Byte
SFR (CAN0ND2H, 0xADU);                  // New Data 2 High Byte
SFR (CAN0IP1L, 0xAEU);                  // Interrupt Pending 1 Low Byte
SFR (CAN0IP1H, 0xAFU);                  // Interrupt Pending 1 High Byte
SFR (CAN0IP2L, 0xB2U);                  // Interrupt Pending 2 Low Byte
SFR (CAN0IP2H, 0xB3U);                  // Interrupt Pending 2 High Byte
SFR (CAN0MV1L, 0xBAU);                  // Message Valid 1 Low Byte
SFR (CAN0MV1H, 0xBBU);                  // Message Valid 1 High Byte
SFR (CAN0MV2L, 0xBCU);                  // Message Valid 2 Low Byte
SFR (CAN0MV2H, 0xBDU);                  // Message Valid 2 High Byte
SFR (CAN0IF1CRL, 0xBEU);                // IF1 Command Request Low Byte
SFR (CAN0IF1CRH, 0xBFU);                // IF1 Command Request High Byte
SFR (CAN0CN, 0xC0U);                    // CAN Control Register Low Byte
SFR (CAN0IF1CML, 0xC2U);                // IF1 Command Mask Low Byte
SFR (CAN0IF1CMH, 0xC3U);                // IF1 Command Mask High Byte
SFR (CAN0IF1M1L, 0xC4U);                // IF1 Mask 1 Low Byte
SFR (CAN0IF1M1H, 0xC5U);                // IF1 Mask 1 High Byte
SFR (CAN0IF1M2L, 0xC6U);                // IF1 Mask 2 Low Byte
SFR (CAN0IF1M2H, 0xC7U);                // IF1 Mask 2 High Byte
SFR (CAN0IF1A1L, 0xCAU);                // IF1 Arbitration 1 Low Byte
SFR (CAN0IF1A1H, 0xCBU);                // IF1 Arbitration 1 High Byte
SFR (CAN0IF1A2L, 0xCCU);                // IF1 Arbitration 2 Low Byte
SFR (CAN0IF1A2H, 0xCDU);                // IF1 Arbitration 2 High Byte
SFR (CAN0IF2MCL, 0xCEU);                // IF2 Message Control Low Byte
SFR (CAN0IF2MCH, 0xCFU);                // IF2 Message Control High Byte
SFR (CAN0IF1MCL, 0xD2U);                // IF1 Message Control Low Byte
SFR (CAN0IF1MCH, 0xD3U);                // IF1 Message Control High Byte
SFR (CAN0IF1DA1L, 0xD4U);               // IF1 Data A 1 Low Byte
SFR (CAN0IF1DA1H, 0xD5U);               // IF1 Data A 1 High Byte
SFR (CAN0IF1DA2L, 0xD6U);               // IF1 Data A 2 Low Byte
SFR (CAN0IF1DA2H, 0xD7U);               // IF1 Data A 2 High Byte
SFR (CAN0IF1DB1L, 0xDAU);               // IF1 Data B 1 Low Byte
SFR (CAN0IF1DB1H, 0xDBU);               // IF1 Data B 1 High Byte
SFR (CAN0IF1DB2L, 0xDCU);               // IF1 Data B 2 Low Byte
SFR (CAN0IF1DB2H, 0xDDU);               // IF1 Data B 2 High Byte
SFR (CAN0IF2CRL, 0xDEU);                // IF2 Command Request Low Byte
SFR (CAN0IF2CRH, 0xDFU);                // IF2 Command Request High Byte
SFR (CAN0IF2CML, 0xE2U);                // IF2 Command Mask Low Byte
SFR (CAN0IF2CMH, 0xE3U);                // IF2 Command Mask High Byte
SFR (CAN0IF2M1L, 0xEAU);                // IF2 Mask 1 Low Byte
SFR (CAN0IF2M1H, 0xEBU);                // IF2 Mask 1 High Byte
SFR (CAN0IF2M2L, 0xECU);                // IF2 Mask 2 Low Byte
SFR (CAN0IF2M2H, 0xEDU);                // IF2 Mask 2 High Byte
SFR (CAN0IF2A1L, 0xEEU);                // IF2 Arbitration 1 Low Byte
SFR (CAN0IF2A1H, 0xEFU);                // IF2 Arbitration 1 High Byte
SFR (CAN0IF2A2L, 0xF2U);                // IF2 Arbitration 2 Low Byte
SFR (CAN0IF2A2H, 0xF3U);                // IF2 Arbitration 2 High Byte
SFR (CAN0IF2DA1L, 0xF6U);               // IF2 Data A 1 Low Byte
SFR (CAN0IF2DA1H, 0xF7U);               // IF2 Data A 1 High Byte
SFR (CAN0IF2DA2L, 0xFAU);               // IF2 Data A 2 Low Byte
SFR (CAN0IF2DA2H, 0xFBU);               // IF2 Data A 2 High Byte
SFR (CAN0IF2DB1L, 0xFCU);               // IF2 Data B 1 Low Byte
SFR (CAN0IF2DB1H, 0xFDU);               // IF2 Data B 1 High Byte
SFR (CAN0IF2DB2L, 0xFEU);               // IF2 Data B 2 Low Byte
SFR (CAN0IF2DB2H, 0xFFU);               // IF2 Data B 2 High Byte


//-----------------------------------------------------------------------------
// 16-bit Register Definitions (might not be supported by all compilers)
//-----------------------------------------------------------------------------

SFR16 (DP, 0x82U);                      // Data Pointer
SFR16 (TMR3RL, 0x92U);                  // Timer3 Reload
SFR16 (TMR3, 0x94U);                    // Timer3 Capture / Reload
SFR16 (SBRL0, 0xACU);                   // UART0 Reload
SFR16 (ADC0, 0xBDU);                    // ADC0 data
SFR16 (ADC0GT, 0xC3U);                  // ADC0 Greater Than Window
SFR16 (ADC0LT, 0xC5U);                  // ADC0 Less Than Window
SFR16 (TMR2RL, 0xCAU);                  // Timer 2 Reload
SFR16 (TMR2, 0xCCU);                    // Timer2 Capture / Reload
SFR16 (PCA0CP5, 0xCEU);                 // PCA0 Module 5 Capture
SFR16 (PCA0CP1, 0xE9U);                 // PCA0 Module 1 Capture
SFR16 (PCA0CP2, 0xEBU);                 // PCA0 Module 2 Capture
SFR16 (PCA0CP3, 0xEDU);                 // PCA0 Module 3 Capture
SFR16 (PCA0, 0xF9U);                    // PCA0 Counter
SFR16 (PCA0CP0, 0xFBU);                 // PCA0 Module 0 Capture
SFR16 (PCA0CP4, 0xFDU);                 // PCA0 Module 4 Capture

SFR16 (CAN0ERR, 0x96U);                 // Error Counter
SFR16 (CAN0BT, 0x9AU);                  // Bit Timing Register
SFR16 (CAN0IID, 0x9CU);                 // Interrupt Register
SFR16 (CAN0TR1, 0xA2U);                 // Transmission Request 1
SFR16 (CAN0TR2, 0xA4U);                 // Transmission Request 2
SFR16 (CAN0ND1, 0xAAU);                 // New Data 1
SFR16 (CAN0ND2, 0xACU);                 // New Data 2
SFR16 (CAN0IP1, 0xAEU);                 // Interrupt Pending 1
SFR16 (CAN0IP2, 0xB2U);                 // Interrupt Pending 2
SFR16 (CAN0MV1, 0xBAU);                 // Message Valid 1
SFR16 (CAN0MV2, 0xBCU);                 // Message Valid 2
SFR16 (CAN0IF1CR, 0xBEU);               // IF1 Command Request
SFR16 (CAN0IF1CM, 0xC2U);               // IF1 Command Mask
SFR16 (CAN0IF1M1, 0xC4U);               // IF1 Mask 1
SFR16 (CAN0IF1M2, 0xC6U);               // IF1 Mask 2
SFR16 (CAN0IF1A1, 0xCAU);               // IF1 Arbitration 1
SFR16 (CAN0IF1A2, 0xCCU);               // IF1 Arbitration 2
SFR16 (CAN0IF2MC, 0xCEU);               // IF2 Message Control
SFR16 (CAN0IF1MC, 0xD2U);               // IF1 Message Control
SFR16 (CAN0IF1DA1, 0xD4U);              // IF1 Data A 1
SFR16 (CAN0IF1DA2, 0xD6U);              // IF1 Data A 2
SFR16 (CAN0IF1DB1, 0xDAU);              // IF1 Data B 1
SFR16 (CAN0IF1DB2, 0xDCU);              // IF1 Data B 2
SFR16 (CAN0IF2CR, 0xDEU);               // IF2 Command Request
SFR16 (CAN0IF2CM, 0xE2U);               // IF2 Command Mask
SFR16 (CAN0IF2M1, 0xEAU);               // IF2 Mask 1
SFR16 (CAN0IF2M2, 0xECU);               // IF2 Mask 2
SFR16 (CAN0IF2A1, 0xEEU);               // IF2 Arbitration 1
SFR16 (CAN0IF2A2, 0xF2U);               // IF2 Arbitration 2
SFR16 (CAN0IF2DA1, 0xF6U);              // IF2 Data A 1
SFR16 (CAN0IF2DA2, 0xFAU);              // IF2 Data A 2
SFR16 (CAN0IF2DB1, 0xFCU);              // IF2 Data B 1
SFR16 (CAN0IF2DB2, 0xFEU);              // IF2 Data B 2

//-----------------------------------------------------------------------------
// LIN0 Indirect Registers
//-----------------------------------------------------------------------------

#define  LIN0DT1   0x00U                // LIN0 Data Byte 1
#define  LIN0DT2   0x01U                // LIN0 Data Byte 2
#define  LIN0DT3   0x02U                // LIN0 Data Byte 3
#define  LIN0DT4   0x03U                // LIN0 Data Byte 4
#define  LIN0DT5   0x04U                // LIN0 Data Byte 5
#define  LIN0DT6   0x05U                // LIN0 Data Byte 6
#define  LIN0DT7   0x06U                // LIN0 Data Byte 7
#define  LIN0DT8   0x07U                // LIN0 Data Byte 8
#define  LIN0CTRL  0x08U                // LIN0 Control
#define  LIN0ST    0x09U                // LIN0 Status
#define  LIN0ERR   0x0AU                // LIN0 Error
#define  LIN0SIZE  0x0BU                // LIN0 Message Size
#define  LIN0DIV   0x0CU                // LIN0 Divider
#define  LIN0MUL   0x0DU                // LIN0 Multiplier
#define  LIN0ID    0x0EU                // LIN0 Identifier

//-----------------------------------------------------------------------------
// Address Definitions for Bit-addressable Registers
//-----------------------------------------------------------------------------

#define SFR_P0       0x80U
#define SFR_TCON     0x88U
#define SFR_P1       0x90U
#define SFR_SCON0    0x98U
#define SFR_P2       0xA0U
#define SFR_IE       0xA8U
#define SFR_P3       0xB0U
#define SFR_IP       0xB8U
#define SFR_SMB0CN   0xC0U
#define SFR_TMR2CN   0xC8U
#define SFR_PSW      0xD0U
#define SFR_PCA0CN   0xD8U
#define SFR_ACC      0xE0U
#define SFR_ADC0CN   0xE8U
#define SFR_B        0xF0U
#define SFR_SPI0CN   0xF8U

//-----------------------------------------------------------------------------
// Bit Definitions
//-----------------------------------------------------------------------------

// TCON 0x88
SBIT (TF1, SFR_TCON, 7);               // Timer 1 Overflow Flag
SBIT (TR1, SFR_TCON, 6);               // Timer 1 On/Off Control
SBIT (TF0, SFR_TCON, 5);               // Timer 0 Overflow Flag
SBIT (TR0, SFR_TCON, 4);               // Timer 0 On/Off Control
SBIT (IE1, SFR_TCON, 3);               // Ext. Interrupt 1 Edge Flag
SBIT (IT1, SFR_TCON, 2);               // Ext. Interrupt 1 Type
SBIT (IE0, SFR_TCON, 1);               // Ext. Interrupt 0 Edge Flag
SBIT (IT0, SFR_TCON, 0);               // Ext. Interrupt 0 Type

// SCON0 0x98
SBIT (OVR0, SFR_SCON0, 7);             // UART0 Mode 0
SBIT (PERR0, SFR_SCON0, 6);            // UART0 Parity Error Flag
SBIT (THRE0, SFR_SCON0, 5);            // UART0 Transmit Holding Reg. Empty
SBIT (REN0, SFR_SCON0, 4);             // UART0 RX Enable
SBIT (TBX0, SFR_SCON0, 3);             // UART0 TX Bit 8
SBIT (RBX0, SFR_SCON0, 2);             // UART0 RX Bit 8
SBIT (TI0, SFR_SCON0, 1);              // UART0 TX Interrupt Flag
SBIT (RI0, SFR_SCON0, 0);              // UART0 RX Interrupt Flag

// IE 0xA8
SBIT (EA, SFR_IE, 7);                  // Global Interrupt Enable
SBIT (ESPI0, SFR_IE, 6);               // SPI0 Interrupt Enable
SBIT (ET2, SFR_IE, 5);                 // Timer 2 Interrupt Enable
SBIT (ES0, SFR_IE, 4);                 // UART0 Interrupt Enable
SBIT (ET1, SFR_IE, 3);                 // Timer 1 Interrupt Enable
SBIT (EX1, SFR_IE, 2);                 // External Interrupt 1 Enable
SBIT (ET0, SFR_IE, 1);                 // Timer 0 Interrupt Enable
SBIT (EX0, SFR_IE, 0);                 // External Interrupt 0 Enable

// IP 0xB8
                                       // Bit 7 unused
SBIT (PSPI0, SFR_IP, 6);               // SPI0 Interrupt Priority
SBIT (PT2, SFR_IP, 5);                 // Timer 2 Priority
SBIT (PS0, SFR_IP, 4);                 // UART0 Priority
SBIT (PS, SFR_IP, 4);                  // UART0 Priority
SBIT (PT1, SFR_IP, 3);                 // Timer 1 Priority
SBIT (PX1, SFR_IP, 2);                 // External Interrupt 1 Priority
SBIT (PT0, SFR_IP, 1);                 // Timer 0 Priority
SBIT (PX0, SFR_IP, 0);                 // External Interrupt 0 Priority

// SMB0CN 0xC0
SBIT (MASTER, SFR_SMB0CN, 7);          // SMBus0 Master/Slave Indicator
SBIT (TXMODE, SFR_SMB0CN, 6);          // SMBus0 Transmit Mode Indicator
SBIT (STA, SFR_SMB0CN, 5);             // SMBus0 Start Flag
SBIT (STO, SFR_SMB0CN, 4);             // SMBus0 Stop Flag
SBIT (ACKRQ, SFR_SMB0CN, 3);           // SMBus0 Acknowledge Request
SBIT (ARBLOST, SFR_SMB0CN, 2);         // SMBus0 Arbitration Lost Indicator
SBIT (ACK, SFR_SMB0CN, 1);             // SMBus0 Acknowledge
SBIT (SI, SFR_SMB0CN, 0);              // SMBus0 Interrupt Flag

// TMR2CN 0xC8
SBIT (TF2H, SFR_TMR2CN, 7);            // Timer 2 High-Byte Overflow Flag
SBIT (TF2L, SFR_TMR2CN, 6);            // Timer 2 Low-Byte  Overflow Flag
SBIT (TF2LEN, SFR_TMR2CN, 5);          // Timer 2 Low-Byte Flag Enable
SBIT (TF2CEN, SFR_TMR2CN, 4);          // Timer 2 Capture Enable
SBIT (T2SPLIT, SFR_TMR2CN, 3);         // Timer 2 Split-Mode Enable
SBIT (TR2, SFR_TMR2CN, 2);             // Timer2 Run Enable
                                       // Unused
SBIT (T2XCLK, SFR_TMR2CN, 0);          // Timer 2 Clk/8 Clock Source

// PSW 0xD0
SBIT (CY, SFR_PSW, 7);                 // Carry Flag
SBIT (AC, SFR_PSW, 6);                 // Auxiliary Carry Flag
SBIT (F0, SFR_PSW, 5);                 // User Flag 0
SBIT (RS1, SFR_PSW, 4);                // Register Bank Select 1
SBIT (RS0, SFR_PSW, 3);                // Register Bank Select 0
SBIT (OV, SFR_PSW, 2);                 // Overflow Flag
SBIT (F1, SFR_PSW, 1);                 // User Flag 1
SBIT (P, SFR_PSW, 0);                  // Accumulator Parity Flag

// PCA0CN 0xD8
SBIT (CF, SFR_PCA0CN, 7);              // PCA0 Counter Overflow Flag
SBIT (CR, SFR_PCA0CN, 6);              // PCA0 Counter Run Control Bit
SBIT (CCF5, SFR_PCA0CN, 5);            // PCA0 Module 5 Interrupt Flag
SBIT (CCF4, SFR_PCA0CN, 4);            // PCA0 Module 4 Interrupt Flag
SBIT (CCF3, SFR_PCA0CN, 3);            // PCA0 Module 3 Interrupt Flag
SBIT (CCF2, SFR_PCA0CN, 2);            // PCA0 Module 2 Interrupt Flag
SBIT (CCF1, SFR_PCA0CN, 1);            // PCA0 Module 1 Interrupt Flag
SBIT (CCF0, SFR_PCA0CN, 0);            // PCA0 Module 0 Interrupt Flag

// ADC0CN 0xE8
SBIT (AD0EN, SFR_ADC0CN, 7);           // ADC0 Enable
SBIT (BURSTEN, SFR_ADC0CN, 6);         // ADC0 Burst Enable
SBIT (AD0INT, SFR_ADC0CN, 5);          // ADC0 EOC Interrupt Flag
SBIT (AD0BUSY, SFR_ADC0CN, 4);         // ADC0 Busy Flag
SBIT (AD0WINT, SFR_ADC0CN, 3);         // ADC0 Window Compare Interrupt Flag
SBIT (AD0LJST, SFR_ADC0CN, 2);         // ADC0 Left Justified
SBIT (AD0CM1, SFR_ADC0CN, 1);          // ADC0 Start Of Conversion Mode Bit 1
SBIT (AD0CM0, SFR_ADC0CN, 0);          // ADC0 Start Of Conversion Mode Bit 0

// SPI0CN 0xF8
SBIT (SPIF, SFR_SPI0CN, 7);            // SPI0 Interrupt Flag
SBIT (WCOL, SFR_SPI0CN, 6);            // SPI0 Write Collision Flag
SBIT (MODF, SFR_SPI0CN, 5);            // SPI0 Mode Fault Flag
SBIT (RXOVRN, SFR_SPI0CN, 4);          // SPI0 RX Overrun Flag
SBIT (NSSMD1, SFR_SPI0CN, 3);          // SPI0 Slave Select Mode 1
SBIT (NSSMD0, SFR_SPI0CN, 2);          // SPI0 Slave Select Mode 0
SBIT (TXBMT, SFR_SPI0CN, 1);           // SPI0 TX Buffer Empty Flag
SBIT (SPIEN, SFR_SPI0CN, 0);           // SPI0 Enable

//-----------------------------------------------------------------------------
// Interrupt Priorities
//-----------------------------------------------------------------------------

#define INTERRUPT_INT0             0   // External Interrupt 0
#define INTERRUPT_TIMER0           1   // Timer0 Overflow
#define INTERRUPT_INT1             2   // External Interrupt 1
#define INTERRUPT_TIMER1           3   // Timer1 Overflow
#define INTERRUPT_UART0            4   // UART0
#define INTERRUPT_TIMER2           5   // Timer2 Overflow
#define INTERRUPT_SPI0             6   // SPI0
#define INTERRUPT_SMBUS0           7   // SMBus0 Interface
#define INTERRUPT_ADC0_WINDOW      8   // ADC0 Window Comparison
#define INTERRUPT_ADC0_EOC         9   // ADC0 End Of Conversion
#define INTERRUPT_PCA0            10   // PCA0 Peripheral
#define INTERRUPT_COMPARATOR0     11   // Comparator0 Comparison
#define INTERRUPT_COMPARATOR1     12   // Comparator1 Comparison
#define INTERRUPT_TIMER3          13   // Timer3 Overflow
#define INTERRUPT_LIN0            14   // LIN Bus Interrupt
#define INTERRUPT_VREG            15   // Voltage Regulator
#define INTERRUPT_CAN0            16   // CAN Bus Interrupt
#define INTERRUPT_PORT_MATCH      17   // Port Match

//-----------------------------------------------------------------------------
// SFR Page Definitions
//-----------------------------------------------------------------------------

#define  CONFIG_PAGE       0x0FU        // System and Port Configuration Page
#define  ACTIVE_PAGE       0x00U        // Active Use Page
#define  CAN0_PAGE         0x0CU        // CAN0 Registers

//-----------------------------------------------------------------------------
// Header File PreProcessor Directive
//-----------------------------------------------------------------------------

#else

//-----------------------------------------------------------------------------
// Page 0 and Page F Registers
//-----------------------------------------------------------------------------
#define P0 *(U8*)0x80U                        // Port 0 Latch
#define SP *(U8*)0x81U                        // Stack Pointer
#define DPL *(U8*)0x82U                       // Data Pointer Low
#define DPH *(U8*)0x83U                       // Data Pointer High
#define SFR0CN *(U8*)0x84U                    // SFR Page Control
#define SFRNEXT *(U8*)0x85U                   // SFR stack next page
#define SFRLAST *(U8*)0x86U                   // SFR stack last page
#define PCON *(U8*)0x87U                      // Power Control
#define TCON *(U8*)0x88U                      // Timer/Counter Control
#define TMOD *(U8*)0x89U                      // Timer/Counter Mode
#define TL0 *(U8*)0x8AU                       // Timer/Counter 0 Low
#define TL1 *(U8*)0x8BU                       // Timer/Counter 1 Low
#define TH0 *(U8*)0x8CU                       // Timer/Counter 0 High
#define TH1 *(U8*)0x8DU                       // Timer/Counter 1 High
#define CKCON *(U8*)0x8EU                     // Clock Control
#define PSCTL *(U8*)0x8FU                     // Program Store R/W Control
#define CLKSEL *(U8*)0x8FU                    // System clock select
#define P1 *(U8*)0x90U                        // Port 1 Latch
#define TMR3CN *(U8*)0x91U                    // Timer/Counter 3 Control
#define TMR3RLL *(U8*)0x92U                   // Timer/Counter 3 Reload Low
#define TMR3RLH *(U8*)0x93U                   // Timer/Counter 3 Reload High
#define TMR3L *(U8*)0x94U                     // Timer/Counter 3 Low
#define TMR3H *(U8*)0x95U                     // Timer/Counter 3 High
#define CLKMUL *(U8*)0x97U                    // Clock Multiplier
#define SCON0 *(U8*)0x98U                     // UART0 Control
#define SBUF0 *(U8*)0x99U                     // UART0 Data Buffer
#define CPT0CN *(U8*)0x9AU                    // Comparator 0 Control
#define CPT0MD *(U8*)0x9BU                    // Comparator 0 Mode
#define CPT0MX *(U8*)0x9CU                    // Comparator 0 Mux
#define CPT1CN *(U8*)0x9DU                    // Comparator 1 Control
#define CPT1MD *(U8*)0x9EU                    // Comparator 0 Mode
#define OSCIFIN *(U8*)0x9EU                   // Internal Oscillator Fine Control
#define CPT1MX *(U8*)0x9FU                    // Comparator 1 Mux
#define OSCXCN *(U8*)0x9FU                    // External Oscillator Control
#define P2 *(U8*)0xA0U                        // Port 2 Latch
#define SPI0CFG *(U8*)0xA1U                   // SPI0 Configuration
#define OSCICN *(U8*)0xA1U                    // Internal Oscillator Control
#define SPI0CKR *(U8*)0xA2U                   // SPI0 Clock rate control
#define OSCICRS *(U8*)0xA2U                   // Internal Oscillator Coarse Control
#define SPI0DAT *(U8*)0xA3U                   // SPI0 Data Buffer
#define P0MDOUT *(U8*)0xA4U                   // Port 0 Output Mode
#define P1MDOUT *(U8*)0xA5U                   // Port 1 Output Mode
#define P2MDOUT *(U8*)0xA6U                   // Port 2 Output Mode
#define SFRPAGE *(U8*)0xA7U                   // SFR Page Select
#define IE *(U8*)0xA8U                        // Interrupt Enable
#define SMOD0 *(U8*)0xA9U                     // Serial Port 0 Control
#define EMI0CN *(U8*)0xAAU                    // EMIF control
#define EMI0TC *(U8*)0xAAU                    // EMIF Timing control
#define SBCON0 *(U8*)0xABU                    // UART0 Baud Rate Generator Control
#define SBRLL0 *(U8*)0xACU                    // UART0 Baud Rate Generator Low
#define SBRLH0 *(U8*)0xADU                    // UART0 Baud Rate Generator High
#define P3MAT *(U8*)0xAEU                     // Port 3 Match
#define P3MDOUT *(U8*)0xAEU                   // Port 3 Mode
#define P3MASK *(U8*)0xAFU                    // Port 3 Mask
#define P4MDOUT *(U8*)0xAFU                   // Port 4 Mode
#define P3 *(U8*)0xB0U                        // Port 3 Latch
#define P2MAT *(U8*)0xB1U                     // Port 2 Match
#define P2MASK *(U8*)0xB2U                    // Port 2 Mask
#define EMI0CF *(U8*)0xB2U                    // EMIF Configuration
#define P4 *(U8*)0xB5U                        // Port 4 Latch
#define FLSCL *(U8*)0xB6U                     // Flash Scale
#define FLKEY *(U8*)0xB7U                     // Flash access limit
#define IP *(U8*)0xB8U                        // Interrupt Priority
#define SMB0ADR *(U8*)0xB9U                   // SMBus0 Slave address
#define ADC0TK *(U8*)0xBAU                    // ADC0 Tracking Mode Select
#define SMB0ADM *(U8*)0xBAU                   // SMBus0 Address Mask
#define ADC0MX *(U8*)0xBBU                    // AMUX0 Channel select
#define ADC0CF *(U8*)0xBCU                    // AMUX0 Channel configuration
#define ADC0L *(U8*)0xBDU                     // ADC0 Data Low
#define ADC0H *(U8*)0xBEU                     // ADC0 Data High
#define SMB0CN *(U8*)0xC0U                    // SMBus0 Control
#define SMB0CF *(U8*)0xC1U                    // SMBus0 Configuration
#define SMB0DAT *(U8*)0xC2U                   // SMBus0 Data
#define ADC0GTL *(U8*)0xC3U                   // ADC0 Greater-Than Compare Low
#define ADC0GTH *(U8*)0xC4U                   // ADC0 Greater-Than Compare High
#define ADC0LTL *(U8*)0xC5U                   // ADC0 Less-Than Compare Word Low
#define ADC0LTH *(U8*)0xC6U                   // ADC0 Less-Than Compare Word High
#define XBR2 *(U8*)0xC7U                      // Port I/O Crossbar Control 2
#define TMR2CN *(U8*)0xC8U                    // Timer/Counter 2 Control
#define REG0CN *(U8*)0xC9U                    // Regulator Control
#define LIN0CF *(U8*)0xC9U                    // LIN 0 Configuration
#define TMR2RLL *(U8*)0xCAU                   // Timer/Counter 2 Reload Low
#define TMR2RLH *(U8*)0xCBU                   // Timer/Counter 2 Reload High
#define TMR2L *(U8*)0xCCU                     // Timer/Counter 2 Low
#define TMR2H *(U8*)0xCDU                     // Timer/Counter 2 High
#define PCA0CPL5 *(U8*)0xCEU                  // PCA0 Capture 5 Low
#define PCA0CPH5 *(U8*)0xCFU                  // PCA0 Capture 5 High
#define PSW *(U8*)0xD0U                       // Program Status Word
#define REF0CN *(U8*)0xD1U                    // Voltage Reference Control
#define LIN0DAT *(U8*)0xD2U                   // LIN0 Data
#define LIN0ADR *(U8*)0xD3U                   // LIN0 Address
#define P0SKIP *(U8*)0xD4U                    // Port 0 Skip
#define P1SKIP *(U8*)0xD5U                    // Port 1 Skip
#define P2SKIP *(U8*)0xD6U                    // Port 2 Skip
#define P3SKIP *(U8*)0xD7U                    // Port 3 Skip
#define PCA0CN *(U8*)0xD8U                    // PCA0 Control
#define PCA0MD *(U8*)0xD9U                    // PCA0 Mode
#define PCA0PWM *(U8*)0xD9U                   // PCA0 PWM Control
#define PCA0CPM0 *(U8*)0xDAU                  // PCA0 Module 0 Mode Register
#define PCA0CPM1 *(U8*)0xDBU                  // PCA0 Module 1 Mode Register
#define PCA0CPM2 *(U8*)0xDCU                  // PCA0 Module 2 Mode Register
#define PCA0CPM3 *(U8*)0xDDU                  // PCA0 Module 3 Mode Register
#define PCA0CPM4 *(U8*)0xDEU                  // PCA0 Module 4 Mode Register
#define PCA0CPM5 *(U8*)0xDFU                  // PCA0 Module 5 Mode Register
#define ACC *(U8*)0xE0U                       // Accumulator
#define XBR0 *(U8*)0xE1U                      // Port I/O Crossbar Control 0
#define XBR1 *(U8*)0xE2U                      // Port I/O Crossbar Control 1
#define CCH0CN *(U8*)0xE3U                    // Cache control
#define IT01CF *(U8*)0xE4U                    // INT0/INT1 Configuration
#define EIE1 *(U8*)0xE6U                      // Extended Interrupt Enable 2
#define EIE2 *(U8*)0xE7U                      // Extended Interrupt Enable 2
#define ADC0CN *(U8*)0xE8U                    // ADC0 Control
#define PCA0CPL1 *(U8*)0xE9U                  // PCA0 Capture 2 Low
#define PCA0CPH1 *(U8*)0xEAU                  // PCA0 Capture 2 High
#define PCA0CPL2 *(U8*)0xEBU                  // PCA0 Capture 3 Low
#define PCA0CPH2 *(U8*)0xECU                  // PCA0 Capture 3 High
#define PCA0CPL3 *(U8*)0xEDU                  // PCA0 Capture 4 Low
#define PCA0CPH3 *(U8*)0xEEU                  // PCA0 Capture 4 High
#define RSTSRC *(U8*)0xEFU                    // Reset Source Configuration/Status
#define B *(U8*)0xF0U                         // B Register
#define P0MAT *(U8*)0xF1U                     // Port 0 Match
#define P0MDIN *(U8*)0xF1U                    // Port 0 Input Mode
#define P0MASK *(U8*)0xF2U                    // Port 0 Mask
#define P1MDIN *(U8*)0xF2U                    // Port 1 Input Mode
#define P1MAT *(U8*)0xF3U                     // Port 1 Match
#define P2MDIN *(U8*)0xF3U                    // Port 2 Input Mode
#define P1MASK *(U8*)0xF4U                    // Port 1 Mask
#define P3MDIN *(U8*)0xF4U                    // Port 3 Input Mode
#define EIP1 *(U8*)0xF6U                      // External Interrupt Priority 1
#define EIP2 *(U8*)0xF7U                      // External Interrupt Priority 2
#define SPI0CN *(U8*)0xF8U                    // SPI0 Control
#define PCA0L *(U8*)0xF9U                     // PCA0 Counter Low
#define SN0 *(U8*)0xF9U                       // Serial Number 0
#define PCA0H *(U8*)0xFAU                     // PCA0 Counter High
#define SN1 *(U8*)0xFAU                       // Serial Number 1
#define PCA0CPL0 *(U8*)0xFBU                  // PCA0 Capture 0 Low
#define SN2 *(U8*)0xFBU                       // Serial Number 2
#define PCA0CPH0 *(U8*)0xFCU                  // PCA0 Capture 0 High
#define SN3 *(U8*)0xFCU                       // Serial Number 3
#define PCA0CPL4 *(U8*)0xFDU                  // PCA0 Capture 4 Low
#define PCA0CPH4 *(U8*)0xFEU                  // PCA0 Capture 4 High
#define VDM0CN *(U8*)0xFFU                    // VDD Monitor Control

//-----------------------------------------------------------------------------
// Page C (CAN0) Registers
//-----------------------------------------------------------------------------

#define CAN0CFG *(U8*)0x92U                   // CAN0 Clock Configuration
#define CAN0STAT *(U8*)0x94U                  // Status Register Low Byte
#define CAN0ERRL *(U8*)0x96U                  // Error Counter Low Byte
#define CAN0ERRH *(U8*)0x97U                  // Error Counter High Byte
#define CAN0BTL *(U8*)0x9AU                   // Bit Timing Register Low Byte
#define CAN0BTH *(U8*)0x9BU                   // Bit Timing Register High Byte
#define CAN0IIDL *(U8*)0x9CU                  // Interrupt Register Low Byte
#define CAN0IIDH *(U8*)0x9DU                  // Interrupt Register High Byte
#define CAN0TST *(U8*)0x9EU                   // Test Register Low Byte
#define CAN0BRPE *(U8*)0xA1U                  // BRP Extension Register Low Byte
#define CAN0TR1L *(U8*)0xA2U                  // Transmission Request 1 Low Byte
#define CAN0TR1H *(U8*)0xA3U                  // Transmission Request 1 High Byte
#define CAN0TR2L *(U8*)0xA4U                  // Transmission Request 2 Low Byte
#define CAN0TR2H *(U8*)0xA5U                 // Transmission Request 2 High Byte
#define CAN0ND1L *(U8*)0xAAU                  // New Data 1 Low Byte
#define CAN0ND1H *(U8*)0xABU                  // New Data 1 High Byte
#define CAN0ND2L *(U8*)0xACU                  // New Data 2 Low Byte
#define CAN0ND2H *(U8*)0xADU                  // New Data 2 High Byte
#define CAN0IP1L *(U8*)0xAEU                  // Interrupt Pending 1 Low Byte
#define CAN0IP1H *(U8*)0xAFU                  // Interrupt Pending 1 High Byte
#define CAN0IP2L *(U8*)0xB2U                  // Interrupt Pending 2 Low Byte
#define CAN0IP2H *(U8*)0xB3U                  // Interrupt Pending 2 High Byte
#define CAN0MV1L *(U8*)0xBAU                  // Message Valid 1 Low Byte
#define CAN0MV1H *(U8*)0xBBU                  // Message Valid 1 High Byte
#define CAN0MV2L *(U8*)0xBCU                  // Message Valid 2 Low Byte
#define CAN0MV2H *(U8*)0xBDU                  // Message Valid 2 High Byte
#define CAN0IF1CRL *(U8*)0xBEU                // IF1 Command Request Low Byte
#define CAN0IF1CRH *(U8*)0xBFU                // IF1 Command Request High Byte
#define CAN0CN *(U8*)0xC0U                    // CAN Control Register Low Byte
#define CAN0IF1CML *(U8*)0xC2U                // IF1 Command Mask Low Byte
#define CAN0IF1CMH *(U8*)0xC3U                // IF1 Command Mask High Byte
#define CAN0IF1M1L *(U8*)0xC4U                // IF1 Mask 1 Low Byte
#define CAN0IF1M1H *(U8*)0xC5U                // IF1 Mask 1 High Byte
#define CAN0IF1M2L *(U8*)0xC6U                // IF1 Mask 2 Low Byte
#define CAN0IF1M2H *(U8*)0xC7U                // IF1 Mask 2 High Byte
#define CAN0IF1A1L *(U8*)0xCAU                // IF1 Arbitration 1 Low Byte
#define CAN0IF1A1H *(U8*)0xCBU                // IF1 Arbitration 1 High Byte
#define CAN0IF1A2L *(U8*)0xCCU                // IF1 Arbitration 2 Low Byte
#define CAN0IF1A2H *(U8*)0xCDU                // IF1 Arbitration 2 High Byte
#define CAN0IF2MCL *(U8*)0xCEU                // IF2 Message Control Low Byte
#define CAN0IF2MCH *(U8*)0xCFU                // IF2 Message Control High Byte
#define CAN0IF1MCL *(U8*)0xD2U                // IF1 Message Control Low Byte
#define CAN0IF1MCH *(U8*)0xD3U                // IF1 Message Control High Byte
#define CAN0IF1DA1L *(U8*)0xD4U               // IF1 Data A 1 Low Byte
#define CAN0IF1DA1H *(U8*)0xD5U               // IF1 Data A 1 High Byte
#define CAN0IF1DA2L *(U8*)0xD6U               // IF1 Data A 2 Low Byte
#define CAN0IF1DA2H *(U8*)0xD7U               // IF1 Data A 2 High Byte
#define CAN0IF1DB1L *(U8*)0xDAU               // IF1 Data B 1 Low Byte
#define CAN0IF1DB1H *(U8*)0xDBU               // IF1 Data B 1 High Byte
#define CAN0IF1DB2L *(U8*)0xDCU               // IF1 Data B 2 Low Byte
#define CAN0IF1DB2H *(U8*)0xDDU               // IF1 Data B 2 High Byte
#define CAN0IF2CRL *(U8*)0xDEU                // IF2 Command Request Low Byte
#define CAN0IF2CRH *(U8*)0xDFU                // IF2 Command Request High Byte
#define CAN0IF2CML *(U8*)0xE2U                // IF2 Command Mask Low Byte
#define CAN0IF2CMH *(U8*)0xE3U                // IF2 Command Mask High Byte
#define CAN0IF2M1L *(U8*)0xEAU                // IF2 Mask 1 Low Byte
#define CAN0IF2M1H *(U8*)0xEBU                // IF2 Mask 1 High Byte
#define CAN0IF2M2L *(U8*)0xECU                // IF2 Mask 2 Low Byte
#define CAN0IF2M2H *(U8*)0xEDU                // IF2 Mask 2 High Byte
#define CAN0IF2A1L *(U8*)0xEEU                // IF2 Arbitration 1 Low Byte
#define CAN0IF2A1H *(U8*)0xEFU                // IF2 Arbitration 1 High Byte
#define CAN0IF2A2L *(U8*)0xF2U                // IF2 Arbitration 2 Low Byte
#define CAN0IF2A2H *(U8*)0xF3U                // IF2 Arbitration 2 High Byte
#define CAN0IF2DA1L *(U8*)0xF6U               // IF2 Data A 1 Low Byte
#define CAN0IF2DA1H *(U8*)0xF7U               // IF2 Data A 1 High Byte
#define CAN0IF2DA2L *(U8*)0xFAU               // IF2 Data A 2 Low Byte
#define CAN0IF2DA2H *(U8*)0xFBU               // IF2 Data A 2 High Byte
#define CAN0IF2DB1L *(U8*)0xFCU               // IF2 Data B 1 Low Byte
#define CAN0IF2DB1H *(U8*)0xFDU               // IF2 Data B 1 High Byte
#define CAN0IF2DB2L *(U8*)0xFEU               // IF2 Data B 2 Low Byte
#define CAN0IF2DB2H *(U8*)0xFFU               // IF2 Data B 2 High Byte

//-----------------------------------------------------------------------------
//16-bit Register Definitions (might not be supported by all compilers)
//-----------------------------------------------------------------------------

#define DP *(U16*)0x82U                      // Data Pointer
#define TMR3RL *(U16*)0x92U                  // Timer3 Reload
#define TMR3 *(U16*)0x94U                    // Timer3 Capture / Reload
#define SBRL0 *(U16*)0xACU                   // UART0 Reload
#define ADC0 *(U16*)0xBDU                    // ADC0 data
#define ADC0GT *(U16*)0xC3U                  // ADC0 Greater Than Window
#define ADC0LT *(U16*)0xC5U                  // ADC0 Less Than Window
#define TMR2RL *(U16*)0xCAU                  // Timer 2 Reload
#define TMR2 *(U16*)0xCCU                    // Timer2 Capture / Reload
#define PCA0CP5 *(U16*)0xCEU                 // PCA0 Module 5 Capture
#define PCA0CP1 *(U16*)0xE9U                 // PCA0 Module 1 Capture
#define PCA0CP2 *(U16*)0xEBU                 // PCA0 Module 2 Capture
#define PCA0CP3 *(U16*)0xEDU                 // PCA0 Module 3 Capture
#define PCA0 *(U16*)0xF9U                    // PCA0 Counter
#define PCA0CP0 *(U16*)0xFBU                 // PCA0 Module 0 Capture
#define PCA0CP4 *(U16*)0xFDU                 // PCA0 Module 4 Capture

#define CAN0ERR *(U16*)0x96U                 // Error Counter
#define CAN0BT *(U16*)0x9AU                  // Bit Timing Register
#define CAN0IID *(U16*)0x9CU                 // Interrupt Register
#define CAN0TR1 *(U16*)0xA2U                 // Transmission Request 1
#define CAN0TR2 *(U16*)0xA4U                 // Transmission Request 2
#define CAN0ND1 *(U16*)0xAAU                 // New Data 1
#define CAN0ND2 *(U16*)0xACU                 // New Data 2
#define CAN0IP1 *(U16*)0xAEU                 // Interrupt Pending 1
#define CAN0IP2 *(U16*)0xB2U                 // Interrupt Pending 2
#define CAN0MV1 *(U16*)0xBAU                 // Message Valid 1
#define CAN0MV2 *(U16*)0xBCU                 // Message Valid 2
#define CAN0IF1CR *(U16*)0xBEU               // IF1 Command Request
#define CAN0IF1CM *(U16*)0xC2U               // IF1 Command Mask
#define CAN0IF1M1 *(U16*)0xC4U               // IF1 Mask 1
#define CAN0IF1M2 *(U16*)0xC6U               // IF1 Mask 2
#define CAN0IF1A1 *(U16*)0xCAU               // IF1 Arbitration 1
#define CAN0IF1A2 *(U16*)0xCCU               // IF1 Arbitration 2
#define CAN0IF2MC *(U16*)0xCEU               // IF2 Message Control
#define CAN0IF1MC *(U16*)0xD2U               // IF1 Message Control
#define CAN0IF1DA1 *(U16*)0xD4U              // IF1 Data A 1
#define CAN0IF1DA2 *(U16*)0xD6U              // IF1 Data A 2
#define CAN0IF1DB1 *(U16*)0xDAU              // IF1 Data B 1
#define CAN0IF1DB2 *(U16*)0xDCU              // IF1 Data B 2
#define CAN0IF2CR *(U16*)0xDEU               // IF2 Command Request
#define CAN0IF2CM *(U16*)0xE2U               // IF2 Command Mask
#define CAN0IF2M1 *(U16*)0xEAU               // IF2 Mask 1
#define CAN0IF2M2 *(U16*)0xECU               // IF2 Mask 2
#define CAN0IF2A1 *(U16*)0xEEU               // IF2 Arbitration 1
#define CAN0IF2A2 *(U16*)0xF2U               // IF2 Arbitration 2
#define CAN0IF2DA1 *(U16*)0xF6U              // IF2 Data A 1
#define CAN0IF2DA2 *(U16*)0xFAU              // IF2 Data A 2
#define CAN0IF2DB1 *(U16*)0xFCU              // IF2 Data B 1
#define CAN0IF2DB2 *(U16*)0xFEU              // IF2 Data B 2

//-----------------------------------------------------------------------------
// LIN0 Indirect Registers
//-----------------------------------------------------------------------------

#define  LIN0DT1   0x00U                // LIN0 Data Byte 1
#define  LIN0DT2   0x01U                // LIN0 Data Byte 2
#define  LIN0DT3   0x02U                // LIN0 Data Byte 3
#define  LIN0DT4   0x03U                // LIN0 Data Byte 4
#define  LIN0DT5   0x04U                // LIN0 Data Byte 5
#define  LIN0DT6   0x05U                // LIN0 Data Byte 6
#define  LIN0DT7   0x06U                // LIN0 Data Byte 7
#define  LIN0DT8   0x07U                // LIN0 Data Byte 8
#define  LIN0CTRL  0x08U                // LIN0 Control
#define  LIN0ST    0x09U                // LIN0 Status
#define  LIN0ERR   0x0AU                // LIN0 Error
#define  LIN0SIZE  0x0BU                // LIN0 Message Size
#define  LIN0DIV   0x0CU                // LIN0 Divider
#define  LIN0MUL   0x0DU                // LIN0 Multiplier
#define  LIN0ID    0x0EU                // LIN0 Identifier

//-----------------------------------------------------------------------------
// Address Definitions for Bit-addressable Registers
//-----------------------------------------------------------------------------

#define SFR_P0       0x80U
#define SFR_TCON     0x88U
#define SFR_P1       0x90U
#define SFR_SCON0    0x98U
#define SFR_P2       0xA0U
#define SFR_IE       0xA8U
#define SFR_P3       0xB0U
#define SFR_IP       0xB8U
#define SFR_SMB0CN   0xC0U
#define SFR_TMR2CN   0xC8U
#define SFR_PSW      0xD0U
#define SFR_PCA0CN   0xD8U
#define SFR_ACC      0xE0U
#define SFR_ADC0CN   0xE8U
#define SFR_B        0xF0U
#define SFR_SPI0CN   0xF8U

//-----------------------------------------------------------------------------
// Bit Definitions
//-----------------------------------------------------------------------------

// TCON 0x88
#define TF1 *(U8*)SFR_TCON               // Timer 1 Overflow Flag
#define TR1 *(U8*)SFR_TCON               // Timer 1 On/Off Control
#define TF0 *(U8*)SFR_TCON               // Timer 0 Overflow Flag
#define TR0 *(U8*)SFR_TCON               // Timer 0 On/Off Control
#define IE1 *(U8*)SFR_TCON               // Ext. Interrupt 1 Edge Flag
#define IT1 *(U8*)SFR_TCON               // Ext. Interrupt 1 Type
#define IE0 *(U8*)SFR_TCON               // Ext. Interrupt 0 Edge Flag
#define IT0 *(U8*)SFR_TCON               // Ext. Interrupt 0 Type

// SCON0 0x98
#define OVR0 *(U8*)SFR_SCON0             // UART0 Mode 0
#define PERR0 *(U8*)SFR_SCON0            // UART0 Parity Error Flag
#define THRE0 *(U8*)SFR_SCON0            // UART0 Transmit Holding Reg. Empty
#define REN0 *(U8*)SFR_SCON0             // UART0 RX Enable
#define TBX0 *(U8*)SFR_SCON0             // UART0 TX Bit 8
#define RBX0 *(U8*)SFR_SCON0             // UART0 RX Bit 8
#define TI0 *(U8*)SFR_SCON0              // UART0 TX Interrupt Flag
#define RI0 *(U8*)SFR_SCON0              // UART0 RX Interrupt Flag

// IE 0xA8
#define EA *(U8*)SFR_IE                  // Global Interrupt Enable
#define ESPI0 *(U8*)SFR_IE               // SPI0 Interrupt Enable
#define ET2 *(U8*)SFR_IE                 // Timer 2 Interrupt Enable
#define ES0 *(U8*)SFR_IE                 // UART0 Interrupt Enable
#define ET1 *(U8*)SFR_IE                 // Timer 1 Interrupt Enable
#define EX1 *(U8*)SFR_IE                 // External Interrupt 1 Enable
#define ET0 *(U8*)SFR_IE                 // Timer 0 Interrupt Enable
#define EX0 *(U8*)SFR_IE                 // External Interrupt 0 Enable

// IP 0xB8
// Bit 7 unused
#define PSPI0 *(U8*)SFR_IP               // SPI0 Interrupt Priority
#define PT2 *(U8*)SFR_IP                 // Timer 2 Priority
#define PS0 *(U8*)SFR_IP                 // UART0 Priority
#define PS *(U8*)SFR_IP                  // UART0 Priority
#define PT1 *(U8*)SFR_IP                 // Timer 1 Priority
#define PX1 *(U8*)SFR_IP                 // External Interrupt 1 Priority
#define PT0 *(U8*)SFR_IP                 // Timer 0 Priority
#define PX0 *(U8*)SFR_IP                 // External Interrupt 0 Priority

// SMB0CN 0xC0
#define MASTER *(U8*)SFR_SMB0CN          // SMBus0 Master/Slave Indicator
#define TXMODE *(U8*)SFR_SMB0CN          // SMBus0 Transmit Mode Indicator
#define STA *(U8*)SFR_SMB0CN             // SMBus0 Start Flag
#define STO *(U8*)SFR_SMB0CN             // SMBus0 Stop Flag
#define ACKRQ *(U8*)SFR_SMB0CN           // SMBus0 Acknowledge Request
#define ARBLOST *(U8*)SFR_SMB0CN         // SMBus0 Arbitration Lost Indicator
#define ACK *(U8*)SFR_SMB0CN             // SMBus0 Acknowledge
#define SI *(U8*)SFR_SMB0CN              // SMBus0 Interrupt Flag

// TMR2CN 0xC8
#define TF2H *(U8*)SFR_TMR2CN            // Timer 2 High-Byte Overflow Flag
#define TF2L *(U8*)SFR_TMR2CN            // Timer 2 Low-Byte  Overflow Flag
#define TF2LEN *(U8*)SFR_TMR2CN          // Timer 2 Low-Byte Flag Enable
#define TF2CEN *(U8*)SFR_TMR2CN          // Timer 2 Capture Enable
#define T2SPLIT *(U8*)SFR_TMR2CN         // Timer 2 Split-Mode Enable
#define TR2 *(U8*)SFR_TMR2CN             // Timer2 Run Enable
// Unused
#define T2XCLK *(U8*)SFR_TMR2CN          // Timer 2 Clk/8 Clock Source

// PSW 0xD0
#define CY *(U8*)SFR_PSW                 // Carry Flag
#define AC *(U8*)SFR_PSW                 // Auxiliary Carry Flag
#define F0 *(U8*)SFR_PSW                 // User Flag 0
#define RS1 *(U8*)SFR_PSW                // Register Bank Select 1
#define RS0 *(U8*)SFR_PSW                // Register Bank Select 0
#define OV *(U8*)SFR_PSW                 // Overflow Flag
#define F1 *(U8*)SFR_PSW                 // User Flag 1
#define P *(U8*)SFR_PSW                  // Accumulator Parity Flag

// PCA0CN 0xD8
#define CF *(U8*)SFR_PCA0CN              // PCA0 Counter Overflow Flag
#define CR *(U8*)SFR_PCA0CN              // PCA0 Counter Run Control Bit
#define CCF5 *(U8*)SFR_PCA0CN            // PCA0 Module 5 Interrupt Flag
#define CCF4 *(U8*)SFR_PCA0CN            // PCA0 Module 4 Interrupt Flag
#define CCF3 *(U8*)SFR_PCA0CN            // PCA0 Module 3 Interrupt Flag
#define CCF2 *(U8*)SFR_PCA0CN            // PCA0 Module 2 Interrupt Flag
#define CCF1 *(U8*)SFR_PCA0CN            // PCA0 Module 1 Interrupt Flag
#define CCF0 *(U8*)SFR_PCA0CN            // PCA0 Module 0 Interrupt Flag

// ADC0CN 0xE8
#define AD0EN *(U8*)SFR_ADC0CN           // ADC0 Enable
#define BURSTEN *(U8*)SFR_ADC0CN         // ADC0 Burst Enable
#define AD0INT *(U8*)SFR_ADC0CN          // ADC0 EOC Interrupt Flag
#define AD0BUSY *(U8*)SFR_ADC0CN         // ADC0 Busy Flag
#define AD0WINT *(U8*)SFR_ADC0CN         // ADC0 Window Compare Interrupt Flag
#define AD0LJST *(U8*)SFR_ADC0CN         // ADC0 Left Justified
#define AD0CM1 *(U8*)SFR_ADC0CN          // ADC0 Start Of Conversion Mode Bit 1
#define AD0CM0 *(U8*)SFR_ADC0CN          // ADC0 Start Of Conversion Mode Bit 0

// SPI0CN 0xF8
#define SPIF *(U8*)SFR_SPI0CN            // SPI0 Interrupt Flag
#define WCOL *(U8*)SFR_SPI0CN            // SPI0 Write Collision Flag
#define MODF *(U8*)SFR_SPI0CN            // SPI0 Mode Fault Flag
#define RXOVRN *(U8*)SFR_SPI0CN          // SPI0 RX Overrun Flag
#define NSSMD1 *(U8*)SFR_SPI0CN          // SPI0 Slave Select Mode 1
#define NSSMD0 *(U8*)SFR_SPI0CN          // SPI0 Slave Select Mode 0
#define TXBMT *(U8*)SFR_SPI0CN           // SPI0 TX Buffer Empty Flag
#define SPIEN *(U8*)SFR_SPI0CN           // SPI0 Enable

//-----------------------------------------------------------------------------
// Interrupt Priorities
//-----------------------------------------------------------------------------

#define INTERRUPT_INT0             0   // External Interrupt 0
#define INTERRUPT_TIMER0           1   // Timer0 Overflow
#define INTERRUPT_INT1             2   // External Interrupt 1
#define INTERRUPT_TIMER1           3   // Timer1 Overflow
#define INTERRUPT_UART0            4   // UART0
#define INTERRUPT_TIMER2           5   // Timer2 Overflow
#define INTERRUPT_SPI0             6   // SPI0
#define INTERRUPT_SMBUS0           7   // SMBus0 Interface
#define INTERRUPT_ADC0_WINDOW      8   // ADC0 Window Comparison
#define INTERRUPT_ADC0_EOC         9   // ADC0 End Of Conversion
#define INTERRUPT_PCA0            10   // PCA0 Peripheral
#define INTERRUPT_COMPARATOR0     11   // Comparator0 Comparison
#define INTERRUPT_COMPARATOR1     12   // Comparator1 Comparison
#define INTERRUPT_TIMER3          13   // Timer3 Overflow
#define INTERRUPT_LIN0            14   // LIN Bus Interrupt
#define INTERRUPT_VREG            15   // Voltage Regulator
#define INTERRUPT_CAN0            16   // CAN Bus Interrupt
#define INTERRUPT_PORT_MATCH      17   // Port Match
#define INTERRUPT_TEMP_TIMER2     18   // Timer2 Overflow

//-----------------------------------------------------------------------------
// SFR Page Definitions
//-----------------------------------------------------------------------------

#define  CONFIG_PAGE       0x0FU        // System and Port Configuration Page
#define  ACTIVE_PAGE       0x00U        // Active Use Page
#define  CAN0_PAGE         0x0CU        // CAN0 Registers

//-----------------------------------------------------------------------------
// Header File PreProcessor Directive
//-----------------------------------------------------------------------------

#endif

#endif                                 // #define C8051F560_DEFS_H

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
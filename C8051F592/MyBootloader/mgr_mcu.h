
/* ----- Global Define -------------------------------*/

#define DTC								(U8)0x01
#define ONESPEC							(U8)0x02

/*----------------------------------------------------*/
#define PAGE_SIZE               512

#define TGT_FLASH_SIZE     			(31*1024)   // Flash size of this MCU (1k Reserved)

// Signature Bytes
#define APP_SIG_BYTE0             0x21
#define APP_SIG_BYTE1             0x48
#define APP_SIG_BYTE2             0x78
#define APP_SIG_BYTE3             0x92

#define APP_START_SIG_ADDR     0x7FF0U

#define APPLICATION_MODE      0
#define BOOTLOADER_MODE       1  

#define INVALID      0x00
#define VALID        0x01

extern void START_APPLICATION(void);   // Function prototype for app's Reset
                                       // vector entry point
                                       // Defined in F50x_Target_BL_Startup.A51

									   // Bit masks for the RSTSRC SFR
#define PORSF  0x02
#define FERROR 0x40

/* ----- Function ------------------------------------*/
void Init_McuTask(void);
void Reset_Mcu(void);
void Operate_McuTask();
void Mcu_StandBy(U8 *pError);
void Mcu_InterInit(U8 *pError);
void Mcu_Idle(U8 *pError);
void Mcu_Running(U8 *pError);
U8 Get_Dser_Vs_Status(void);
void Check_Ser_Vs();
void Check_Dser_Vs();

/*----------------------------------------------------*/

/* ----- Extern Function -----------------------------*/
//extern U16 i2c_master_read(U8 slave_addr, U16 addr);
/*----------------------------------------------------*/

/* ----- Global Value --------------------------------*/
/*----------------------------------------------------*/




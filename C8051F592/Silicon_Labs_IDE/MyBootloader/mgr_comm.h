#ifndef MGR_COMM_H
#define MGR_COMM_H

/* ----- Global Define -------------------------------*/
/*
#define TW8836		0x00U
#define DESERIALIZE	0x01U
#define SERIALIZE	0x02U
*/
#define  INIT		      		0x00U           // (MR) data byte received
#define  RX			      		0x01U           // (MR) data byte received
#define  TX			      		0x02U           // (MR) data byte received

/*----------------------------------------------------*/

/* ----- Function ------------------------------------*/
void Init_CommTask(void);
void Operate_CommTask(void);
void Comm_StandBy(U8 *pError);
void Comm_InterInit(U8 *pError);
void Comm_Idle(U8 *pError);
void Comm_Running(U8 *pError);
void VCan_Restart(void);
/*----------------------------------------------------*/

/* ----- Extern Function -----------------------------*/
//extern U16 i2c_master_read(U8 slave_addr, U16 addr);
/*----------------------------------------------------*/

/* ----- Global Value --------------------------------*/

/*----------------------------------------------------*/

#endif


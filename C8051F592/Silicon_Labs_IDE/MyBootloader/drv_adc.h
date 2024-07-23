#ifndef DRV_ADC_H
#define DRV_ADC_H


/* ----- Global Define -------------------------------*/
#define ANALOG_INPUTS 			1
#define INT_DEC             	256        // Integrate and decimate ratio

#define ADC_65V			0x00U
#define ADC_ACC			0x01U
#define ADC_IGN			0x02U

#define CHECK_65V_ACC_SHORT 	0xD010
#define CHECK_65V_GND_SHORT 	0x6530

#define CHECK_ACC_85V		 	0x98D0
#define CHECK_ACC_70V		 	0x82AF
#define CHECK_IGN_70V		 	0x88EB
#define CHECK_IGN_65V		 	0x8150
#define CHECK_IGN_90V		 	0x9EC8
#define CHECK_IGN_16V		 	0xC350

#define ADC_ACC_HIGH			0x01
#define ADC_ACC_LOW				0x02
#define ADC_ACC_LOW_70V         0x03

#define ADC_IGN_HIGH			0x01
#define ADC_IGN_MID				0x02
#define ADC_IGN_LOW				0x03

#define ADC_65V_HIGH			0x01
#define ADC_65V_LOW				0x02


#define SCALE                    1000L // Scale for temp calculations
#define SAMPLING_NUMBER            256 // Number of samples per calculation

#define OVER_ROUND                  10 // Number of shifts (>>N) to reach the
//#define OVER_ROUND                  10 // Number of shifts (>>N) to reach the
                                       // correct number of bits of precision

//    T(C) = 3.0469*ADC_sum - 265.61;
#define REV_B                     0x01 // Value of the REVID register for
                                       // revision B
//#define SLOPE_REV_B               2578 // Slope of the temp transfer function
#define SLOPE_REV_B               3047   // Slope of the temp transfer function
#define OFFSET_REV_B           265610 // Offset for the temp transfer function
                                       // These values are for revision B
                                       // devices with the equation
                                       //     Vtemp = 2.67T(C) + 713mV

#define REV_C                     0x02 // Value of the REVID register for
                                       // revision C
#define SLOPE_REV_C               2261 // Slope of the temp transfer function
#define OFFSET_REV_C           265610L // Offset for the temp transfer function
/*----------------------------------------------------*/


/* ----- Global Value --------------------------------*/

/*----------------------------------------------------*/


/* ----- Function ------------------------------------*/
void ADC_Init(void);
U8 Get_Video_Signal(void);
U8 Get_Temperature(void);
U8 Get_ACC_State(void);
U8 Get_IGN_State(void);
void Temperature_compute(void);
void Acc_Compute(void);
void Ign_Compute(void);
void V65_Compute(void);
/*
U8 Check_65V_ACC_Short(void);

U8 Check_65V_GND_Short(void);


U8 Check_ACC_85V_Low(void);

U8 Check_ACC_85V_High(void);

U8 Check_IGN_70V_High(void);

U8 Check_IGN_65V_Low(void);
*/


/*----------------------------------------------------*/


/* ----- INTERRUPT -----------------------------------*/

/*----------------------------------------------------*/

/* ----- Extern Function -----------------------------*/

/*----------------------------------------------------*/

#endif


#ifndef __TOUCH_7846_H
#define __TOUCH_7846_H

#include "stm32f4xx.h"	

/* Private typedef -----------------------------------------------------------*/
typedef	struct POINT
{
   uint16_t x;
   uint16_t y;
}Coordinate;


typedef struct Matrix
{
  long double 	An,
  		Bn,
		Cn,
		Dn,
		En,
		Fn,
		Divider ;
} Matrix ;

/* Private variables ---------------------------------------------------------*/
extern Coordinate ScreenSample[3];
extern Coordinate DisplaySample[3];
extern Matrix matrix ;
extern Coordinate  display ;

/* Private define ------------------------------------------------------------*/
#define	CHX 	0x90 	
#define	CHY 	0xd0	


#define TP_CS(a)	if (a)	\
			GPIO_SetBits(GPIOB,GPIO_Pin_12);\
			else		\
			GPIO_ResetBits(GPIOB,GPIO_Pin_12)

#define TP_INT_IN   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)

/* Private function prototypes -----------------------------------------------*/				
void TP_Init(void);	
Coordinate *Read_Ads7846(void);
void TouchPanel_Calibrate(void);
void DrawCross(uint16_t Xpos,uint16_t Ypos);
void TP_DrawPoint(uint16_t Xpos,uint16_t Ypos);
FunctionalState setCalibrationMatrix( Coordinate * displayPtr,Coordinate * screenPtr,Matrix * matrixPtr);
FunctionalState getDisplayPoint(Coordinate * displayPtr,Coordinate * screenPtr,Matrix * matrixPtr );
uint8_t LCD_TouchRead(Coordinate * displayPtr);
#endif



















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
#define	CHX 	0x90 	/* 通道Y+的选择控制字 */	
#define	CHY 	0xd0	/* 通道X+的选择控制字 */


#define TP_CS(a)	if (a)	\
			GPIO_SetBits(GPIOB,GPIO_Pin_12);\
			else		\
			GPIO_ResetBits(GPIOB,GPIO_Pin_12)

#define TP_INT_IN   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)

/* Private function prototypes -----------------------------------------------*/				
extern void TP_Init(void);	
extern Coordinate *Read_Ads7846(void);
extern void TouchPanel_Calibrate(void);
extern void DrawCross(uint16_t Xpos,uint16_t Ypos);
extern void TP_DrawPoint(uint16_t Xpos,uint16_t Ypos);
extern FunctionalState setCalibrationMatrix( Coordinate * displayPtr,Coordinate * screenPtr,Matrix * matrixPtr);
extern FunctionalState getDisplayPoint(Coordinate * displayPtr,Coordinate * screenPtr,Matrix * matrixPtr );

#endif



















/**
  ******************************************************************************
  * @file     touch_7846.c
  * @author
  * @version
  * @date
  * @brief
  *
  *
  ******************************************************************************
  * @attention
  ******************************************************************************
  */
#ifndef	__TOUCH_7846_H_
#define	__TOUCH_7846_H_

/* Includes ------------------------------------------------------------------*/
#include "utility.h"
#include <stdio.h>

/* Private define ------------------------------------------------------------*/
#define THRESHOLD 2   /* 差值门限 */

/* Private variables ---------------------------------------------------------*/
Matrix matrix ;
Coordinate  display ;
Coordinate ScreenSample[3];
Coordinate DisplaySample[3] =   {
  				{ 45, 45 },
				{ 45, 270},
				{ 190,190}
				} ;



extern uint8_t Pen_Pressed;
uint8_t PMode2;
/*******************************************************************************
*obtiene valor PMode2 de Formato de pantalla*/
/******************************************************************************/
void GetFormat(void)				
{
  PMode2=LCD_FormatRead();
}
/*******************************************************************************
* Function Name  : ADS7843_SPI_Init
* Description    : ADS7843 SPI 初始化
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void ADS7843_SPI_Init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
  /* DISABLE SPI2 */
  //SPI_Cmd(SPI2, DISABLE);
  SPI_I2S_DeInit(SPI2);	
  /* SPI2 Config -------------------------------------------------------------*/
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI2, &SPI_InitStructure);
  /* Enable SPI2 */
  SPI_Cmd(SPI2, ENABLE);
}

/*******************************************************************************
* Function Name  : TP_Init
* Description    : ADS7843端口初始化
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void TP_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  /* Configure SPI2 pins: SCK, MISO and MOSI ---------------------------------*/
  RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD, ENABLE);

  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_25MHz;
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;

  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_15|GPIO_Pin_13|GPIO_Pin_14;			
  GPIO_Init(GPIOB,&GPIO_InitStruct);			

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);      //sclk	10	 13
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);	//m齭o	11	 14
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);	//mos�	12	 15
  /* TP_CS */
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12; // 3
  GPIO_Init(GPIOB,&GPIO_InitStruct);    // d  	
  /* TP_IRQ */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;
  GPIO_Init(GPIOD,&GPIO_InitStruct);
  /**/
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource6);  	
  EXTI_InitStructure.EXTI_Line = EXTI_Line6;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);	    				
  /**/
  TP_CS(1);
  ADS7843_SPI_Init();
}


void EXTI9_5_IRQHandler(void)		
{
  if(EXTI_GetITStatus(EXTI_Line6) != RESET)
  {
   Pen_Pressed=1;	
   EXTI_ClearITPendingBit(EXTI_Line6);
   // Read_Ads7846();
  }
}
/*******************************************************************************
* Function Name  : DelayUS
* Description    : 延时1us
* Input          : - cnt: 延时值
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void DelayUS(vu32 cnt)
{
  uint16_t i;
  for(i = 0;i<cnt;i++)
  {
     uint8_t us = 12; /* 设置值为12，大约延1微秒 */
     while (us--)     /* 延1微秒	*/
     {
       ;
     }
  }
}


/*******************************************************************************
* Function Name  : WR_CMD
* Description    : 向 ADS7843写数据
* Input          : - cmd: 传输的数据
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void WR_CMD (uint8_t cmd)
{
  /* Wait for SPI2 Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
  /* Send SPI2 data */
  SPI_I2S_SendData(SPI2,cmd);
  /* Wait for SPI2 data reception */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
  /* Read SPI2 received data */
  SPI_I2S_ReceiveData(SPI2);
}



/*******************************************************************************
* Function Name  : RD_AD
* Description    : 读取ADC值
* Input          : None
* Output         : None
* Return         : ADS7843返回二字节数据
* Attention		 : None
*******************************************************************************/
static int RD_AD(void)
{
  unsigned short buf,temp;
  /* Wait for SPI2 Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
  /* Send SPI2 data */
  SPI_I2S_SendData(SPI2,0x0000);
  /* Wait for SPI2 data reception */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
  /* Read SPI2 received data */
  temp=SPI_I2S_ReceiveData(SPI2);
  buf=temp<<8;
  DelayUS(1);
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
  /* Send SPI2 data */
  SPI_I2S_SendData(SPI2,0x0000);
  /* Wait for SPI2 data reception */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
  /* Read SPI2 received data */
  temp=SPI_I2S_ReceiveData(SPI2);
  buf |= temp;
  buf>>=3;
  buf&=0xfff;
  return buf;
}


/*******************************************************************************
* Function Name  : Read_X
* Description    : 读取ADS7843通道X+的ADC值
* Input          : None
* Output         : None
* Return         : ADS7843返回通道X+的ADC值
* Attention		 : None
*******************************************************************************/
int Read_X(void)
{
  int i;
  TP_CS(0);
  DelayUS(1);
  WR_CMD(CHX);
  DelayUS(1);
  i=RD_AD();
  TP_CS(1);
  return i;
}

/*******************************************************************************
* Function Name  : Read_Y
* Description    : 读取ADS7843通道Y+的ADC值
* Input          : None
* Output         : None
* Return         : ADS7843返回通道Y+的ADC值
* Attention		 : None
*******************************************************************************/
int Read_Y(void)
{
  int i;
  TP_CS(0);
  DelayUS(1);
  WR_CMD(CHY);
  DelayUS(1);
  i=RD_AD();
  TP_CS(1);
  return i;
}


/*******************************************************************************
* Function Name  : TP_GetAdXY
* Description    : 读取ADS7843 通道X+ 通道Y+的ADC值
* Input          : None
* Output         : None
* Return         : ADS7843返回 通道X+ 通道Y+的ADC值
* Attention		 : None
*******************************************************************************/
void TP_GetAdXY(int *x,int *y)
{
  int adx,ady;
  adx=Read_X();
  DelayUS(1);
  ady=Read_Y();
  *x=adx;
  *y=ady;
}

/*******************************************************************************
* Function Name  : TP_DrawPoint
* Description    : 在指定座标画点
* Input          : - Xpos: Row Coordinate
*                  - Ypos: Line Coordinate
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void TP_DrawPoint(uint16_t Xpos,uint16_t Ypos)
{
  Pixel(Xpos,Ypos,0xf800);     /* 中心点 */
  Pixel(Xpos+1,Ypos,0xf800);
  Pixel(Xpos,Ypos+1,0xf800);
  Pixel(Xpos+1,Ypos+1,0xf800);	
}	

/*******************************************************************************
* Function Name  : DrawCross
* Description    : 在指定座标画十字准星
* Input          : - Xpos: Row Coordinate
*                  - Ypos: Line Coordinate
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void DrawCross(uint16_t Xpos,uint16_t Ypos)
{
   	LCD_DrawUniLine(Xpos-12,Ypos,Xpos+13,Ypos);
  	LCD_DrawUniLine(Xpos,Ypos-12,Xpos,Ypos+13);
  	Pixel(Xpos+2,Ypos+2,BLUE);
  	Pixel(Xpos-2,Ypos+2,BLUE);
  	Pixel(Xpos+2,Ypos-2,BLUE);
  	Pixel(Xpos-2,Ypos-2,BLUE);
  	LCD_Circle(Xpos, Ypos, 6, 1, BLUE);

}	
	
/*******************************************************************************
* Function Name  : Read_Ads7846
* Description    : 得到滤波之后的X Y
* Input          : None
* Output         : None
* Return         : Coordinate结构体地址
* Attention		 : None
*******************************************************************************/
Coordinate *Read_Ads7846(void)
{
  static Coordinate  screen;
  int m0,m1,m2,TP_X[1],TP_Y[1],temp[3];
  uint8_t count=0;
  int buffer[2][9]={{0},{0}};  /* 坐标X和Y进行多次采样 */
  ADS7843_SPI_Init(); 		
  do					       /* 循环采样9次 */
  {		
    TP_GetAdXY(TP_X,TP_Y);
    buffer[0][count]=TP_X[0];
    buffer[1][count]=TP_Y[0];
    count++;
  }
  while(!TP_INT_IN&& count<9);  /* TP_INT_IN为触摸屏中断引脚,当用户点击触摸屏时TP_INT_IN会被置低 */
  if(count==9)   /* 成功采样9次,进行滤波 */
  {
    /* 为减少运算量,分别分3组取平均值 */
    temp[0]=(buffer[0][0]+buffer[0][1]+buffer[0][2])/3;
    temp[1]=(buffer[0][3]+buffer[0][4]+buffer[0][5])/3;
    temp[2]=(buffer[0][6]+buffer[0][7]+buffer[0][8])/3;
    /* 计算3组数据的差值 */
    m0=temp[0]-temp[1];
    m1=temp[1]-temp[2];
    m2=temp[2]-temp[0];
    /* 对上述差值取绝对值 */
    m0=m0>0?m0:(-m0);
    m1=m1>0?m1:(-m1);
    m2=m2>0?m2:(-m2);
    /* 判断绝对差值是否都超过差值门限，如果这3个绝对差值都超过门限值，则判定这次采样点为野点,抛弃采样点，差值门限取为2 */
    if( m0>THRESHOLD  &&  m1>THRESHOLD  &&  m2>THRESHOLD ) return 0;
    /* 计算它们的平均值，同时赋值给screen */
    if(m0<m1)
    {
      if(m2<m0)
	screen.x=(temp[0]+temp[2])/2;
      else
	screen.x=(temp[0]+temp[1])/2;	
    }
    else if(m2<m1)
      screen.x=(temp[0]+temp[2])/2;
    else
      screen.x=(temp[1]+temp[2])/2;

    /* 同上 计算Y的平均值 */
    temp[0]=(buffer[1][0]+buffer[1][1]+buffer[1][2])/3;
    temp[1]=(buffer[1][3]+buffer[1][4]+buffer[1][5])/3;
    temp[2]=(buffer[1][6]+buffer[1][7]+buffer[1][8])/3;
    m0=temp[0]-temp[1];
    m1=temp[1]-temp[2];
    m2=temp[2]-temp[0];
    m0=m0>0?m0:(-m0);
    m1=m1>0?m1:(-m1);
    m2=m2>0?m2:(-m2);
    if(m0>THRESHOLD&&m1>THRESHOLD&&m2>THRESHOLD) return 0;

    if(m0<m1)
    {
      if(m2<m0)
	screen.y=(temp[0]+temp[2])/2;
      else
	screen.y=(temp[0]+temp[1])/2;	
    }
    else if(m2<m1)
      screen.y=(temp[0]+temp[2])/2;
    else
      screen.y=(temp[1]+temp[2])/2;

    return &screen;
  }
  return 0;
}
	
/*******************************************************************************
* Function Name  : setCalibrationMatrix
* Description    : 计算出 K A B C D E F
* Input          : None
* Output         : None
* Return         : 返回1表示成功 0失败
* Attention		 : None
*******************************************************************************/
FunctionalState setCalibrationMatrix( Coordinate * displayPtr,Coordinate * screenPtr,Matrix * matrixPtr)
{
  FunctionalState retTHRESHOLD = ENABLE ;  /* K＝(X0－X2) (Y1－Y2)－(X1－X2) (Y0－Y2) */
  matrixPtr->Divider = ((screenPtr[0].x - screenPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) -
    ((screenPtr[1].x - screenPtr[2].x) * (screenPtr[0].y - screenPtr[2].y));
  if( matrixPtr->Divider == 0 )
  {
    retTHRESHOLD = DISABLE;
  }
  else
  {
    /* A＝((XD0－XD2) (Y1－Y2)－(XD1－XD2) (Y0－Y2))／K	*/
    matrixPtr->An = ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) -
      ((displayPtr[1].x - displayPtr[2].x) * (screenPtr[0].y - screenPtr[2].y));
    /* B＝((X0－X2) (XD1－XD2)－(XD0－XD2) (X1－X2))／K	*/
    matrixPtr->Bn = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].x - displayPtr[2].x)) -
      ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].x - screenPtr[2].x)) ;
    /* C＝(Y0(X2XD1－X1XD2)+Y1(X0XD2－X2XD0)+Y2(X1XD0－X0XD1))／K */
    matrixPtr->Cn = (screenPtr[2].x * displayPtr[1].x - screenPtr[1].x * displayPtr[2].x) * screenPtr[0].y +
      (screenPtr[0].x * displayPtr[2].x - screenPtr[2].x * displayPtr[0].x) * screenPtr[1].y +
	(screenPtr[1].x * displayPtr[0].x - screenPtr[0].x * displayPtr[1].x) * screenPtr[2].y ;
    /* D＝((YD0－YD2) (Y1－Y2)－(YD1－YD2) (Y0－Y2))／K	*/
    matrixPtr->Dn = ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].y - screenPtr[2].y)) -
      ((displayPtr[1].y - displayPtr[2].y) * (screenPtr[0].y - screenPtr[2].y)) ;
    /* E＝((X0－X2) (YD1－YD2)－(YD0－YD2) (X1－X2))／K	*/
    matrixPtr->En = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].y - displayPtr[2].y)) -
      ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].x - screenPtr[2].x)) ;
    /* F＝(Y0(X2YD1－X1YD2)+Y1(X0YD2－X2YD0)+Y2(X1YD0－X0YD1))／K */
    matrixPtr->Fn = (screenPtr[2].x * displayPtr[1].y - screenPtr[1].x * displayPtr[2].y) * screenPtr[0].y +
      (screenPtr[0].x * displayPtr[2].y - screenPtr[2].x * displayPtr[0].y) * screenPtr[1].y +
	(screenPtr[1].x * displayPtr[0].y - screenPtr[0].x * displayPtr[1].y) * screenPtr[2].y ;
  }  return( retTHRESHOLD ) ;
}

/*******************************************************************************
* Function Name  : getDisplayPoint
* Description    : 通过 K A B C D E F 把通道X Y的值转换为液晶屏坐标
* Input          : None
* Output         : None
* Return         : 返回1表示成功 0失败
* Attention		 : None
*******************************************************************************/
FunctionalState getDisplayPoint(Coordinate * displayPtr, Coordinate * screenPtr,
				Matrix * matrixPtr )
{
  FunctionalState retTHRESHOLD =ENABLE ;
  if( matrixPtr->Divider != 0 )  {
    /* XD = AX+BY+C */
    displayPtr->x = ( (matrixPtr->An * screenPtr->x) +
		     (matrixPtr->Bn * screenPtr->y) +
                       matrixPtr->Cn
		     ) / matrixPtr->Divider ;
    /* YD = DX+EY+F */
    displayPtr->y = ( (matrixPtr->Dn * screenPtr->x) +
		     (matrixPtr->En * screenPtr->y) +
                       matrixPtr->Fn
	             ) / matrixPtr->Divider ;
  }
  else
  {    retTHRESHOLD = DISABLE;
  }
  return(retTHRESHOLD);
}

/*******************************************************************************
* Function Name  : TouchPanel_Calibrate
* Description    : 校准触摸屏
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void TouchPanel_Calibrate(void)
{
  uint8_t i;
  Coordinate * Ptr;
  for(i=0;i<3;i++)
  {
   LCD_Clear(BLACK);
   //LCD_SetTextColor(BLUE);
   //LCD_SetBackColor(BLACK);
   //LCD_StringLine(10,10,"Touch crosshair to calibrate");
   GUI_Text(10, 10, "Touch crosshair to calibrate",BLUE,BLACK);
   Delay(0xFFFFFF);
   DrawCross(DisplaySample[i].x,DisplaySample[i].y);
   do
   {
   Ptr=Read_Ads7846();
   }
   while( Ptr == (void*)0 );
   ScreenSample[i].x= Ptr->x; ScreenSample[i].y= Ptr->y;
  }
  setCalibrationMatrix( &DisplaySample[0],&ScreenSample[0],&matrix ) ;  /* 送入值得到参数 */	
  LCD_Clear(BLACK);
}

/*******************************************************************************
* Function Name  : LCD_TouchRead( )
* Author				 : Anilandro
* Description    : Lectura de puntero sobre pantalla con versi髇 Portrait y Landscape
* Input          : None
* Output         : None
* Return         :
* Attention		 : None
*******************************************************************************/
uint8_t LCD_TouchRead(Coordinate * displayLCD){
  uint16_t px,py,x,y;
  int p,f;

  //char cadena[20];

  GetFormat();							 /*obtiene valor de formato de pantalla activo*/
  p=0;
  f=0;

  while(f<30){
    getDisplayPoint(&display, Read_Ads7846(), &matrix ) ;	 /*lee la posici髇 del puntero sobre la pantalla*/
    px=display.x;
    py=display.y;
    if((PMode2==0)&&(py<400)){x=px,y=py;p=1;break;}
    if((PMode2==1)&&(px<400)){x=px,y=py;p=1;break;}
    f++;
  }

  if(f>=30){p=0;x=400;y=400;}
  displayLCD->x = x;
  displayLCD->y =	y;

  return(p);
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

#endif


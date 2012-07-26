/**
  ******************************************************************************
  * @file    utility.c
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

/* Includes ------------------------------------------------------------------*/

#ifndef	__UTILITY_H_
#define	__UTILITY_H_

/* Includes ------------------------------------------------------------------*/
#include "utility.h"


/* Private typedef -----------------------------------------------------------*/
//GPIO_InitTypeDef  GPIO_InitStructure;
/* Private define ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
* @brief  Delay Function.
* @param  nCount:specifies the Delay time length.
* @retval None
*/
void delay_us(__IO uint32_t nCount) 	/* for 168 MHz @ Level3 Opt */
{
    __IO uint32_t i,j;
    i=nCount;
    while(i)
    {
        i--;
        j=55;
        while(j)j--;
    }
}

void delay_ms(__IO uint32_t nCount) 	/* for 168 MHz @ Level3 Opt */
{
    __IO uint32_t i, j;
    i=nCount;
    while(i)
    {
        i--;
        delay_us(998);
    }
}
/**
* @brief  Init HeartBeat LED
*
* @param
* @return none
*
* Heartbeat led indicate alive system.
*/
void HeartBeatInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  /* GPIOD Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}
/**
* @brief  Init HeartBeat LED
*
* @param
* @return none
*
* Heartbeat led indicate alive system.
*/
void HeartBeat_toggle(void)
{

    if(HeartBeatLed)
    {
        /* PD12/PD13 to be toggled */
        GPIO_SetBits(GPIOD, GPIO_Pin_12);
        GPIO_ResetBits(GPIOD, GPIO_Pin_13);
    }
    else
    {
        /* PD12/PD13 to be toggled */
        GPIO_ResetBits(GPIOD, GPIO_Pin_12);
        GPIO_SetBits(GPIOD, GPIO_Pin_13);
    }
}
void SystemStart(void)
{
    HeartBeatInit();
    BTInit();
    //RFM22BInit();
    LCD_Init();
    LCD_Clear(GREEN);
    TP_Init();

}

/**
* @brief  Init Ring Buffer Tx/Rx USART
*
* @param
* @return none
*
*
*/
void BufferInit(__IO FIFO_TypeDef *buffer)
{
  uint8_t i;
  i=0;
  buffer->count = 0;//0 bytes in buffer
  buffer->in = 0;//index points to start
  buffer->out = 0;//index points to start
  while(i<=USARTBUFFSIZE)
  {
    buffer->buff[i]=0;
    i++;

  }
}
/**
* @brief  Fill Ring Buffer Tx/Rx USART data
*
* @param
* @return none
*
*
*/
ErrorStatus BufferPut(__IO FIFO_TypeDef *buffer, uint8_t ch)
{
  if(buffer->count==USARTBUFFSIZE)
    return ERROR;//buffer full
  buffer->buff[buffer->in++]=ch;
  buffer->count++;
  if(buffer->in==USARTBUFFSIZE)
    buffer->in=0;//start from beginning
  return SUCCESS;
}
/**
* @brief  Get Ring Buffer Tx/Rx USART data
*
* @param
* @return none
*
*
*/
ErrorStatus BufferGet(__IO FIFO_TypeDef *buffer, uint8_t *ch)
{
  if(buffer->count==0)
    return ERROR;//buffer empty
  *ch=buffer->buff[buffer->out++];
  buffer->count--;
  if(buffer->out==USARTBUFFSIZE)
    buffer->out=0;//start from beginning
  return SUCCESS;
}
/**
* @brief  Evaluate Ring Buffer Tx/Rx USART
*
* @param
* @return none
*
*
*/
ErrorStatus BufferIsEmpty(__IO FIFO_TypeDef buffer)
{
  if(buffer.count==0)
    return SUCCESS;//buffer full
  return ERROR;
}
/**
* @brief  Init USART controller
*
* @param
* @return none
*
*
*/

/**
* @brief  Configures the nested vectored interrupt controller.
* @param  None
* @retval None
*/
void NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the USARTx Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
/**
* @brief
*
* @param
* @return none
*
*
*/
void Usart2Put(uint8_t ch)
{
  //put char to the buffer
  BufferPut(&U2Tx, ch);
  //enable Transmit Data Register empty interrupt
  USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
  USART_SendData(USART2, (uint8_t) ch);
  //Loop until the end of transmission
  while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
  {
  }
}
/**
* @brief
*
* @param
* @return none
*
*
*/
uint8_t Usart2Get(void)
{
  uint8_t ch;
  //check if buffer is empty
  while (BufferIsEmpty(U2Rx) ==SUCCESS);
  BufferGet(&U2Rx, &ch);
  return ch;
}


#endif


/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "utility.h"

/** @addtogroup STM32F4_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup IO_Toggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t HeartBeatLed;
uint32_t Tickcount;
__IO uint32_t TimingDelay;
FIFO_TypeDef U2Rx ,U2Tx;
uint8_t TextTx[30]="\rPrueba de BT \n\n";  /*Solo para test de la tx por la usart */
uint8_t *ptr; /*Solo para test de la tx por la usart */
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/
void NMI_Handler(void)
{
}


void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}


void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}


void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}


void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}


void DebugMon_Handler(void)
{
}


void PendSV_Handler(void)
{
}
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{

  TimingDelay_Decrement();
  Tickcount++;
  if(Tickcount>=1000)	/*Equivale a un segundo*/
  {
    HeartBeatLed^= 1;
    Tickcount=0;
    //test tx datos por usart a traves del buffer de tx
    ptr=TextTx;
    BufferInit(&U2Tx);
    while (*ptr!='\n'){
    	BufferPut(&U2Tx, *ptr++);  //solo para test de la tx por la usart)
	
   }
   USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
  }
}

/**
  * @brief  This function handles USARTx global interrupt request.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
  uint8_t ch;
  //if Receive interrupt
  if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
    ch=(uint8_t)USART_ReceiveData(USART2);
    //put char to the buffer
    BufferPut(&U2Rx, ch);
  }
  if (USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
  {

    if (BufferGet(&U2Tx, &ch) == SUCCESS)//if buffer read
    {
      USART_SendData(USART2, ch);
    }
    else//if buffer empty
    {
      //disable Transmit Data Register empty interrupt
      USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
    }
  }
}



void SDIO_IRQHandler(void)
{

}



void EXTI0_IRQHandler(void)
{

}

void TIM3_IRQHandler(void)
{
  
}
 void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  }		   
}
/**
******************************************************************************
* @file    util.h
* @author
* @version
* @date
* @brief
*
******************************************************************************
* @attention
*
******************************************************************************
*/
#ifndef _UTILITY_H
#define _UTILITY_H
//
//
//
//           /* This is myheader.h */
//           #ifndef _MYHEADER_
//           #define _MYHEADER_
//
//           /* All the rest of the header here */
//
//           #endif /* _MYHEADER_ */
//           /* End of myheader.h */
//
//    The preprocessor will access the "rest of the header" only the first time
//    the header#include <stm32f4xx.h>

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "F2M03GLA.h"
#include "RFM22B.h"
#include "SSD1289.h"
#include "touch_7846.h"
#include "bmp.h"
#include "delay.h"
#include "intrinsics.h"
#include "math.h"
#include "AsciiLib.h"

/* Exported constants --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define USARTBUFFSIZE	128

/* RFM22B SPI Interface pins  */
#define RFM22B_SPI                           SPI2
#define RFM22B_SPI_CLK                       RCC_APB1Periph_SPI2
#define RFM22B_SPI_CLK_INIT                  RCC_APB1PeriphClockCmd

#define RFM22B_SPI_SCK_PIN                   GPIO_Pin_13
#define RFM22B_SPI_SCK_GPIO_PORT             GPIOB
#define RFM22B_SPI_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOB
#define RFM22B_SPI_SCK_SOURCE                GPIO_PinSource13
#define RFM22B_SPI_SCK_AF                    GPIO_AF_SPI2

#define RFM22B_SPI_MISO_PIN                  GPIO_Pin_14
#define RFM22B_SPI_MISO_GPIO_PORT            GPIOB
#define RFM22B_SPI_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define RFM22B_SPI_MISO_SOURCE               GPIO_PinSource14
#define RFM22B_SPI_MISO_AF                   GPIO_AF_SPI2

#define RFM22B_SPI_MOSI_PIN                  GPIO_Pin_15
#define RFM22B_SPI_MOSI_GPIO_PORT            GPIOB
#define RFM22B_SPI_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define RFM22B_SPI_MOSI_SOURCE               GPIO_PinSource15
#define RFM22B_SPI_MOSI_AF                   GPIO_AF_SPI2

#define RFM22B_CS_PIN                        GPIO_Pin_12
#define RFM22B_CS_GPIO_PORT                  GPIOB
#define RFM22B_CS_GPIO_CLK                   RCC_AHB1Periph_GPIOB
#define RFM22B_SPI_CS_SOURCE                 GPIO_PinSource12
#define RFM22B_SPI_CS_AF                     GPIO_AF_SPI2

/* Private macro -------------------------------------------------------------*/
/* Select RFM22B: Chip Select pin low */
#define RFM22B_CS_LOW()       GPIO_ResetBits(RFM22B_CS_GPIO_PORT, RFM22B_CS_PIN)
/* Deselect RFM22B: Chip Select pin high */
#define RFM22B_CS_HIGH()      GPIO_SetBits(RFM22B_CS_GPIO_PORT, RFM22B_CS_PIN)
/* Private variables ---------------------------------------------------------*/
extern uint8_t HeartBeatLed;
extern  __IO uint32_t TimingDelay;

typedef struct{
  uint8_t in;
  uint8_t out;
  uint8_t count;
  uint8_t buff[USARTBUFFSIZE];
}FIFO_TypeDef;

extern FIFO_TypeDef U2Rx ,U2Tx;
/* Private function prototypes -----------------------------------------------*/
/*Begin miscellaneous functions prototypes*/
extern void delay_us(__IO uint32_t nCount);
extern void delay_ms(__IO uint32_t nCount);
void SystemStart(void);
void HeartBeat_toggle(void);
void HeartBeatInit(void);
void NVIC_Config(void);
/*End miscellaneous functions prototypes*/
void BufferInit(__IO FIFO_TypeDef *buffer);
ErrorStatus BufferPut(__IO FIFO_TypeDef *buffer, uint8_t ch);
ErrorStatus BufferGet(__IO FIFO_TypeDef *buffer, uint8_t *ch);
ErrorStatus BufferIsEmpty(__IO FIFO_TypeDef buffer);
void Usart2Put(uint8_t ch);
uint8_t Usart2Get(void);

#endif /* UTILITY_H_ */

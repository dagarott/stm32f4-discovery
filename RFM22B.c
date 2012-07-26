/**
  ******************************************************************************
  * @file     RFM22B.c
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

#ifndef	_RFM22B_H_
#define	_RFM22B_H_

#include "stm32f4xx.h"
#include "RFM22B.h"
#include "utility.h"

/**
  * @brief  Initializes the peripherals used by the SPI RFM22B driver.
  * @param  None
  * @retval None
  */
void RFM22B_LowLevel_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /*!< Enable the SPI clock */
  RFM22B_SPI_CLK_INIT(RFM22B_SPI_CLK, ENABLE);

  /*!< Enable GPIO clocks */
  RCC_AHB1PeriphClockCmd(RFM22B_SPI_SCK_GPIO_CLK | RFM22B_SPI_MISO_GPIO_CLK |
                         RFM22B_SPI_MOSI_GPIO_CLK | RFM22B_CS_GPIO_CLK, ENABLE);

  /*!< SPI pins configuration *************************************************/

  /*!< Connect SPI pins to AF5 */
  GPIO_PinAFConfig(RFM22B_SPI_SCK_GPIO_PORT, RFM22B_SPI_SCK_SOURCE,
		   RFM22B_SPI_SCK_AF);
  GPIO_PinAFConfig(RFM22B_SPI_MISO_GPIO_PORT, RFM22B_SPI_MISO_SOURCE,
		   RFM22B_SPI_MISO_AF);
  GPIO_PinAFConfig(RFM22B_SPI_MOSI_GPIO_PORT, RFM22B_SPI_MOSI_SOURCE,
		   RFM22B_SPI_MOSI_AF);


  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;

  /*!< SPI SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = RFM22B_SPI_SCK_PIN;
  GPIO_Init(RFM22B_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);
  /*!< SPI MOSI pin configuration */
  GPIO_InitStructure.GPIO_Pin =  RFM22B_SPI_MOSI_PIN;
  GPIO_Init(RFM22B_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);
  /*!< SPI MISO pin configuration */
  GPIO_InitStructure.GPIO_Pin =  RFM22B_SPI_MISO_PIN;
  GPIO_Init(RFM22B_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);
  /*!< Configure SFM22B Card CS pin in output pushpull mode ********************/
  GPIO_InitStructure.GPIO_Pin = RFM22B_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(RFM22B_CS_GPIO_PORT, &GPIO_InitStructure);
}


void RFM22BInit(void)
{
  SPI_InitTypeDef  SPI_InitStructure;

  RFM22B_LowLevel_Init();

  /*!< Deselect the RFM22B: Chip Select high */
  RFM22B_CS_HIGH();

  /*!< SPI configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;

  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(RFM22B_SPI, &SPI_InitStructure);

  /*!< Enable the RFM22B_SPI  */
  SPI_Cmd(RFM22B_SPI, ENABLE);
}
/**
  * @brief  DeInitializes the peripherals used by the SPI FLASH driver.
  * @param  None
  * @retval None
  */
void RFM22B_LowLevel_DeInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /*!< Disable the RFM22B_SPI  ************************************************/
  SPI_Cmd(RFM22B_SPI, DISABLE);

  /*!< DeInitializes the RFM22B_SPI *******************************************/
  SPI_I2S_DeInit(RFM22B_SPI);

  /*!< RFM22B_SPI Periph clock disable ****************************************/
  RFM22B_SPI_CLK_INIT(RFM22B_SPI_CLK, DISABLE);

  /*!< Configure all pins used by the SPI as input floating *******************/
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

  GPIO_InitStructure.GPIO_Pin = RFM22B_SPI_SCK_PIN;
  GPIO_Init(RFM22B_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = RFM22B_SPI_MISO_PIN;
  GPIO_Init(RFM22B_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = RFM22B_SPI_MOSI_PIN;
  GPIO_Init(RFM22B_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = RFM22B_CS_PIN;
  GPIO_Init(RFM22B_CS_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  DeInitializes the peripherals used by the SPI FLASH driver.
  * @param  None
  * @retval None
  */
void RFM22B_DeInit(void)
{
  RFM22B_LowLevel_DeInit();
}

#endif
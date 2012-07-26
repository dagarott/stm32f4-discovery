/**
******************************************************************************
* @file    F2M03GLA.h
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
#ifndef _RFM22B_H
#define _RFM22B_H
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

/* Private function prototypes -----------------------------------------------*/
/*Begin RFM22B functions prototypes*/
extern void RFM22BInit(void);
void RFM22B_LowLevel_Init(void);
void RFM22B_LowLevel_DeInit(void);
void RFM22B_DeInit(void);
/*End RFM22B functions prototypes*/

#endif
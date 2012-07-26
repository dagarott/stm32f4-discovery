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
#ifndef _F2M03GLA_H
#define _F2M03GLA_H
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

#define BTBAUDRATE	38400

/* Private function prototypes -----------------------------------------------*/
/*Begin Bluetooth functions prototypes*/
extern void BTInit(void);

/*End Bluetooth prototypes functions*/

#endif
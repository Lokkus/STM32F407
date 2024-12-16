#ifndef __USER_PERIPHERAL_INIT_H
#define __USER_PERIPHERAL_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Function Prototypes -------------------------------------------------------*/
void Error_Handler(void);
void peripheral_init(void);

UART_HandleTypeDef* UART_GetHandle(void);
DAC_HandleTypeDef* DAC_GetHandle(void);

#ifdef __cplusplus
}
#endif

#endif /* __USER_PERIPHERAL_INIT_H */

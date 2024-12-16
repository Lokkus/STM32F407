#ifndef __USER_DMA_INIT_H
#define __USER_DMA_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Function Prototypes -------------------------------------------------------*/
void DMA_init(void);
DMA_HandleTypeDef* DMA_USART_TX_GetHandle(void);
DMA_HandleTypeDef* DMA_USART_RX_GetHandle(void);

#ifdef __cplusplus
}
#endif

#endif /* __USER_DMA_INIT_H */

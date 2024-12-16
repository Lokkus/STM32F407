#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include "main.h"
#include <stdbool.h>
#define RX_BUFFER_SIZE 10

#ifdef __cplusplus
extern "C" {
#endif

typedef struct 
{
    uint8_t* data;
    size_t size;
    bool rx_buffer1_flag;
}DynamicBuffer;

void start_uart_dma(UART_HandleTypeDef *huart);
void UART_IDLECallback(UART_HandleTypeDef *huart);
DynamicBuffer* get_dynamic_buffer();


#ifdef __cplusplus
}
#endif

#endif

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
}DynamicBuffer;

void enable_getting_uart_data_dma();
void send_uart_data_dma(uint8_t* data);
void UART_IDLECallback(UART_HandleTypeDef *huart);
DynamicBuffer* get_dynamic_buffer();


#ifdef __cplusplus
}
#endif

#endif

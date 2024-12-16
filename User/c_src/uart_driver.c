#include "main.h"

/* Static receive buffer for UART DMA */
static uint8_t rx_buffer[RX_BUFFER_SIZE];

/* Dynamic buffer to store incoming UART data */
static DynamicBuffer dynamic_buffer = {NULL, 0, true};

/* Function Prototypes */
static void add_to_dynamic_buffer(uint8_t *data, size_t length);
static void free_dynamic_buffer(void) __attribute__((unused));

/**
 * @brief Add data to the dynamic buffer.
 *
 * This function appends the specified data to a dynamically allocated buffer.
 * If the buffer is empty, it initializes it with the provided data.
 *
 * @param data   Pointer to the data to be added.
 * @param length Length of the data to be added.
 */
static void add_to_dynamic_buffer(uint8_t *data, size_t length)
{
    if (length == 0) return;

    // Reallocate buffer to fit the new data
    uint8_t *new_data = realloc(dynamic_buffer.data, dynamic_buffer.size + length);
    if (new_data == NULL) {
        // Allocation error handling
        return;
    }

    // Copy new data to the end of the current buffer
    memcpy(new_data + dynamic_buffer.size, data, length);
    dynamic_buffer.data = new_data;
    dynamic_buffer.size += length;
}

/**
 * @brief Free the dynamic buffer.
 *
 * This function releases the memory used by the dynamic buffer and resets
 * its size to zero.
 */
static void free_dynamic_buffer(void)
{
    free(dynamic_buffer.data);
    dynamic_buffer.data = NULL;
    dynamic_buffer.size = 0;
}

/**
 * @brief Start UART reception in circular DMA mode.
 *
 * This function initializes the UART peripheral to start receiving data
 * in DMA mode, using a circular buffer.
 *
 * @param huart Pointer to the UART handle structure.
 */
void start_uart_dma(UART_HandleTypeDef *huart)
{
    // Start reception in circular DMA mode
    if (HAL_UART_Receive_DMA(huart, rx_buffer, RX_BUFFER_SIZE) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief UART IDLE line detection callback.
 *
 * This function is called when the UART peripheral detects an IDLE line,
 * indicating that the transmission has paused. It processes the received data
 * and appends it to the dynamic buffer.
 *
 * @param huart Pointer to the UART handle structure.
 */
void UART_IDLECallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        // Stop DMA temporarily to determine how many bytes have been received
        HAL_UART_DMAStop(huart);

        // Calculate the number of bytes received so far
        uint16_t bytes_left = __HAL_DMA_GET_COUNTER(DMA_USART_RX_GetHandle());
        uint16_t bytes_received = RX_BUFFER_SIZE - bytes_left;

        // Append the received data to the dynamic buffer
        add_to_dynamic_buffer(rx_buffer, bytes_received);

        // Optionally clear the buffer (not necessary)
        memset(rx_buffer, 0, RX_BUFFER_SIZE);

        // Restart DMA reception from the beginning
        HAL_UART_Receive_DMA(huart, rx_buffer, RX_BUFFER_SIZE);

        // Here you can process the data in the dynamic buffer, e.g., print:
        // printf("Received: %.*s\r\n", (int)dynamic_buffer.size, dynamic_buffer.data);

        // After processing, optionally free the dynamic buffer:
        // free_dynamic_buffer();
    }
}

/**
 * @brief UART receive complete callback.
 *
 * This function is called when a DMA transfer is complete. It appends
 * the entire buffer to the dynamic buffer and clears the receive buffer.
 *
 * @param huart Pointer to the UART handle structure.
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        // Append the entire buffer to the dynamic buffer
        add_to_dynamic_buffer(rx_buffer, RX_BUFFER_SIZE);
        // Clear the receive buffer
        memset(rx_buffer, 0, RX_BUFFER_SIZE);
    }
}

/**
 * @brief Get a pointer to the dynamic buffer.
 *
 * This function provides access to the dynamic buffer for external processing.
 *
 * @return Pointer to the DynamicBuffer structure.
 */
DynamicBuffer* get_dynamic_buffer()
{
    return &dynamic_buffer;
}

#include "user_dma_init.h"

static DMA_HandleTypeDef hdma_usart1_tx;
static DMA_HandleTypeDef hdma_usart1_rx;
static DMA_HandleTypeDef hdma_dac1;

static void DMA_UART_TX_Init(void);
static void DMA_UART_RX_Init(void);
static void DMA_DAC_Init(void);

static void DMA_UART_TX_Init(void)
{
    // DMA UART TX Init
    hdma_usart1_tx.Instance = DMA2_Stream7;
    hdma_usart1_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

    if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
    {
        Error_Handler();
    }

    __HAL_LINKDMA(UART_GetHandle(), hdmatx, hdma_usart1_tx);
}

static void DMA_UART_RX_Init(void)
{
    // Configure DMA for USART1 RX
    hdma_usart1_rx.Instance = DMA2_Stream5;
    hdma_usart1_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_CIRCULAR;  
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_usart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
        Error_Handler();
    }

    __HAL_LINKDMA(UART_GetHandle(), hdmarx, hdma_usart1_rx);
}

static void DMA_DAC_Init(void)
{
    /* Initialize DMA for DAC */
    __HAL_RCC_DMA1_CLK_ENABLE(); // Enable the clock for DMA1
    hdma_dac1.Instance = DMA1_Stream5;
    hdma_dac1.Init.Channel = DMA_CHANNEL_7; // DMA channel for DAC1
    hdma_dac1.Init.Direction = DMA_MEMORY_TO_PERIPH; // Memory to peripheral direction
    hdma_dac1.Init.PeriphInc = DMA_PINC_DISABLE; // Disable peripheral increment
    hdma_dac1.Init.MemInc = DMA_MINC_ENABLE; // Enable memory increment
    hdma_dac1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD; // Peripheral data alignment: Half-word
    hdma_dac1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD; // Memory data alignment: Half-word
    hdma_dac1.Init.Mode = DMA_CIRCULAR; // Circular mode
    hdma_dac1.Init.Priority = DMA_PRIORITY_LOW; // Low priority
    hdma_dac1.Init.FIFOMode = DMA_FIFOMODE_DISABLE; // Disable FIFO mode

    if (HAL_DMA_Init(&hdma_dac1) != HAL_OK)
    {
        Error_Handler();
    }

    // Link DMA to DAC
    __HAL_LINKDMA(DAC_GetHandle(), DMA_Handle1, hdma_dac1);
}

void DMA_init(void)
{
    __HAL_RCC_DMA2_CLK_ENABLE();
    DMA_UART_TX_Init();
    DMA_UART_RX_Init();
    DMA_DAC_Init();
}

/* Getters */
DMA_HandleTypeDef* DMA_USART_TX_GetHandle(void)
{
    return &hdma_usart1_tx;
}

DMA_HandleTypeDef* DMA_USART_RX_GetHandle(void)
{
    return &hdma_usart1_rx;
}
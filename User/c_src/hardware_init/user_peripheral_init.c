#include "user_peripheral_init.h"

static UART_HandleTypeDef huart1;
static TIM_HandleTypeDef htim;
static DAC_HandleTypeDef hdac;


static void SystemClock_Config(void);
static void UART_Init(void);
static void TIM1_BaseConfig(void);
static void TIM1_PWMConfig(void);
static void TIM6_BaseConfig(void);
static void TIM6_TriggerOutputConfig(void);
static void TIMs_Init(void);
static void NVIC_Init(void);
static void DAC_Init(void);

static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState       = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM       = 4;
    RCC_OscInitStruct.PLL.PLLN       = 168;
    RCC_OscInitStruct.PLL.PLLP       = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ       = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                       | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        Error_Handler();
    }
}

static void UART_Init(void)
{
    __HAL_RCC_USART1_CLK_ENABLE();

    // Init UART1
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits   = UART_STOPBITS_1;
    huart1.Init.Parity     = UART_PARITY_NONE;
    huart1.Init.Mode       = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }

    // Enable IDLE line interrupt
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
}

/**
 * @brief Initialize basic configuration for TIM1.
 */
static void TIM1_BaseConfig(void)
{
    __HAL_RCC_TIM1_CLK_ENABLE();

    htim.Instance = TIM1;
    htim.Init.Prescaler = 16799; // Clock divider: (168 MHz / (Prescaler + 1)) = 10 kHz
    htim.Init.CounterMode = TIM_COUNTERMODE_UP; // Counter counts up
    htim.Init.Period = 999; // Period: (10 kHz / (Period + 1)) = 5 Hz
    htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // No additional clock division
    htim.Init.RepetitionCounter = 0; // No repetition

    if (HAL_TIM_Base_Init(&htim) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief Configure PWM mode for TIM1 Channel 1.
 */
static void TIM1_PWMConfig(void)
{
    TIM_OC_InitTypeDef sConfigOC = {0};
    sConfigOC.OCMode = TIM_OCMODE_TOGGLE; // Toggle mode
    sConfigOC.Pulse = 500; // Half of the period (50% duty cycle)
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH; // Positive polarity
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE; // Fast mode disabled

    if (HAL_TIM_OC_ConfigChannel(&htim, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief Initialize basic configuration for TIM6.
 */
static void TIM6_BaseConfig(void)
{
    __HAL_RCC_TIM6_CLK_ENABLE();

    htim.Instance = TIM6;
    htim.Init.Prescaler = 14; // Clock: 168 MHz / (Prescaler + 1) = 12 MHz
    htim.Init.Period = 24;    // Period: (1 MHz / (Period + 1)) = 1 kHz
    htim.Init.CounterMode = TIM_COUNTERMODE_UP;

    if (HAL_TIM_Base_Init(&htim) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief Configure TIM6 as trigger output for DAC.
 */
static void TIM6_TriggerOutputConfig(void)
{
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

    if (HAL_TIMEx_MasterConfigSynchronization(&htim, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

static void TIMs_Init(void)
{
    TIM1_BaseConfig();
    TIM1_PWMConfig();
    TIM6_BaseConfig();
    TIM6_TriggerOutputConfig();
}

static void NVIC_Init(void)
{
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);

    /* Configure the NVIC for DMA */
    HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);          // Set priority for the DMA interrupt
    HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);                  // Enable the interrupt

    /* Configure the NVIC for DMA RX */
    HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 0, 1);          // Set priority for the DMA RX interrupt
    HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn);                  // Enable the RX interrupt
}

static void DAC_Init(void)
{
    // Enable the clock for the DAC peripheral
    __HAL_RCC_DAC_CLK_ENABLE();

    // Initialize the DAC instance
    hdac.Instance = DAC;
    if (HAL_DAC_Init(&hdac) != HAL_OK)
    {
        Error_Handler();
    }

    // Configure DAC channel
    DAC_ChannelConfTypeDef sConfig = {0};
    sConfig.DAC_Trigger = DAC_TRIGGER_T6_TRGO; // Trigger by TIM6
    sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE; // Enable output buffer
    if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
    {
        Error_Handler();
    }
}


void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}


void peripheral_init(void)
{
    HAL_Init();
    SystemClock_Config();
    GPIO_init();
    DMA_init();
    UART_Init();
    NVIC_Init();
    TIMs_Init();
    DAC_Init();
}


/* Getters */
UART_HandleTypeDef* UART_GetHandle(void)
{
    return &huart1;
}

DAC_HandleTypeDef* DAC_GetHandle(void)
{
    return &hdac;
}

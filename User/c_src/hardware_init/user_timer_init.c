#include "user_timer_init.h"

static TIM_HandleTypeDef htim1;
static TIM_HandleTypeDef htim6;

static void TIM1_BaseConfig(void);
static void TIM1_PWMConfig(void);
static void TIM6_BaseConfig(void);
static void TIM6_TriggerOutputConfig(void);

/**
 * @brief Initialize basic configuration for TIM1.
 */
static void TIM1_BaseConfig(void)
{
    __HAL_RCC_TIM1_CLK_ENABLE();

    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 16799; 
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 999; 
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; 
    htim1.Init.RepetitionCounter = 0; 

    if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
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

    if (HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
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

    htim6.Instance = TIM6;
    htim6.Init.Prescaler = 14; 
    htim6.Init.Period = 24;   
    htim6.Init.CounterMode = TIM_COUNTERMODE_UP;

    if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
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

    if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

void TIMs_Init(void)
{
    TIM1_BaseConfig();
    TIM1_PWMConfig();
    TIM6_BaseConfig();
    TIM6_TriggerOutputConfig();
}

/* Getters*/
TIM_HandleTypeDef* TIM1_GetHandle()
{
    return &htim1;
}

TIM_HandleTypeDef* TIM6_GetHandle()
{
    return &htim6;
}


#include "user_gpio_init.h"

static void GPIO_Init_GPIOD(void);
static void GPIO_Init_GPIOB_UART(void);
static void GPIO_Init_GPIOA_TIM1(void);
static void GPIO_Init_GPIOA_DAC1(void);

/* GPIO Initialization Functions */

/**
 * @brief Initialize GPIOD pins.
 */
static void GPIO_Init_GPIOD(void)
{
    __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_init = {0};
    GPIO_init.Pin   = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_init.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_init.Pull  = GPIO_PULLDOWN;
    GPIO_init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOD, &GPIO_init);
}

/**
 * @brief Initialize GPIOB pins for UART.
 */
static void GPIO_Init_GPIOB_UART(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_init = {0};
    GPIO_init.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_init.Mode = GPIO_MODE_AF_PP;
    GPIO_init.Pull = GPIO_NOPULL;
    GPIO_init.Alternate = GPIO_AF7_USART1;
    GPIO_init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_init);
}

/**
 * @brief Initialize GPIOA pin 8 for TIM1.
 */
static void GPIO_Init_GPIOA_TIM1(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_init = {0};
    GPIO_init.Pin = GPIO_PIN_8;
    GPIO_init.Mode = GPIO_MODE_AF_PP; // Alternate Function Push-Pull
    GPIO_init.Pull = GPIO_NOPULL;
    GPIO_init.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_init.Alternate = GPIO_AF1_TIM1; // Alternate Function TIM1
    HAL_GPIO_Init(GPIOA, &GPIO_init);
}

/**
 * @brief Initialize GPIOA pin 4 for DAC1.
 */
static void GPIO_Init_GPIOA_DAC1(void)
{
    GPIO_InitTypeDef GPIO_init = {0};
    GPIO_init.Pin = GPIO_PIN_4;
    GPIO_init.Mode = GPIO_MODE_ANALOG;
    GPIO_init.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_init);
}

void GPIO_init(void)
{
    GPIO_Init_GPIOD();
    GPIO_Init_GPIOB_UART();
    GPIO_Init_GPIOA_TIM1();
    GPIO_Init_GPIOA_DAC1();
}
#include "timer_driver.h"

void start_timer(TIM_HandleTypeDef *htim)
{
    if (HAL_TIM_Base_Start(htim) != HAL_OK)
    {
        Error_Handler();
    }
}

void stop_timer(TIM_HandleTypeDef *htim)
{
    if (HAL_TIM_Base_Stop(htim) != HAL_OK)
    {
        Error_Handler();
    }
}


void set_frequency(TIM_HandleTypeDef *htim, uint32_t freq, uint32_t sys_clock)
{
    if (freq == 0 || sys_clock == 0)
    {
        Error_Handler(); // Prevent division by zero
        return;
    }

    // Calculate prescaler and period
    uint32_t prescaler = (sys_clock / (freq * 65536)) - 1;
    uint32_t period = (sys_clock / (freq * (prescaler + 1))) - 1;

    // Set new values
    htim->Init.Prescaler = prescaler;
    htim->Init.Period = period;

    // Reinitialize the timer with new settings
    if (HAL_TIM_Base_Init(htim) != HAL_OK)
    {
        Error_Handler();
    }
}


void set_prescaler_and_period(TIM_HandleTypeDef *htim, uint32_t presc, uint32_t period)
{
    // Check if prescaler and period values are within valid ranges
    if (presc > 0xFFFF || period > 0xFFFF)
    {
        Error_Handler(); // Values exceed 16-bit limits
        return;
    }

    // Update prescaler and period in the timer handle
    htim->Init.Prescaler = presc;
    htim->Init.Period = period;

    // Reinitialize the timer with the new settings
    if (HAL_TIM_Base_Init(htim) != HAL_OK)
    {
        Error_Handler();
    }
}

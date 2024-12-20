#ifndef __TIMER_DRIVER_H
#define __TIMER_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Function Prototypes -------------------------------------------------------*/
void start_timer(TIM_HandleTypeDef *htim);
void stop_timer(TIM_HandleTypeDef *htim);
void set_frequency(TIM_HandleTypeDef *htim, uint32_t freq, uint32_t sys_clock);
void set_prescaler_and_period(TIM_HandleTypeDef *htim, uint32_t presc, uint32_t period);

#ifdef __cplusplus
}
#endif

#endif /* __TIMER_DRIVER_H */
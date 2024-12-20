#ifndef __USER_TIMER_INIT_H
#define __USER_TIMER_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Function Prototypes -------------------------------------------------------*/
TIM_HandleTypeDef* TIM1_GetHandle();
TIM_HandleTypeDef* TIM6_GetHandle();
void TIMs_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __USER_TIMER_INIT_H */
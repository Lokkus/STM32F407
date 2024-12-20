#include "timer_test.h"

static void check_timer_in_default_settings();

static void check_timer_in_default_settings()
{
    start_timer(TIM1_GetHandle());
    HAL_TIM_PWM_Start(TIM1_GetHandle(), TIM_CHANNEL_1);
}

void timer_tests()
{
    check_timer_in_default_settings();
}
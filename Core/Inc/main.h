/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "uart_test.h"
#include "timer_test.h"
#include "uart_driver.h"
#include "sine_generator.h"
#include "user_peripheral_init.h"
#include "user_dma_init.h"
#include "user_gpio_init.h"
#include "user_timer_init.h"
#include "timer_driver.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
}

void tests();

#endif

#endif /* __MAIN_H */

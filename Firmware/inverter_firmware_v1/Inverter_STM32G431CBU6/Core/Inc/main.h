/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BTN_0_Pin GPIO_PIN_13
#define BTN_0_GPIO_Port GPIOC
#define BTN_0_EXTI_IRQn EXTI15_10_IRQn
#define BTN_1_Pin GPIO_PIN_14
#define BTN_1_GPIO_Port GPIOC
#define BTN_1_EXTI_IRQn EXTI15_10_IRQn
#define BTN_2_Pin GPIO_PIN_15
#define BTN_2_GPIO_Port GPIOC
#define BTN_2_EXTI_IRQn EXTI15_10_IRQn
#define EXT_TX_Pin GPIO_PIN_2
#define EXT_TX_GPIO_Port GPIOA
#define EXT_RX_Pin GPIO_PIN_3
#define EXT_RX_GPIO_Port GPIOA
#define W_I_Sense_Pin GPIO_PIN_4
#define W_I_Sense_GPIO_Port GPIOA
#define W_V_Sense_Pin GPIO_PIN_5
#define W_V_Sense_GPIO_Port GPIOA
#define V_V_Sense_Pin GPIO_PIN_6
#define V_V_Sense_GPIO_Port GPIOA
#define V_I_Sense_Pin GPIO_PIN_7
#define V_I_Sense_GPIO_Port GPIOA
#define U_V_Sense_Pin GPIO_PIN_4
#define U_V_Sense_GPIO_Port GPIOC
#define U_I_Sense_Pin GPIO_PIN_2
#define U_I_Sense_GPIO_Port GPIOB
#define PWM_U_L_Pin GPIO_PIN_13
#define PWM_U_L_GPIO_Port GPIOB
#define PWM_V_L_Pin GPIO_PIN_14
#define PWM_V_L_GPIO_Port GPIOB
#define PWM_W_L_Pin GPIO_PIN_15
#define PWM_W_L_GPIO_Port GPIOB
#define PWM_U_H_Pin GPIO_PIN_8
#define PWM_U_H_GPIO_Port GPIOA
#define PWM_V_H_Pin GPIO_PIN_9
#define PWM_V_H_GPIO_Port GPIOA
#define PWM_W_H_Pin GPIO_PIN_10
#define PWM_W_H_GPIO_Port GPIOA
#define ENC_A_Pin GPIO_PIN_15
#define ENC_A_GPIO_Port GPIOA
#define VCP_TX_Pin GPIO_PIN_10
#define VCP_TX_GPIO_Port GPIOC
#define VCP_RX_Pin GPIO_PIN_11
#define VCP_RX_GPIO_Port GPIOC
#define PWM_NEO_Pin GPIO_PIN_4
#define PWM_NEO_GPIO_Port GPIOB
#define ENC_Z_Pin GPIO_PIN_6
#define ENC_Z_GPIO_Port GPIOB
#define ENC_B_Pin GPIO_PIN_8
#define ENC_B_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/*
 * motor.h
 *
 *  Created on: Mar 18, 2026
 *      Author: nicolas
 */

#ifndef INC_CONTROL_MOTOR_H_
#define INC_CONTROL_MOTOR_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "stm32g4xx_hal.h"
#include "user_interface/shell.h"

typedef struct h_motor_struct {
    TIM_HandleTypeDef* htim;

    uint32_t channels;

    float k;
    float vmax;
    float speed_max;

    float speed_target;
    float duty;
} h_motor_t;

extern h_motor_t h_motor1;

HAL_StatusTypeDef motorInit(h_motor_t *motor,
		TIM_HandleTypeDef* htim,
		uint32_t channels,
		float k, float vmax, float speed_max);
HAL_StatusTypeDef motorSetSpeed(h_motor_t *motor, float rpm);
HAL_StatusTypeDef motorSetDutyCycle(h_motor_t *motor, float duty);
HAL_StatusTypeDef motorUpdate(h_motor_t *motor);
HAL_StatusTypeDef motorStart(h_motor_t *motor);
HAL_StatusTypeDef motorStop(h_motor_t *motor);
HAL_StatusTypeDef motorPrint(h_motor_t *motor);
int motorShellSetDuty(h_shell_t* h_shell, int argc, char** argv);
int motorShellSetRPM(h_shell_t* h_shell, int argc, char** argv);
int motorShellStart(h_shell_t* h_shell, int argc, char** argv);
int motorShellStop(h_shell_t* h_shell, int argc, char** argv);
#endif /* INC_CONTROL_MOTOR_H_ */

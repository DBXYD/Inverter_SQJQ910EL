#include <stdio.h>
#include <stdlib.h>
#include "control/motor.h"
#include "main.h"
#include "tim.h"

h_motor_t h_motor1;

/* Init */
HAL_StatusTypeDef motorInit(h_motor_t *motor,
		TIM_HandleTypeDef* htim,
		uint32_t channels,
		float k, float vmax, float speed_max){

	motor->htim = htim;
	motor->channels = channels;
	motor->k = k;
	motor->vmax = vmax;
	motor->speed_max = speed_max;

	motor->speed_target = 0;
	motor->duty = 0.5+motor->speed_target/(2*motor->speed_max);

	shellAdd(&hshell1, "setMotorDuty", motorShellSetDuty, "Set instant duty cycle");
	shellAdd(&hshell1, "setMotorRPM", motorShellSetRPM, "Set instant RPM Target");
	shellAdd(&hshell1, "setMotorStart", motorShellStart, "Start PWM");
	shellAdd(&hshell1, "setMotorStop", motorShellStop, "Stop PWM");

	return HAL_OK;
}


/* RPM -> duty */
HAL_StatusTypeDef motorSetSpeed(h_motor_t *motor, float rpm){

	if(rpm > motor->speed_max) rpm = motor->speed_max;
	if(rpm < -motor->speed_max) rpm = -motor->speed_max;

	motor->speed_target = rpm;

	motor->duty = 0.5 + (0.5 * rpm / motor->speed_max);

	motorUpdate(motor);

	return HAL_OK;
}


HAL_StatusTypeDef motorSetDutyCycle(h_motor_t *motor, float duty){
	if(duty > 1) duty = 1;
	if(duty < 0) duty = 0;

	motor->duty = duty;

	motorUpdate(motor);

	return HAL_OK;
}

/* Application PWM */
HAL_StatusTypeDef motorUpdate(h_motor_t *motor){

	uint32_t ARR = __HAL_TIM_GET_AUTORELOAD(motor->htim);
	uint32_t pwm = (uint32_t)(motor->duty * ARR);

	if(pwm > ARR-2) pwm = ARR-2;
	if(pwm < 2) pwm = 2;
	__HAL_TIM_SET_COMPARE(motor->htim, TIM_CHANNEL_1, pwm);
	__HAL_TIM_SET_COMPARE(motor->htim, TIM_CHANNEL_2, ARR-pwm);

	return HAL_OK;
}

/* Start */
HAL_StatusTypeDef motorStart(h_motor_t *motor){

	motor->speed_target = 0;
	motor->duty = 0.5;

	motorUpdate(motor);

	HAL_TIM_PWM_Start(motor->htim, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(motor->htim, TIM_CHANNEL_1);

	HAL_TIM_PWM_Start(motor->htim, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(motor->htim, TIM_CHANNEL_2);

	return HAL_OK;
}

/* Stop */
HAL_StatusTypeDef motorStop(h_motor_t *motor){

	HAL_TIM_PWM_Stop(motor->htim, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Stop(motor->htim, TIM_CHANNEL_1);

	HAL_TIM_PWM_Stop(motor->htim, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Stop(motor->htim, TIM_CHANNEL_2);

	motor->speed_target = 0;
	motor->duty = 0.5;

	return HAL_OK;
}

/* Debug */
HAL_StatusTypeDef motorPrint(h_motor_t *motor){

	printf("Speed: %.2f rpm\tDuty: %.2f\r\n",
			motor->speed_target,
			motor->duty);

	return HAL_OK;
}

int motorShellSetDuty(h_shell_t* h_shell, int argc, char** argv){
	if(argc != 2) return 1;
	float duty = atof(argv[1]);
	if(duty < 0 || 1 < duty) return 1;

	motorSetSpeed(&h_motor1, (2*duty-1)*h_motor1.speed_max);

	return 0;
}

int motorShellSetRPM(h_shell_t* h_shell, int argc, char** argv){
	if(argc != 2) return 1;
	float rpm = atof(argv[1]);
	if(rpm < -h_motor1.speed_max || 1 > h_motor1.speed_max) return 1;

	motorSetSpeed(&h_motor1, rpm);

	return 0;
}

int motorShellStart(h_shell_t* h_shell, int argc, char** argv){
	if(argc != 1) return 1;
	motorStart(&h_motor1);
}

int motorShellStop(h_shell_t* h_shell, int argc, char** argv){
	if(argc != 1) return 1;
	motorStop(&h_motor1);
}

/*
 * app.c
 *
 *  Created on: Nov 11, 2025
 *      Author: nicolas
 */

#include "app.h"
#include "tim.h"
#include "usart.h"
#include "adc.h"
#include "state.h"
#include "user_interface/shell.h"
#include "user_interface/neopixel.h"
#include "user_interface/button.h"
#include "acquisition/analog.h"
#include "acquisition/encoder.h"
#include "control/motor.h"
#include "control/control.h"

static char shell_uart3_received_char;

static uint32_t loop_number = 0;
static StateInput_t state_input;

void init_device(void){

	state_input = INIT_START;

	// FSM Init
	FSM_Init();

	// Init SHELL
	hshell1.drv.transmit = shell_uart3_transmit;
	hshell1.drv.receive = shell_uart3_receive;
	shellInit(&hshell1);
	HAL_UART_Receive_IT(&huart3, (uint8_t *)&shell_uart3_received_char, 1);

	// Init LED
	h_ledstring1.htim = &htim3;
	h_ledstring1.tim_channel = TIM_CHANNEL_1;
	neoPixelInit(&h_ledstring1);

	// Init BUTTON
	h_buttons1[0].port = BTN_0_GPIO_Port;
	h_buttons1[0].pin  = BTN_0_Pin;
	h_buttons1[0].id   = 0;

	h_buttons1[1].port = BTN_1_GPIO_Port;
	h_buttons1[1].pin  = BTN_1_Pin;
	h_buttons1[1].id   = 1;

	h_buttons1[2].port = BTN_2_GPIO_Port;
	h_buttons1[2].pin  = BTN_2_Pin;
	h_buttons1[2].id   = 2;
	buttonInit(h_buttons1);

	// INIT INPUT
    h_analogInput1.gain[0] = 10.9; //19
    h_analogInput1.offset[0] = 0;
    h_analogInput1.unit[0] = 'V';
    h_analogInput1.channel[0] = 'U';

    h_analogInput1.gain[1] = 10.9; //19
    h_analogInput1.offset[1] = 0;
    h_analogInput1.unit[1] = 'V';
    h_analogInput1.channel[1] = 'V';

    h_analogInput1.gain[2] = 10.9; //19
    h_analogInput1.offset[2] = 0;
    h_analogInput1.unit[2] = 'V';
    h_analogInput1.channel[2] = 'W';

    // 50mV/A
    // Offset : 2.46V
    h_analogInput1.gain[3] = 20;
    h_analogInput1.offset[3] = 2.483;
    h_analogInput1.unit[3] = 'I';
    h_analogInput1.channel[3] = 'U';

    h_analogInput1.gain[4] = 20;
    h_analogInput1.offset[4] = 2.483;
    h_analogInput1.unit[4] = 'I';
    h_analogInput1.channel[4] = 'V';

    h_analogInput1.gain[5] = 20;
    h_analogInput1.offset[5] = 2.483;
    h_analogInput1.unit[5] = 'I';
    h_analogInput1.channel[5] = 'W';

    analogInputInit(&h_analogInput1, &hadc2, 6);

	// INIT ENCODER
	encoderInit(&h_encoder1, &htim8, -2.9296875, 0.01); // -1*(60*100)/(1024*2), -1 : inv A et B, 60 sec / min, 100Hz, 1024 tic / turn, 2 count / tic, 0.01 ms

	// MOTOR INIT
	motorInit(&h_motor1, &htim1, TIM_CHANNEL_1 | TIM_CHANNEL_2, 1, 24, 1500); // K, Vmax, speed_max

	// CONTROL INIT
	controlInit(&h_control1, &h_motor1, &h_encoder1, 0, 0, 0, 0, 0);

	// TICK INIT
	HAL_TIM_Base_Start_IT(&htim4);


	state_input = INIT_DONE;

}

uint8_t shell_uart3_transmit(const char *pData, uint16_t size)
{
	HAL_UART_Transmit(&huart3, (uint8_t *)pData, size, HAL_MAX_DELAY);
	return size;
}

uint8_t shell_uart3_receive(char *pData, uint16_t size)
{
	*pData = shell_uart3_received_char;
	return 1;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART3) {
		HAL_UART_Receive_IT(&huart3, (uint8_t *)&shell_uart3_received_char, 1);
		shellRun(&hshell1);
	}
}

void loop(){
	loop_number++;
	//	Every 10 ms

	encoderUpdate(&h_encoder1);
	FSM_Update(&h_control1);
	controlUpdate(&h_control1);
	controlUpdateMotorSpeed(&h_control1);

	// Every 100 ms
	if(loop_number%10 == 0){

	}

	//	Every 1 sec
	if(loop_number%100 == 0){

	}

}

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
#include "user_interface/shell.h"
#include "user_interface/neopixel.h"
#include "user_interface/button.h"
#include "acquisition/analog.h"
#include "acquisition/encoder.h"
#include "control/motor.h"

static char shell_uart3_received_char;

void init_device(void){
	// Initialisation user interface
	// SHELL
	hshell1.drv.transmit = shell_uart3_transmit;
	hshell1.drv.receive = shell_uart3_receive;
	shellInit(&hshell1);

	// LED
	h_ledstring1.htim = &htim3;
	h_ledstring1.tim_channel = TIM_CHANNEL_1;
	neoPixelInit(&h_ledstring1);

	// BUTTON
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

    HAL_UART_Receive_IT(&huart3, (uint8_t *)&shell_uart3_received_char, 1);

	// Initialisation motor control
	// MOTOR
	//	motor_init();
	// ASSERV (PID)
	//	asserv_init();
	//

    // Initialisation data acquistion
	// ANALOG INPUT
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

	// ENCODER INPUT
	encoderInit(&h_encoder1, &htim8, 2.9296875); // (60*100)/(1024*2) 60 sec / min, 100Hz, 1024 tic / turn, 2 count / tic

	// MOTOR INIT
	motorInit(&h_motor1, &htim1, TIM_CHANNEL_1 | TIM_CHANNEL_2, 1, 48, 3000);

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


}

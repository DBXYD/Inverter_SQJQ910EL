#include <stdio.h>
#include <stdlib.h>
#include "acquisition/analog.h"
#include "user_interface/shell.h"
#include "control/motor.h"
#include "adc.h"
#include "main.h"
#include "tim.h"

#define DIV_FREQ 400;
h_analoginput_t h_analogInput1;
uint32_t idx_div = 0;
float I_u = 0;

HAL_StatusTypeDef analogInputInit(h_analoginput_t *analogInput, ADC_HandleTypeDef* hadc, int nb_channels){
	analogInput->hadc = hadc;
	analogInput->nb_channels = nb_channels;
    HAL_ADC_Start_DMA(analogInput->hadc, (uint32_t*) analogInput->raw_values, (uint32_t) analogInput->nb_channels);
    return HAL_OK;
}

HAL_StatusTypeDef analogInputPrint(h_analoginput_t *analogInput)
{
	for(int idx = 0; idx < analogInput->nb_channels; idx++){
		analogInput->values[idx] = (((float)analogInput->raw_values[idx]*3.3/4096.0)-analogInput->offset[idx])*analogInput->gain[idx];
//		printf("%4d, %2.3f %c \t", analogInput->raw_values[idx], analogInput->values[idx], analogInput->unit[idx]);

	}
//	printf("U_u:%.3f,",analogInput->values[0]);
//	printf("U_v:%.3f,",analogInput->values[1]);
//	printf("I_u:%.3f,",analogInput->values[3]);
//	printf("I_v:%.3f",analogInput->values[4]);
//	printf("\r\n");
    return HAL_OK;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc){
	I_u = h_analogInput1.values[3];
	if(I_u < 0) I_u = -I_u;
	if(I_u > 10) printf("Warning !\r\n");
	if(I_u > 20){
		printf("Error !\r");
		motorStop(&h_motor1);
	}
	idx_div = (idx_div+1)%DIV_FREQ;
	if(idx_div==0) {
		analogInputPrint(&h_analogInput1);
	}
}

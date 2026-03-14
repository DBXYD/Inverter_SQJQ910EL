/*
 * analog.h
 *
 *  Created on: Feb 22, 2026
 *      Author: nicolas
 */

#ifndef INC_ACQUISITION_ANALOG_H_
#define INC_ACQUISITION_ANALOG_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "stm32g4xx_hal.h"
#include "user_interface/shell.h"

#define ADC_MAX_CHANNELS 6

typedef struct h_analog_input_struct{
    ADC_HandleTypeDef* hadc;
    uint8_t nb_channels;
    uint16_t raw_values[ADC_MAX_CHANNELS];
    float offset[ADC_MAX_CHANNELS];
    float gain[ADC_MAX_CHANNELS];
    float values[ADC_MAX_CHANNELS];
    char unit[ADC_MAX_CHANNELS];
    char channel[ADC_MAX_CHANNELS];
} h_analoginput_t;

extern h_analoginput_t h_analogInput1;

HAL_StatusTypeDef analogInputInit(h_analoginput_t *analogInput, ADC_HandleTypeDef* hadc, int nb_channels);
HAL_StatusTypeDef analogInputPrint(h_analoginput_t *analogInput);

#endif /* INC_ACQUISITION_ANALOG_H_ */

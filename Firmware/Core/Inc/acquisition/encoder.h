/*
 * encoder.h
 *
 *  Created on: Feb 22, 2026
 *      Author: nicolas
 */

#ifndef INC_ACQUISITION_ENCODER_H_
#define INC_ACQUISITION_ENCODER_H_

#include "main.h"
#include <stdint.h>

#define ADC_MAX_CHANNELS 16

typedef struct {
    ADC_HandleTypeDef* hadc;
    uint8_t nb_channels;
    uint32_t channels[ADC_MAX_CHANNELS]; // liste des ADC_CHANNEL_x
    uint16_t values[ADC_MAX_CHANNELS];   // valeurs lues
} h_adc_t;

/* Initialisation de l’ADC avec liste de canaux */
HAL_StatusTypeDef adcReaderInit(h_adc_t *adc, ADC_HandleTypeDef* hadc, uint8_t nb_channels, uint32_t *channel_list);

/* Lecture de tous les canaux et stockage dans adc->values */
HAL_StatusTypeDef adcReaderReadAll(h_adc_t *adc);

/* Affichage via printf */
void adcReaderPrint(h_adc_t *adc);

#endif
#endif /* INC_ACQUISITION_ENCODER_H_ */

/*
 * encoder.h
 *
 *  Created on: Feb 22, 2026
 *      Author: nicolas
 */

#ifndef INC_ACQUISITION_ENCODER_H_
#define INC_ACQUISITION_ENCODER_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "stm32g4xx_hal.h"
#include "user_interface/shell.h"

typedef struct h_encoder_struct {
    TIM_HandleTypeDef* htim;
    int32_t count;
    int32_t previous_count;
    int32_t delta_step;
    float velocity;
    float gain; // (60*100)/(1024*2) rpm
} h_encoder_t;

// Instance globale (optionnelle comme pour analog)
extern h_encoder_t h_encoder1;

/* Initialisation de l’encodeur */
HAL_StatusTypeDef encoderInit(h_encoder_t *encoder, TIM_HandleTypeDef* htim, float gain);

/* Mise à jour des mesures (à appeler périodiquement) */
HAL_StatusTypeDef encoderUpdate(h_encoder_t *encoder);

/* Affichage via shell */
HAL_StatusTypeDef encoderPrint(h_encoder_t *encoder);

/* Remise à zéro */
HAL_StatusTypeDef encoderReset(h_encoder_t *encoder);

int encoderGetSpeed(h_shell_t* h_shell, int argc, char** argv);

#endif /* INC_ACQUISITION_ENCODER_H_ */



//#include "main.h"
//#include <stdint.h>
//
//#define ADC_MAX_CHANNELS 16
//
//typedef struct {
//    ADC_HandleTypeDef* hadc;
//    uint8_t nb_channels;
//    uint32_t channels[ADC_MAX_CHANNELS]; // liste des ADC_CHANNEL_x
//    uint16_t values[ADC_MAX_CHANNELS];   // valeurs lues
//} h_adc_t;
//
///* Initialisation de l’ADC avec liste de canaux */
//HAL_StatusTypeDef adcReaderInit(h_adc_t *adc, ADC_HandleTypeDef* hadc, uint8_t nb_channels, uint32_t *channel_list);
//
///* Lecture de tous les canaux et stockage dans adc->values */
//HAL_StatusTypeDef adcReaderReadAll(h_adc_t *adc);
//
///* Affichage via printf */
//void adcReaderPrint(h_adc_t *adc);

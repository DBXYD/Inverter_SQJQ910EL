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

HAL_StatusTypeDef encoderInit(h_encoder_t *encoder, TIM_HandleTypeDef* htim, float gain, float delta_step);
HAL_StatusTypeDef encoderUpdate(h_encoder_t *encoder);
//HAL_StatusTypeDef encoderPrint(h_encoder_t *encoder);
HAL_StatusTypeDef encoderReset(h_encoder_t *encoder);
float encoderGetSpeed(h_encoder_t *encoder); // en RPM
int encoderShellGetSpeed(h_shell_t* h_shell, int argc, char** argv);

#endif /* INC_ACQUISITION_ENCODER_H_ */

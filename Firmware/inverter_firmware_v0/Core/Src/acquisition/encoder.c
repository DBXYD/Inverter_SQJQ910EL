/*
 * encoder.c
 *
 *  Created on: Feb 22, 2026
 *      Author: nicolas
 */
#include <stdio.h>
#include <stdlib.h>
#include "acquisition/encoder.h"
#include "user_interface/shell.h"
#include "main.h"
#include "tim.h"

h_encoder_t h_encoder1;

//typedef struct h_encoder_struct {
//    TIM_HandleTypeDef* htim;
//    int32_t count;
//    int32_t previous_count;
//    int32_t delta_step;
//    float velocity;
//    float gain; // (60*100)/(1024*2) rpm
//} h_encoder_t;


/* Initialisation */
HAL_StatusTypeDef encoderInit(h_encoder_t *encoder, TIM_HandleTypeDef* htim, float gain){
    encoder->htim = htim;
    encoder->gain = gain;

    encoder->count = 0;
    encoder->previous_count = 32768;
    encoder->velocity = 0.0f;
    encoder->delta_step = 0;

	shellAdd(&hshell1, "getSpeed", encoderGetSpeed, "Get instant speed");

    /* Démarrage du timer en mode encodeur */
    __HAL_TIM_SET_COUNTER(encoder->htim, encoder->previous_count);
    HAL_TIM_Encoder_Start(encoder->htim, TIM_CHANNEL_ALL);

    return HAL_OK;
}

/* Mise à jour (à appeler périodiquement) */
HAL_StatusTypeDef encoderUpdate(h_encoder_t *encoder){
    /* Calcul vitesse brute */
    encoder->count = (int32_t)__HAL_TIM_GET_COUNTER(encoder->htim);
    __HAL_TIM_SET_COUNTER(encoder->htim, encoder->previous_count);
	encoder->delta_step = encoder->count - encoder->previous_count;

    /* Conversion physique */
    encoder->velocity = encoder->delta_step * encoder->gain;

    return HAL_OK;
}

/* Affichage */
HAL_StatusTypeDef encoderPrint(h_encoder_t *encoder){
    encoderUpdate(encoder);

    printf("Pos: %6d \t Speed : %4.1f\r\n", encoder->count, encoder->velocity);
    return HAL_OK;
}

/* Reset */
HAL_StatusTypeDef encoderReset(h_encoder_t *encoder){
    __HAL_TIM_SET_COUNTER(encoder->htim, 0);

    encoder->count = 0;
    encoder->previous_count = 32768;
    encoder->velocity = 0.0f;
    encoder->delta_step = 0;

    return HAL_OK;
}

int encoderGetSpeed(h_shell_t* h_shell, int argc, char** argv){
	if(argc != 1) return 1;

//	encoderUpdate(&h_encoder1);
	printf("Speed : %6d rpm\r\n", h_encoder1.count);
	printf("Speed : %4.1f rpm\r\n", h_encoder1.velocity);

	return 0;
}




/* Callback périodique (ex: timer IT ou boucle) */
//void encoderCallback(void){
//    idx_div_encoder = (idx_div_encoder + 1) % DIV_FREQ;
//
//    if(idx_div_encoder == 0){
//        encoderPrint(&h_encoder1);
//    }
//}

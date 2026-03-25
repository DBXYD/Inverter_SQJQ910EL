/*
 * control.h
 *
 *  Created on: Mar 25, 2026
 *      Author: nicolas
 */

#ifndef SRC_CONTROL_CONTROL_H_
#define SRC_CONTROL_CONTROL_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "stm32g4xx_hal.h"
#include "control/motor.h"
#include "acquisition/encoder.h"
#include "user_interface/shell.h"

typedef enum{
    LOOP_OPENED,
	LOOP_CLOSED,
} loop_t;

typedef struct h_control_struct {
	h_motor_t* hmotor;
    h_encoder_t* hencoder;

    float target; // en RPM

    /* Coefficients du correcteur */
    float a0, a1, a2;
    float b0, b1, b2;

    /* États du système (mémoire) */
    float e_k, e_k_1, e_k_2; // Error en RPM
    float u_k, u_k_1, u_k_2; // Commande en duty cycle entre -1 et 1

    loop_t loop_status;
    uint8_t reset;

} h_control_t;

extern h_control_t h_control1;

void controlInit(h_control_t *hctrl, h_motor_t *hmotor, h_encoder_t *hencoder, float a1, float a2, float b0, float b1, float b2);
void controlSetLoop(h_control_t *hctrl, loop_t mode);
void controlUpdate(h_control_t *hctrl);
void controlUpdateMotorSpeed(h_control_t *hctrl);
int controlSetCoeff(h_control_t *hctrl, char* coeff, float value);
int controlShellSetMode(h_shell_t* h_shell, int argc, char** argv);
int controlShellSetCoeff(h_shell_t* h_shell, int argc, char** argv);


#endif /* SRC_CONTROL_CONTROL_H_ */

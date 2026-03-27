/*
 * control.c
 *
 *  Created on: Mar 25, 2026
 *      Author: nicolas
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "stm32g4xx_hal.h"
#include "user_interface/shell.h"
#include "control/control.h"
#include "control/motor.h"




h_control_t h_control1;
/**
 * @brief Initialise le contrôleur
 */
void controlInit(h_control_t *hctrl,
                  h_motor_t *hmotor,
                  h_encoder_t *hencoder,
                  float a1, float a2, float b0, float b1, float b2){
    hctrl->hmotor = hmotor;
    hctrl->hencoder = hencoder;
    hctrl->target = 0;

    hctrl->a0 = 1.0;
    hctrl->a1 = a1;
    hctrl->a2 = a2;
    hctrl->b0 = b0;
    hctrl->b1 = b1;
    hctrl->b2 = b2;

    hctrl->loop_status = LOOP_OPENED;

    hctrl->reset = 1;

    /* Reset mémoire */
    hctrl->e_k = 0;
    hctrl->e_k_1 = 0;
    hctrl->e_k_2 = 0;

    hctrl->u_k = 0;
    hctrl->u_k_1 = 0;
    hctrl->u_k_2 = 0;

	shellAdd(&hshell1, "setControlMode", controlShellSetMode, "Change open/close loop");
	shellAdd(&hshell1, "setControlCoeff", controlShellSetCoeff, "set a1, a2, b0, b1 and b2 coeff");
	shellAdd(&hshell1, "setControlResetCoeff", controlShellResetCoeff, "reset a1, a2, b0, b1 and b2 coeff");
	shellAdd(&hshell1, "setControlPwmEnable", controlShellSetPwnEnable, "activate pwm");
	shellAdd(&hshell1, "setControlPwmDisable", controlShellSetPwnDisable, "deactivate pwm");
	shellAdd(&hshell1, "setControlTarget", controlShellSetTarget, "set motor target speed");

}

/**
 * @brief Change le mode de boucle
 */
void controlSetLoop(h_control_t *hctrl, loop_t mode){
	hctrl->pwm_status = PWM_DISABLED;
    hctrl->loop_status = mode;
    hctrl->reset = 1;
}

/**
 * @brief Mise à jour du contrôleur
 * @param consigne (target)
 */
void controlUpdate(h_control_t *hctrl)
{
    /* Calcul erreur */
	hctrl->e_k = hctrl->target - encoderGetSpeed(hctrl->hencoder);

    if (hctrl->loop_status == LOOP_CLOSED)
    {
        /* Correcteur discret (forme générale IIR) */
    	hctrl->u_k =  hctrl->b0 * hctrl->e_k
    	            + hctrl->b1 * hctrl->e_k_1
    	            + hctrl->b2 * hctrl->e_k_2
    	            - hctrl->a1 * hctrl->u_k_1
    	            - hctrl->a2 * hctrl->u_k_2;
    }
    else if(hctrl->loop_status == LOOP_OPENED)
    {
        /* Boucle ouverte */
        hctrl->u_k = hctrl->target;
    }
    else if(hctrl->loop_status == LOOP_UNDEFINED){
    	/* Motor Off */
    	hctrl->u_k = 0;
    }

    /* Mise à jour mémoire */
    hctrl->e_k_2 = hctrl->e_k_1;
    hctrl->e_k_1 = hctrl->e_k;

    hctrl->u_k_2 = hctrl->u_k_1;
    hctrl->u_k_1 = hctrl->u_k;
}

void controlUpdateMotorSpeed(h_control_t *hctrl){
	if(hctrl->pwm_status == PWM_DISABLED || hctrl->loop_status == LOOP_UNDEFINED){
		motorStop(hctrl->hmotor);
	}
	else{
		motorSetDutyCycle(hctrl->hmotor, (1 + hctrl->u_k/hctrl->hmotor->speed_max)/2);
	}

}

int controlSetCoeff(h_control_t *hctrl, char* coeff, float value){
	hctrl->pwm_status = PWM_DISABLED;
	hctrl->target = 0;
	hctrl->hmotor->ccr = __HAL_TIM_GET_AUTORELOAD(hctrl->hmotor->htim)/2;
	hctrl->hmotor->ccr_target = __HAL_TIM_GET_AUTORELOAD(hctrl->hmotor->htim)/2;

	if(strcmp(coeff,"a1")==0){
		hctrl->a1 = value;
		return 0;
	}
	else if(strcmp(coeff,"a2")==0){
		hctrl->a2 = value;
		return 0;
	}
	else if(strcmp(coeff,"b0")==0){
		hctrl->b0 = value;
		return 0;
	}
	else if(strcmp(coeff,"b1")==0){
		hctrl->b1 = value;
		return 0;
	}
	else if(strcmp(coeff,"b2")==0){
		hctrl->b2 = value;
		return 0;
	}


	return 1;
}

int controlShellSetMode(h_shell_t* h_shell, int argc, char** argv){
	if(argc != 2) return 1;
	if(strcmp(argv[1],"close")==0){
		controlSetLoop(&h_control1,LOOP_CLOSED);
		return 0;
	}
	else if(strcmp(argv[1],"open")==0){
		controlSetLoop(&h_control1,LOOP_OPENED);
		return 0;
	}
	return 1;
}

int controlShellSetCoeff(h_shell_t* h_shell, int argc, char** argv){
	if(argc != 3) return 1;

	return controlSetCoeff(&h_control1, argv[1],atof(argv[2]));
}

int controlShellResetCoeff(h_shell_t* h_shell, int argc, char** argv){
	if(argc != 1) return 1;

	controlSetCoeff(&h_control1, "a1", 0);
	controlSetCoeff(&h_control1, "a2", 0);
	controlSetCoeff(&h_control1, "b0", 0);
	controlSetCoeff(&h_control1, "b1", 0);
	controlSetCoeff(&h_control1, "b2", 0);
}

int controlShellSetPwnEnable(h_shell_t* h_shell, int argc, char** argv){
	if(argc != 1) return 1;
	h_control1.pwm_status = PWM_ENABLED;
	return 0;
}

int controlShellSetPwnDisable(h_shell_t* h_shell, int argc, char** argv){
	if(argc != 1) return 1;
	h_control1.pwm_status = PWM_DISABLED;
	return 0;
}

int controlShellSetTarget(h_shell_t* h_shell, int argc, char** argv){
	if(argc != 2) return 1;
	h_control1.target = atof(argv[1]);
	return 0;
}

/*
 * state.c
 *
 *  Created on: Mar 25, 2026
 *      Author: nicolas
 */
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "state.h"

static State_t currentState;

// STATE_INIT
// STATE_IDLE
// STATE_LOOP_OPENED
// STATE_LOOP_CLOSED
// STATE_CURRENT_OVERLOAD
// STATE_ERROR

void FSM_Init(){
	currentState = STATE_INIT;
}

void FSM_Update(h_control_t *hctrl){
	switch (currentState)
	{
	case STATE_INIT:
	{
		// Get inputs

		// Next Step
		currentState = STATE_IDLE;
		hctrl->loop_status = LOOP_UNDEFINED;
		hctrl->pwm_status = PWM_DISABLED;

		// Set ouputs

		break;
	}

	case STATE_IDLE:
	{
		// Get inputs


		// Next Step
		if(hctrl->loop_status == LOOP_OPENED){
			currentState = STATE_LOOP_OPENED;

		} else if(hctrl->loop_status == LOOP_CLOSED){
			currentState = STATE_LOOP_CLOSED;

		} else{
			currentState = LOOP_UNDEFINED;

		}
		// Set ouputs

		break;
	}

	case STATE_LOOP_OPENED:
	{
		// Get inputs


		// Next Step
		if(hctrl->loop_status == LOOP_OPENED){
			currentState = STATE_LOOP_OPENED;

		} else if(hctrl->loop_status == LOOP_CLOSED){
			currentState = STATE_LOOP_CLOSED;

		} else{
			currentState = LOOP_UNDEFINED;

		}
		// Set ouputs
		if(hctrl->pwm_status == PWM_ENABLED){
			if(hctrl->hmotor->started == 0){
				motorStart(hctrl->hmotor);
				hctrl->hmotor->started = 1;
			}
		}
		else if(hctrl->pwm_status == PWM_ENABLED){
			motorStop(hctrl->hmotor);
		}
		break;
	}

	case STATE_LOOP_CLOSED:
	{
		// Get inputs


		// Next Step
		if(hctrl->loop_status == LOOP_OPENED){
			currentState = STATE_LOOP_OPENED;

		} else if(hctrl->loop_status == LOOP_CLOSED){
			if(hctrl->pwm_status == PWM_DISABLED){
				currentState = STATE_LOOP_CLOSED_CONFIG;
			}
			else if(hctrl->pwm_status == PWM_ENABLED){
				currentState = STATE_LOOP_CLOSED;
			}

		} else{
			currentState = LOOP_UNDEFINED;

		}

		// Set ouputs
		if(hctrl->pwm_status == PWM_ENABLED){
			motorStart(hctrl->hmotor);
		}
		else if(hctrl->pwm_status == PWM_ENABLED){
			motorStop(hctrl->hmotor);
		}

		break;
	}

	case STATE_LOOP_CLOSED_CONFIG:
	{
		// Get inputs


		// Next Step
		if(hctrl->loop_status == LOOP_OPENED){
			currentState = STATE_LOOP_OPENED;

		} else if(hctrl->loop_status == LOOP_CLOSED){
			if(hctrl->pwm_status == PWM_DISABLED){
				currentState = STATE_LOOP_CLOSED_CONFIG;
			}
			else if(hctrl->pwm_status == PWM_ENABLED){
				currentState = STATE_LOOP_CLOSED;
			}

		} else{
			currentState = LOOP_UNDEFINED;

		}

		// Set ouputs


		break;
	}

	case STATE_CURRENT_OVERLOAD:
	{
		// Get inputs


		// Next Step
		currentState = STATE_CURRENT_OVERLOAD;

		// Set ouputs
		hctrl->pwm_status = PWM_DISABLED;


		break;
	}

	case STATE_ERROR:
	{
		// Get inputs


		// Next Step
		currentState = STATE_ERROR;

		// Set ouputs
		hctrl->pwm_status = PWM_DISABLED;

		break;
	}

	default:
	{
		// Get inputs


		// Next Step
		currentState = STATE_IDLE;

		// Set ouputs
		hctrl->pwm_status = PWM_DISABLED;

		break;
	}
	}
}

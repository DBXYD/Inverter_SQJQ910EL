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

static State_t currentState = STATE_INIT;
// STATE_INIT
// STATE_IDLE
// STATE_LOOP_OPENED
// STATE_LOOP_CLOSED
// STATE_CURRENT_OVERLOAD
// STATE_ERROR

void FSM_Update(h_control_t *hctrl){
    switch (currentState)
    {
        case STATE_INIT:
        {
            currentState = STATE_IDLE;
            break;
        }

        case STATE_IDLE:
        {
        	if(hctrl->loop_status == LOOP_OPENED){

        	} else if(hctrl->loop_status == LOOP_CLOSED){

        	}
        	currentState = STATE_IDLE;
            break;
        }

        case STATE_LOOP_OPENED:
        {

        	currentState = STATE_LOOP_OPENED;
            break;
        }

        case STATE_LOOP_CLOSED:
        {

        	currentState = STATE_LOOP_CLOSED;
            break;
        }

        case STATE_CURRENT_OVERLOAD:
        {

        	currentState = STATE_CURRENT_OVERLOAD;
            break;
        }

        case STATE_ERROR:
        {

        	currentState = STATE_ERROR;
            break;
        }

        default:
        {
        	currentState = STATE_IDLE;
            break;
        }
    }
}

/*
 * state.h
 *
 *  Created on: Mar 25, 2026
 *      Author: nicolas
 */

#ifndef INC_STATE_H_
#define INC_STATE_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "stm32g4xx_hal.h"
#include "control/control.h"

typedef enum{
    STATE_INIT = 0,
    STATE_IDLE,
    STATE_LOOP_OPENED,
	STATE_LOOP_CLOSED,
	STATE_LOOP_CLOSED_CONFIG,
	STATE_CURRENT_OVERLOAD,
    STATE_ERROR
} State_t;

typedef enum{
    INIT_START = 0,
	INIT_DONE,
} StateInput_t;

void FSM_Init(void);
void FSM_Update(h_control_t *hctrl);

#endif /* INC_STATE_H_ */

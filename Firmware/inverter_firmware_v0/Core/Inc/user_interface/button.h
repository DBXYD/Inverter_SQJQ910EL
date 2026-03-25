/*
 * button.h
 *
 *  Created on: Feb 22, 2026
 */

#ifndef USER_INTERFACE_BUTTON_H_
#define USER_INTERFACE_BUTTON_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "stm32g4xx_hal.h"
#include "user_interface/shell.h"

#define BUTTON_COUNT 3

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
    uint8_t id;
} h_button_t;

typedef enum {
    BUTTON_EVENT_PRESSED = 0,
    BUTTON_EVENT_RELEASED
} button_event_t;

extern h_button_t h_buttons1[BUTTON_COUNT];

HAL_StatusTypeDef buttonInit(h_button_t *h_buttons);
button_event_t buttonRead(h_button_t *h_buttons, int id);

int shellButton(h_shell_t* h_shell, int argc, char** argv);

#endif /* USER_INTERFACE_BUTTON_H_ */

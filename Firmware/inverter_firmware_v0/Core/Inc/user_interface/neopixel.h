/*
 * neopixel.h
 *
 *  Created on: Apr 30, 2025
  */

#ifndef INC_NEOPIXEL_H_
#define INC_NEOPIXEL_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "stm32g4xx_hal.h"
#include "user_interface/shell.h"

#define NUMBER_OF_LEDS 1
#define TOTAL_DATA_LENGTH NUMBER_OF_LEDS * 24 + 1

typedef struct h_ledstring_struct {
	TIM_HandleTypeDef * htim;
	uint32_t tim_channel;
	uint16_t data[TOTAL_DATA_LENGTH];
} h_ledstring_t;

extern h_ledstring_t h_ledstring1;

//void neoPixelTask(void * unused);
HAL_StatusTypeDef neoPixelInit(h_ledstring_t *h_ledstring);
HAL_StatusTypeDef neoPixelRepaint(h_ledstring_t *h_ledstring);
HAL_StatusTypeDef neoPixelSetHexColor(h_ledstring_t *h_ledstring, uint16_t index, uint32_t hex);
HAL_StatusTypeDef neoPixelSetRGBColor(h_ledstring_t *h_ledstring, uint16_t index, uint8_t red, uint8_t green, uint8_t blue);
HAL_StatusTypeDef neoPixelSetHueColor(h_ledstring_t *h_ledstring, uint16_t index, uint16_t hue, uint8_t sat);

int shellLed(h_shell_t* h_shell, int argc, char** argv);


#endif /* INC_NEOPIXEL_H_ */

/*
 * neopixel.c
 *
 *  Created on: Apr 30, 2025
 */
#include "user_interface/shell.h"
#include "user_interface/neopixel.h"
#include <stdlib.h>
#include "main.h"

extern TIM_HandleTypeDef htim16;

h_ledstring_t h_ledstring1;

HAL_StatusTypeDef neoPixelInit(h_ledstring_t *h_ledstring) {
	for (int i = 0 ; i < TOTAL_DATA_LENGTH ; i++) {
		h_ledstring->data[i] = 6;
	}
	h_ledstring->data[TOTAL_DATA_LENGTH-1] = 0;

	shellAdd(&hshell1, "setLed", shellLed, "Set Led R G B on 0-255 value");

	for(int i = 0; i<3; i++){
		neoPixelSetRGBColor(h_ledstring, 0, 100, 0, 0);
		neoPixelRepaint(h_ledstring);
		HAL_Delay(50);
		neoPixelSetRGBColor(h_ledstring, 0, 0, 0, 0);
		neoPixelRepaint(h_ledstring);
		HAL_Delay(50);
	}

	return neoPixelRepaint(h_ledstring);
}

HAL_StatusTypeDef neoPixelRepaint(h_ledstring_t *h_ledstring) {
	return HAL_TIM_PWM_Start_DMA(h_ledstring->htim, h_ledstring->tim_channel, (uint32_t *) h_ledstring->data, TOTAL_DATA_LENGTH);
}

HAL_StatusTypeDef neoPixelSetHexColor(h_ledstring_t *h_ledstring, uint16_t index, uint32_t hex) {
	uint8_t red = (hex & 0xFF0000) >> 16;
	uint8_t green = (hex & 0x00FF00) >> 8;
	uint8_t blue = (hex & 0x0000FF);

	neoPixelSetRGBColor(h_ledstring, index, red, green, blue);
	return HAL_ERROR;
}

HAL_StatusTypeDef neoPixelSetRGBColor(h_ledstring_t *h_ledstring, uint16_t index, uint8_t red, uint8_t green, uint8_t blue) {
	// neopixel color encoding is GRB
	uint32_t hex = (green << 16) + (red << 8) + (blue);

	if (index < NUMBER_OF_LEDS) {
		for (int j = 0 ; j < 24 ; j++) {
			if (hex & (1<<j)) {
				h_ledstring->data[23-j + 24*index] = 13;
			}
			else {
				h_ledstring->data[23-j + 24*index] = 6;
			}
		}
	}
	return HAL_OK;
}

HAL_StatusTypeDef neoPixelSetHueColor(h_ledstring_t *h_ledstring, uint16_t index, uint16_t hue, uint8_t sat){
	uint8_t red = 0, green = 0, blue = 0;
	uint16_t segment = hue / 128;        // 0 à 5
	uint8_t offset = hue % 128;          // 0 à 255

	switch (segment) {
	case 0:
		red = 255-offset;
		green = offset;
		blue = 0;
		break; // Rouge → Jaune
	case 1:
		red = 128-offset;
		green = 128+offset;
		blue = 0;
		break; // Jaune → Vert
	case 2:
		red = 0;
		green = 255-offset;
		blue = offset;
		break; // Vert → Cyan
	case 3:
		red = 0;
		green = 128-offset;
		blue = 128+offset;
		break; // Cyan → Bleu
	case 4:
		red = offset;
		green = 0;
		blue = 255-offset;
		break; // Bleu → Magenta
	case 5:
		red = 128+offset;
		green = 0;
		blue = 128 - offset;
		break; // Magenta → Rouge
	}
	printf("Red : %3d, Blue : %3d, Green : %3d\r\n", red>>(8-sat), green>>(8-sat), blue>>(8-sat));
	return neoPixelSetRGBColor(h_ledstring, index, red>>(8-sat), green>>(8-sat), blue>>(8-sat));
}

int shellLed(h_shell_t* h_shell, int argc, char** argv){
	if(argc < 4) return 1;
	int r = (atoi(argv[1]) <= 0) ? 0 :
			(atoi(argv[1]) >= 255) ? 255 :
					atoi(argv[1]);
	int g = (atoi(argv[2]) <= 0) ? 0 :
			(atoi(argv[2]) >= 255) ? 255 :
					atoi(argv[2]);
	int b = (atoi(argv[3]) <= 0) ? 0 :
			(atoi(argv[3]) >= 255) ? 255 :
					atoi(argv[3]);
	neoPixelSetRGBColor(&h_ledstring1, 0, r, g, b);
	neoPixelRepaint(&h_ledstring1);

	return 0;
}

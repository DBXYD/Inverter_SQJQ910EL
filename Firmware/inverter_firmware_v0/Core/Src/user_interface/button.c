/*
 * button.c
 *
 *  Created on: Feb 22, 2026
 */

#include "user_interface/button.h"
#include "user_interface/shell.h"
#include "user_interface/neopixel.h"
#include <stdlib.h>
#include "main.h"

h_button_t h_buttons1[BUTTON_COUNT];

HAL_StatusTypeDef buttonInit(h_button_t *h_buttons)
{
    return HAL_OK;
}

void buttonEventCallback(uint8_t id, button_event_t event)
{
	printf("Button pressed %d\r\n", id);
	switch(id){
	case 0 :
		neoPixelSetRGBColor(&h_ledstring1, 0, 100, 0, 0);
		break;
	case 1 :
		neoPixelSetRGBColor(&h_ledstring1, 0, 0, 100, 0);;
		break;
	case 2 :
		neoPixelSetRGBColor(&h_ledstring1, 0, 0, 0, 100);;
		break;
	default :
		;
	}
	neoPixelRepaint(&h_ledstring1);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        if (GPIO_Pin == h_buttons1[i].pin)
        {
            GPIO_PinState state = HAL_GPIO_ReadPin(h_buttons1[i].port, h_buttons1[i].pin);

            if (state == GPIO_PIN_RESET)
            {
                buttonEventCallback(h_buttons1[i].id,
                                    BUTTON_EVENT_PRESSED);
            }
            else
            {
                buttonEventCallback(h_buttons1[i].id,
                                    BUTTON_EVENT_RELEASED);
            }
        }
    }
}




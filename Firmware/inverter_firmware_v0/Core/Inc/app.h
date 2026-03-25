/*
 * app.h
 *
 *  Created on: Nov 11, 2025
 *      Author: nicolas
 */

#ifndef INC_APP_H_
#define INC_APP_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "stm32g4xx_hal.h"

void init_device();
void loop();

uint8_t shell_uart3_transmit(const char *pData, uint16_t size);
uint8_t shell_uart3_receive(char *pData, uint16_t size);

#endif /* INC_APP_H_ */

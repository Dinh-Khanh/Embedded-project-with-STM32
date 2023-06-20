/*
 * delay.h
 *
 *  Created on: Jun 20, 2023
 *      Author: Admin
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#include "stm32f1xx_hal.h"
TIM_HandleTypeDef htim2;
void delay_init();
void delay(uint16_t time);

#endif /* INC_DELAY_H_ */

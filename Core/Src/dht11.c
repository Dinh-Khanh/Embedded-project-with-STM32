/*
 * dht11.c
 *
 *  Created on: Jun 20, 2023
 *      Author: Admin
 */
#include "dht11.h"
#include "delay.h"
void dht11_init(){
	delay_init();
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	/*Configure GPIO pin : PA5 */
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : PA6 */
	GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

uint8_t dht11_read(uint8_t *data) {
	//kich cho DHT11
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
	delay(20000);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
	//
	//		Cho chan A5 lên cao
	__HAL_TIM_SET_COUNTER(&htim2, 0);

	while (__HAL_TIM_GET_COUNTER(&htim2) < 10) {
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)) {
			break;
		}
	}
	u16Tim = __HAL_TIM_GET_COUNTER(&htim2);
	if (u16Tim >= 10) {
		return 0;
	}

	// cho chan A5 xuong thap -> DHT11 bat dau phản hồi
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	while (__HAL_TIM_GET_COUNTER(&htim2) < 45) {
		if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)) {
			break;
		}
	}
	u16Tim = __HAL_TIM_GET_COUNTER(&htim2);
	if (u16Tim >= 45 || u16Tim <= 5) {
		return 0;
	}
	// cho chan A5 len cao -> DHT11 dang keo xun thap
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	while (__HAL_TIM_GET_COUNTER(&htim2) < 90) {
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)) {
			break;
		}
	}
	u16Tim = __HAL_TIM_GET_COUNTER(&htim2);
	if (u16Tim >= 90 || u16Tim <= 70) {
		return 0;
	}
	// cho chan A5 xuong thap -> DHT11 dang keo len cao
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	while (__HAL_TIM_GET_COUNTER(&htim2) < 95) {
		if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)) {
			break;
		}
	}
	u16Tim = __HAL_TIM_GET_COUNTER(&htim2);
	if (u16Tim >= 95 || u16Tim <= 75) {
		return 0;
	}

	//------------Doc Data--------------
	//Nhan byte so 1
	for (i = 0; i < 8; i++) {
		__HAL_TIM_SET_COUNTER(&htim2, 0);
		while (__HAL_TIM_GET_COUNTER(&htim2) < 65) {
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)) {
				break;
			}
		}
		u16Tim = __HAL_TIM_GET_COUNTER(&htim2);
		if (u16Tim >= 65 || u16Tim <= 45) {
			return 0;
		}
		__HAL_TIM_SET_COUNTER(&htim2, 0);
		while (__HAL_TIM_GET_COUNTER(&htim2) < 80) {
			if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)) {
				break;
			}
		}
		u16Tim = __HAL_TIM_GET_COUNTER(&htim2);
		if (u16Tim >= 80 || u16Tim <= 10) {
			return 0;
		}
		u8Buff[0] <<= 1;
		if (u16Tim > 45) {
			//Nhan bit 1
			u8Buff[0] |= 1;
		} else {
			//nhan bit 0
			u8Buff[0] &= ~1;
		}
	}
	//Nhan byte so 2
	for (i = 0; i < 8; i++) {
		__HAL_TIM_SET_COUNTER(&htim2, 0);
		while (__HAL_TIM_GET_COUNTER(&htim2) < 65) {
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)) {
				break;
			}
		}
		u16Tim = __HAL_TIM_GET_COUNTER(&htim2);
		if (u16Tim >= 65 || u16Tim <= 45) {
			return 0;
		}
		__HAL_TIM_SET_COUNTER(&htim2, 0);
		while (__HAL_TIM_GET_COUNTER(&htim2) < 80) {
			if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)) {
				break;
			}
		}
		u16Tim = __HAL_TIM_GET_COUNTER(&htim2);
		if (u16Tim >= 80 || u16Tim <= 10) {
			return 0;
		}
		u8Buff[1] <<= 1;
		if (u16Tim > 45) {
			//Nhan bit 1
			u8Buff[1] |= 1;
		} else {
			//nhan bit 0
			u8Buff[1] &= ~1;
		}
	}
	//Nhan byte so 3
	for (i = 0; i < 8; i++) {
		__HAL_TIM_SET_COUNTER(&htim2, 0);
		while (__HAL_TIM_GET_COUNTER(&htim2) < 65) {
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)) {
				break;
			}
		}
		u16Tim = __HAL_TIM_GET_COUNTER(&htim2);
		if (u16Tim >= 65 || u16Tim <= 45) {
			return 0;
		}
		__HAL_TIM_SET_COUNTER(&htim2, 0);
		while (__HAL_TIM_GET_COUNTER(&htim2) < 80) {
			if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)) {
				break;
			}
		}
		u16Tim = __HAL_TIM_GET_COUNTER(&htim2);
		if (u16Tim >= 80 || u16Tim <= 10) {
			return 0;
		}
		u8Buff[2] <<= 1;
		if (u16Tim > 45) {
			//Nhan bit 1
			u8Buff[2] |= 1;
		} else {
			//nhan bit 0
			u8Buff[2] &= ~1;
		}
	}
	//Nhan byte so 4
	for (i = 0; i < 8; i++) {
		__HAL_TIM_SET_COUNTER(&htim2, 0);
		while (__HAL_TIM_GET_COUNTER(&htim2) < 65) {
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)) {
				break;
			}
		}
		u16Tim = __HAL_TIM_GET_COUNTER(&htim2);
		if (u16Tim >= 65 || u16Tim <= 45) {
			return 0;
		}
		__HAL_TIM_SET_COUNTER(&htim2, 0);
		while (__HAL_TIM_GET_COUNTER(&htim2) < 80) {
			if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)) {
				break;
			}
		}
		u16Tim = __HAL_TIM_GET_COUNTER(&htim2);
		if (u16Tim >= 80 || u16Tim <= 10) {
			return 0;
		}
		u8Buff[3] <<= 1;
		if (u16Tim > 45) {
			//Nhan bit 1
			u8Buff[3] |= 1;
		} else {
			//nhan bit 0
			u8Buff[3] &= ~1;
		}
	}
	//Nhan byte so 5
	for (i = 0; i < 8; i++) {
		__HAL_TIM_SET_COUNTER(&htim2, 0);
		while (__HAL_TIM_GET_COUNTER(&htim2) < 65) {
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)) {
				break;
			}
		}
		u16Tim = __HAL_TIM_GET_COUNTER(&htim2);
		if (u16Tim >= 65 || u16Tim <= 45) {
			return 0;
		}
		__HAL_TIM_SET_COUNTER(&htim2, 0);
		while (__HAL_TIM_GET_COUNTER(&htim2) < 80) {
			if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)) {
				break;
			}
		}
		u16Tim = __HAL_TIM_GET_COUNTER(&htim2);
		if (u16Tim >= 80 || u16Tim <= 10) {
			return 0;
		}
		u8Buff[4] <<= 1;
		if (u16Tim > 45) {
			//Nhan bit 1
			u8Buff[4] |= 1;
		} else {
			//nhan bit 0
			u8Buff[4] &= ~1;
		}
	}
	// Kiem  tra loi data bang byte so 5
	u8CheckSum = u8Buff[0] + u8Buff[1] + u8Buff[2] + u8Buff[3];
	if (u8CheckSum != u8Buff[4]) {
		return 0;
	} else {
		for (i=0; i<4; i++){
			data[i]=u8Buff[i];
		}
	}
	return 1;
}


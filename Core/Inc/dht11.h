/*
 * dht11.h
 *
 *  Created on: Jun 20, 2023
 *      Author: Admin
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#include "stm32f1xx_hal.h"
uint8_t i;
uint16_t u16Tim;
char u8Buff[5];
uint8_t u8CheckSum;
void dht11_init();
uint8_t dht11_read(uint8_t *data);
#endif /* INC_DHT11_H_ */

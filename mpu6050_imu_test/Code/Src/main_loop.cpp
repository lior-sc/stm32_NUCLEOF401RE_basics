/*
 * main_loop.cpp
 *
 *  Created on: Sep 5, 2023
 *      Author: lior
 */

#include "main.h"
#include "mpu6050.h"

extern I2C_HandleTypeDef hi2c1;

mpu6050 acc(hi2c1, GPIO_PIN_RESET);

void main_loop()
{
	while(1)
	{

	}
}




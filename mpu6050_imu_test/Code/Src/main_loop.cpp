/*
 * main_loop.cpp
 *
 *  Created on: Sep 5, 2023
 *      Author: lior
 */

#include "main.h"
#include "mpu6050.h"

extern I2C_HandleTypeDef hi2c1;

mpu6050 acc(GPIO_PIN_RESET,&hi2c1);

void main_loop()
{
	while(1)
	{
		acc.init();
		uint8_t imu_address = 0x00;
		acc.who_am_i(&imu_address);
		HAL_Delay(1000);
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	}
}




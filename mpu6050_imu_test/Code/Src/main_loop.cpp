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

// function decleration
void routine_n1();
void routine_n2();
void routine_n3();

void main_loop()
{
	// initialize accelerometer
	acc.init();
	while(1)
	{
//		routine_n1();
		routine_n2();
		routine_n3();
	}
}

void routine_n1()
{
	uint8_t imu_address = 0x00;
	acc.who_am_i(&imu_address);
	acc.set_sleep_enabled();
	acc.set_sleep_disabled();
	HAL_Delay(1000);
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}

void routine_n2()
{
	int16_t data[7] = {0};
	acc.get_data_raw(data);
	HAL_Delay(100);
	return;
}

void routine_n3()
{
	acc.get_data();
	HAL_Delay(100);
	return;
}

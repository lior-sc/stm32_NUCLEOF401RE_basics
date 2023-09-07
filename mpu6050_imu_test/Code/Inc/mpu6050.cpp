/*
 * mpu6050.cpp
 *
 *  Created on: Sep 5, 2023
 *      Author: lior
 */

#include "mpu6050.h"

extern UART_HandleTypeDef huart2;

mpu6050::mpu6050(I2C_HandleTypeDef hi2c_handle, uint8_t AD0_state = 0) {
	// set MPU6050 device address
	hi2c = hi2c_handle;

	if(AD0_state == GPIO_PIN_SET){
		MPU6050_ADDRESS = MPU6050_ADDRESS_AD0_HIGH;
	}
	else{
		MPU6050_ADDRESS = MPU6050_ADDRESS_AD0_LOW;
	}
}

mpu6050::~mpu6050() {
	// TODO Auto-generated destructor stub
}

bool mpu6050::init(){
//	HAL_I2C_Mem_Write(&hi2c, DevAddress, MemAddress, MemAddSize, pData, Size, Timeout)
	i2c_buf[0] = RA_WHO_AM_I;
	// write the required register address
	HAL_I2C_Master_Transmit(&hi2c, MPU6050_ADDRESS, i2c_buf, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c, MPU6050_ADDRESS, i2c_buf, 1, HAL_MAX_DELAY);


	return true;
}


/*
 * mpu6050.cpp
 *
 *  Created on: Sep 5, 2023
 *      Author: lior
 */

#include "mpu6050.h"
#include "string.h"

extern UART_HandleTypeDef huart2;
extern I2C_HandleTypeDef hi2c1;
//using namespace MPU6050_NAMESPACE;


mpu6050::mpu6050(uint8_t AD0_state = 0) {
	// set MPU6050 device address

	if(AD0_state == GPIO_PIN_SET){
		MPU6050_ADDRESS = MPU6050_ADDRESS_AD0_HIGH << 1;
	}
	else{
		MPU6050_ADDRESS = MPU6050_ADDRESS_AD0_LOW << 1;
	}
}

mpu6050::~mpu6050() {
	// TODO Auto-generated destructor stub
}

bool mpu6050::init(){
//	HAL_I2C_Mem_Write(&hi2c, DevAddress, MemAddress, MemAddSize, pData, Size, Timeout)
	uint8_t tx_buf = MPU6050_RA_WHO_AM_I;
	uint8_t rx_buf[3] = {0x00,0x00,0x00};

	// write the required register address
	HAL_I2C_Master_Transmit(&hi2c1, MPU6050_ADDRESS, &tx_buf, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c1, MPU6050_ADDRESS, rx_buf, 1, HAL_MAX_DELAY);

	return true;
}


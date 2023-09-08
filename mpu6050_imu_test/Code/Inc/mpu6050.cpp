/*
 * mpu6050.cpp
 *
 *  Created on: Sep 5, 2023
 *      Author: lior
 */

#include "mpu6050.h"
#include "string.h"

extern UART_HandleTypeDef huart2;
//extern I2C_HandleTypeDef hi2c1;



mpu6050::mpu6050(uint8_t AD0_state, I2C_HandleTypeDef *i2c_handle) {
	// set MPU6050 device address
	this->hi2c = i2c_handle;
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

HAL_StatusTypeDef mpu6050::init(){
	HAL_StatusTypeDef ret;
	uint8_t tx_buf = MPU6050_RA_WHO_AM_I;
	uint8_t rx_buf[3] = {0x00,0x00,0x00};


	// This segment deals with direct transmit-recieve interface
	ret = HAL_I2C_Master_Transmit(hi2c, MPU6050_ADDRESS, &tx_buf, 1, HAL_MAX_DELAY);
	ret = HAL_I2C_Master_Receive(hi2c, MPU6050_ADDRESS>>1, rx_buf, 1, HAL_MAX_DELAY);

	// This method is a shortened HAL version which includes the first transmission
	rx_buf[0] = 0x00;
	ret = HAL_I2C_Mem_Read(hi2c, MPU6050_ADDRESS, MPU6050_RA_WHO_AM_I, 1, rx_buf, 1, HAL_MAX_DELAY);


	return ret;
}

HAL_StatusTypeDef mpu6050::who_am_i(uint8_t *device_address)
{
	 /** @brief
	  * This register is used to verify the identity of the device.
	  * The contents of WHO_AM_I are the upper 6 bits of the MPU-60X0’s 7-bit I2C address.
	  * The least significant bit of the MPU-60X0’s I2C address is determined by the value of the AD0 pin.
	  * The value of the AD0 pin is not reflected in this register.
	  * The default value of the register is 0x68.
	  *
	  * NOTE:
	  * we use the HAL_I2C_Mem_Read() function to receive the same result
	  */

	HAL_StatusTypeDef ret;
	uint8_t tx_buf = MPU6050_RA_WHO_AM_I;
//	uint8_t rx_buf = 0x00;

	// Send the MPU6050 the address to be read.
	ret = HAL_I2C_Master_Transmit(hi2c, MPU6050_ADDRESS, &tx_buf, 1, HAL_MAX_DELAY);
	if(ret != HAL_OK)
	{
		return ret;
	}

	// Read 1 byte from the MPU6050. the MPU will send the content of the register
	ret = HAL_I2C_Master_Receive(hi2c, MPU6050_ADDRESS, device_address, 1, HAL_MAX_DELAY);

//	*device_address = rx_buf;

	return ret;
}




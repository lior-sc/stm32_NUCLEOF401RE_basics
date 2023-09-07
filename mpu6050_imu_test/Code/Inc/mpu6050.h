/*
 * mpu6050.h
 *
 *  Created on: Sep 5, 2023
 *      Author: lior
 *
 *      references:
 *      https://github.com/right13/STM32-Nucleo/blob/master/MPU6050
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include "stm32f4xx_hal.h"



class mpu6050 {
private:
	// Addresses & constants
	const uint8_t MPU6050_ADDRESS_AD0_LOW = 0x68;	// this is a 7 bit representation. the last bit is for read/write notation
	const uint8_t MPU6050_ADDRESS_AD0_HIGH = 0x69;  // this is a 7 bit representation. the last bit is for read/write notation
	const uint8_t RA_WHO_AM_I = 0x75;
	const uint8_t RA_USER_CTRL = 0x6A;
	const uint8_t RA_PWR_ADDR =  0x6B;


	// Variables
	uint8_t MPU6050_ADDRESS = MPU6050_ADDRESS_AD0_LOW << 1;	// shift address 1 bit left to leave space for read/write bit
	I2C_HandleTypeDef hi2c;
	uint8_t i2c_buf[12];

public:
	// Variables

	// Constructor, Destructor
	mpu6050(I2C_HandleTypeDef, uint8_t);
	virtual ~mpu6050();

	// Functions
	bool init();



};

#endif /* INC_MPU6050_H_ */

/*
 * mpu6050.h
 *
 *  Created on: Sep 5, 2023
 *      Author: lior
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include "stm32f4xx_hal.h"

class mpu6050 {
private:
	const uint8_t MPU6050_ADDRESS_AD0_LOW = 0b1101000;	// this is a 7 bit representation. the last bit is for read/write notation
	const uint8_t MPU6050_ADDRESS_AD0_HIGH = 0b1101001; // this is a 7 bit representation. the last bit is for read/write notation
	uint8_t MPU6050_ADDRESS = MPU6050_ADDRESS_AD0_LOW;

public:
	mpu6050(uint8_t);
	virtual ~mpu6050();
};

#endif /* INC_MPU6050_H_ */

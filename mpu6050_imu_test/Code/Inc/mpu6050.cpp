/*
 * mpu6050.cpp
 *
 *  Created on: Sep 5, 2023
 *      Author: lior
 */

#include "mpu6050.h"


mpu6050::mpu6050(uint8_t AD0_state) {
	// TODO Auto-generated constructor stub
	if(AD0_state == 0 || AD0_state == 1){
		MPU6050_ADDRESS | (AD0_state << 1);
	}
	else{
		// do nothing. AD0_state should be 0 or 1.
	}
}

mpu6050::~mpu6050() {
	// TODO Auto-generated destructor stub
}


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

//namespace MPU6050_IMU{

/******************************MPU6050 Addresses******************************/
const uint8_t MPU6050_ADDRESS_AD0_LOW = 0x68;	// this is a 7 bit representation. the last bit is for read/write notation
const uint8_t MPU6050_ADDRESS_AD0_HIGH = 0x69;  // this is a 7 bit representation. the last bit is for read/write notation


/******************************MPU6050 Registers******************************/
enum MPU6050_REG : uint8_t {
	MPU6050_RA_XG_OFFS_TC = 0x00,
	MPU6050_RA_YG_OFFS_TC,
	MPU6050_RA_ZG_OFFS_TC,
	MPU6050_RA_X_FINE_GAIN,
	MPU6050_RA_Y_FINE_GAIN,
	MPU6050_RA_Z_FINE_GAIN,
	MPU6050_RA_XA_OFFS_H,
	MPU6050_RA_XA_OFFS_L_TC,
	MPU6050_RA_YA_OFFS_H,
	MPU6050_RA_YA_OFFS_L_TC,
	MPU6050_RA_ZA_OFFS_H = 0x0A,
	MPU6050_RA_ZA_OFFS_L_TC,
	MPU6050_RA_SELF_TEST_X = 0x0D,
	MPU6050_RA_SELF_TEST_Y,
	MPU6050_RA_SELF_TEST_Z,
	MPU6050_RA_SELF_TEST_A = 0x10,
	MPU6050_RA_XG_OFFS_USRH = 0x13,
	MPU6050_RA_XG_OFFS_USRL,
	MPU6050_RA_YG_OFFS_USRH,
	MPU6050_RA_YG_OFFS_USRL,
	MPU6050_RA_ZG_OFFS_USRH,
	MPU6050_RA_ZG_OFFS_USRL,
	MPU6050_RA_SMPLRT_DIV,
	MPU6050_RA_CONFIG = 0x1A,
	MPU6050_RA_GYRO_CONFIG,
	MPU6050_RA_ACCEL_CONFIG,
	MPU6050_RA_FF_THR,
	MPU6050_RA_FF_DUR,
	MPU6050_RA_MOT_THR,
	MPU6050_RA_MOT_DUR = 0x20,
	MPU6050_RA_ZRMOT_THR,
	MPU6050_RA_ZRMOT_DUR,
	MPU6050_RA_FIFO_EN,
	MPU6050_RA_I2C_MST_CTRL,
	MPU6050_RA_I2C_SLV0_ADDR,
	MPU6050_RA_I2C_SLV0_REG,
	MPU6050_RA_I2C_SLV0_CTRL,
	MPU6050_RA_I2C_SLV1_ADDR,
	MPU6050_RA_I2C_SLV1_REG,
	MPU6050_RA_I2C_SLV1_CTRL 	= 0x2A,
	MPU6050_RA_I2C_SLV2_ADDR,
	MPU6050_RA_I2C_SLV2_REG,
	MPU6050_RA_I2C_SLV2_CTRL,
	MPU6050_RA_I2C_SLV3_ADDR,
	MPU6050_RA_I2C_SLV3_REG,
	MPU6050_RA_I2C_SLV3_CTRL 	= 0x30,
	MPU6050_RA_I2C_SLV4_ADDR,
	MPU6050_RA_I2C_SLV4_REG,
	MPU6050_RA_I2C_SLV4_DO,
	MPU6050_RA_I2C_SLV4_CTRL,
	MPU6050_RA_I2C_SLV4_DI,
	MPU6050_RA_I2C_MST_STATUS,
	MPU6050_RA_INT_PIN_CFG,
	MPU6050_RA_INT_ENABLE,
	MPU6050_RA_DMP_INT_STATUS,
	MPU6050_RA_INT_STATUS   	= 0x3A,
	MPU6050_RA_ACCEL_XOUT_H,
	MPU6050_RA_ACCEL_XOUT_L,
	MPU6050_RA_ACCEL_YOUT_H,
	MPU6050_RA_ACCEL_YOUT_L,
	MPU6050_RA_ACCEL_ZOUT_H,
	MPU6050_RA_ACCEL_ZOUT_L  	= 0x40,
	MPU6050_RA_TEMP_OUT_H,
	MPU6050_RA_TEMP_OUT_L,
	MPU6050_RA_GYRO_XOUT_H,
	MPU6050_RA_GYRO_XOUT_L,
	MPU6050_RA_GYRO_YOUT_H,
	MPU6050_RA_GYRO_YOUT_L,
	MPU6050_RA_GYRO_ZOUT_H,
	MPU6050_RA_GYRO_ZOUT_L,
	MPU6050_RA_EXT_SENS_DATA_00,
	MPU6050_RA_EXT_SENS_DATA_01 	= 0x4A,
	MPU6050_RA_EXT_SENS_DATA_02,
	MPU6050_RA_EXT_SENS_DATA_03,
	MPU6050_RA_EXT_SENS_DATA_04,
	MPU6050_RA_EXT_SENS_DATA_05,
	MPU6050_RA_EXT_SENS_DATA_06,
	MPU6050_RA_EXT_SENS_DATA_07  	= 0x50,
	MPU6050_RA_EXT_SENS_DATA_08,
	MPU6050_RA_EXT_SENS_DATA_09,
	MPU6050_RA_EXT_SENS_DATA_10,
	MPU6050_RA_EXT_SENS_DATA_11,
	MPU6050_RA_EXT_SENS_DATA_12,
	MPU6050_RA_EXT_SENS_DATA_13,
	MPU6050_RA_EXT_SENS_DATA_14,
	MPU6050_RA_EXT_SENS_DATA_15,
	MPU6050_RA_EXT_SENS_DATA_16,
	MPU6050_RA_EXT_SENS_DATA_17  	= 0x5A,
	MPU6050_RA_EXT_SENS_DATA_18,
	MPU6050_RA_EXT_SENS_DATA_19,
	MPU6050_RA_EXT_SENS_DATA_20,
	MPU6050_RA_EXT_SENS_DATA_21,
	MPU6050_RA_EXT_SENS_DATA_22,
	MPU6050_RA_EXT_SENS_DATA_23  	= 0x60,
	MPU6050_RA_MOT_DETECT_STATUS,
	MPU6050_RA_I2C_SLV0_DO       	= 0x63,
	MPU6050_RA_I2C_SLV1_DO,
	MPU6050_RA_I2C_SLV2_DO,
	MPU6050_RA_I2C_SLV3_DO,
	MPU6050_RA_I2C_MST_DELAY_CTRL,
	MPU6050_RA_SIGNAL_PATH_RESET,
	MPU6050_RA_MOT_DETECT_CTRL,
	MPU6050_RA_USER_CTRL    	= 0x6A,
	MPU6050_RA_PWR_MGMT_1,
	MPU6050_RA_PWR_MGMT_2,
	MPU6050_RA_BANK_SEL,
	MPU6050_RA_MEM_START_ADDR,
	MPU6050_RA_MEM_R_W,
	MPU6050_RA_DMP_CFG_1    	= 0x70,
	MPU6050_RA_DMP_CFG_2,
	MPU6050_RA_FIFO_COUNTH,
	MPU6050_RA_FIFO_COUNTL,
	MPU6050_RA_FIFO_R_W,
	MPU6050_RA_WHO_AM_I
};

enum CLK_SRC : uint8_t{
  MPU6050_CLOCK_INTERNAL = 0x00,
  MPU6050_CLOCK_PLL_XGYRO,
  MPU6050_CLOCK_PLL_YGYRO,
  MPU6050_CLOCK_PLL_ZGYRO,
  MPU6050_CLOCK_PLL_EXT32K,
  MPU6050_CLOCK_PLL_EXT19M,
  MPU6050_CLOCK_KEEP_RESET = 0x07,
};

enum GYRO_FS : uint8_t{
	MPU6050_GYRO_FS_250 = 0x00,
	MPU6050_GYRO_FS_500,
	MPU6050_GYRO_FS_1000,
	MPU6050_GYRO_FS_2000
};

enum ACCEL_FS : uint8_t{
    MPU6050_ACCEL_FS_2 = 0x00,
    MPU6050_ACCEL_FS_4,
    MPU6050_ACCEL_FS_8,
    MPU6050_ACCEL_FS_16,
};

class mpu6050 {
private:
	// Addresses & constants
	// Variables
	uint8_t MPU6050_ADDRESS = MPU6050_ADDRESS_AD0_LOW << 1;	// shift address 1 bit left to leave space for read/write bit
	I2C_HandleTypeDef *hi2c;		// This is a pointer to an I2C handle.

public:
	// Variables

	// Constructor, Destructor
	mpu6050(uint8_t, I2C_HandleTypeDef *);
	virtual ~mpu6050();

	// Functions
	HAL_StatusTypeDef init();
	HAL_StatusTypeDef who_am_i(uint8_t *);
	HAL_StatusTypeDef set_clock_source(uint8_t);
	HAL_StatusTypeDef set_fullscale_accel_range(uint8_t);
	HAL_StatusTypeDef set_fullscale_gyro_range(uint8_t);
	HAL_StatusTypeDef set_sleep_enabled();
	HAL_StatusTypeDef set_sleep_disabled();
}; // end of class


//} // end of namespace


#endif /* INC_MPU6050_H_ */

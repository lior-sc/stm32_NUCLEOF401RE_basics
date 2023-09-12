/*
 * mpu6050.cpp
 *
 *  Created on: Sep 5, 2023
 *      Author: lior
 */

#include "mpu6050.h"
#include "string.h"
#include "math.h"


extern UART_HandleTypeDef huart2;
//extern I2C_HandleTypeDef hi2c1;



mpu6050::mpu6050(uint8_t AD0_state, I2C_HandleTypeDef *i2c_handle)
{
	// set MPU6050 device address
	this->hi2c = i2c_handle;
	if(AD0_state == GPIO_PIN_SET){
		MPU6050_ADDRESS = MPU6050_ADDRESS_AD0_HIGH << 1;
	}
	else{
		MPU6050_ADDRESS = MPU6050_ADDRESS_AD0_LOW << 1;
	}

	/** @NOTE:
	 * Initialize MPU6050 outside of constructor using the init() method.
	 * It does not work well when the IMU is initialized inside the
	 * constructor. I don't know why.
	 */
}

mpu6050::~mpu6050() {
	// TODO Auto-generated destructor stub
}

/**************************Private Functions**************************/
HAL_StatusTypeDef mpu6050::set_accel_fullscale_range(uint8_t accel_fs_range)
{
	HAL_StatusTypeDef ret;
	uint8_t tx_buf[2] = {MPU6050_RA_ACCEL_CONFIG, 0x00};
	uint8_t rx_buf = 0x00;

	// make sure the input value is in the option range
	if(accel_fs_range > 3){
		// not in range. go back
		return HAL_ERROR;
	}

	// read current register status
	ret = HAL_I2C_Master_Transmit(hi2c, MPU6050_ADDRESS, tx_buf, 1, HAL_MAX_DELAY);
	ret = HAL_I2C_Master_Receive(hi2c, MPU6050_ADDRESS, &rx_buf, 1, HAL_MAX_DELAY);

	// build byte to write to register
	tx_buf[1] = rx_buf & 0b11100111;	// set the afs_sel bits to zero
	tx_buf[1] |= accel_fs_range << 3;		// input the accel_fs_range to the register

	// write back the value to the register
	ret = HAL_I2C_Master_Transmit(hi2c, MPU6050_ADDRESS, tx_buf, 2, HAL_MAX_DELAY);

	return ret;
}

HAL_StatusTypeDef mpu6050::set_gyro_fullscale_range(uint8_t gyro_fs_range)
{
	HAL_StatusTypeDef ret;
	uint8_t buf = 0x00;

	// make sure the input value is in the option range
	if(gyro_fs_range > 3){
		// not in range. go back
		return HAL_ERROR;
	}

	// read current register status
	ret = HAL_I2C_Mem_Read(hi2c, MPU6050_ADDRESS, MPU6050_RA_GYRO_CONFIG, 1, &buf, 1, HAL_MAX_DELAY);

	// build byte to write to register
	buf &= 0b11100111;			// set the afs_sel bits to zero
	buf |= gyro_fs_range << 3;	// set the FS_SEL bits to required value

	// write back the value to the register
	ret = HAL_I2C_Mem_Write(hi2c, MPU6050_ADDRESS, MPU6050_RA_GYRO_CONFIG, 1, &buf, 1, HAL_MAX_DELAY);

	return ret;
}


HAL_StatusTypeDef mpu6050::init(){
	/**@brief
	 * In this function we are going to initialize the MPU6050 according to our needs
	 */
	HAL_StatusTypeDef ret;
	uint8_t tx_buf[10] = {0};
//	uint8_t rx_buf[10] = {0};


	// set power management registers
	tx_buf[0] = MPU6050_RA_PWR_MGMT_1;
	tx_buf[1] = 0b00000001; //value written to PWR_MGMT_1 register
	tx_buf[2] = 0b00000000; //value written to PWR_MGMT_2 register

	ret = HAL_I2C_Master_Transmit(hi2c, MPU6050_ADDRESS, tx_buf, 3, HAL_MAX_DELAY);

	// set accelerometer fullscale range
	this->set_accel_fullscale_2G();
	this->set_gyro_fullscale_500();

	/*
	// read power management registers (for debug purposes)
	ret = HAL_I2C_Master_Transmit(hi2c, MPU6050_ADDRESS, tx_buf, 1, HAL_MAX_DELAY);
	ret = HAL_I2C_Master_Receive(hi2c, MPU6050_ADDRESS, rx_buf, 2, HAL_MAX_DELAY);
	*/
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

HAL_StatusTypeDef mpu6050::set_clock_source(uint8_t clock_source)
{
	HAL_StatusTypeDef ret;
	uint8_t tx_buf[2] = {MPU6050_RA_PWR_MGMT_1, 0x00};
	uint8_t rx_buf = 0x00;

	// Make sure

	// read current register status
	ret = HAL_I2C_Master_Transmit(hi2c, MPU6050_ADDRESS, tx_buf, 1, HAL_MAX_DELAY);
	ret = HAL_I2C_Master_Receive(hi2c, MPU6050_ADDRESS, &rx_buf, 1, HAL_MAX_DELAY);

	// Input desired clock source value
	tx_buf[1] = (rx_buf & 0b11111000) | (clock_source & 0b00000111);

	// write adjusted value to register
	ret = HAL_I2C_Master_Transmit(hi2c, MPU6050_ADDRESS, tx_buf, 2, HAL_MAX_DELAY);

	return ret;
}

HAL_StatusTypeDef mpu6050::set_sleep_enabled()
{
	HAL_StatusTypeDef ret;
	uint8_t buf[2] = {MPU6050_RA_PWR_MGMT_1, 0x00};

	// read current register status
	ret = HAL_I2C_Master_Transmit(hi2c, MPU6050_ADDRESS, buf, 1, HAL_MAX_DELAY);
	ret = HAL_I2C_Master_Receive(hi2c, MPU6050_ADDRESS, &buf[1], 1, HAL_MAX_DELAY);

	// build byte to write to register
	buf[1] |= 0b01000000;			// set the sleep bit to 1

	// write back the value to the register
	ret = HAL_I2C_Master_Transmit(hi2c, MPU6050_ADDRESS, buf, 2, HAL_MAX_DELAY);

	// for debug purposes
	buf[1] = 0x00;
	HAL_I2C_Mem_Read(hi2c, MPU6050_ADDRESS, buf[0], 1, &buf[1], 1, HAL_MAX_DELAY);

	return ret;
}

HAL_StatusTypeDef mpu6050::set_sleep_disabled()
{
	HAL_StatusTypeDef ret;
	uint8_t buf[2] = {MPU6050_RA_PWR_MGMT_1, 0x00};

	// read current register status
	ret = HAL_I2C_Master_Transmit(hi2c, MPU6050_ADDRESS, buf, 1, HAL_MAX_DELAY);
	ret = HAL_I2C_Master_Receive(hi2c, MPU6050_ADDRESS, &buf[1], 1, HAL_MAX_DELAY);

	// build byte to write to register
	buf[1] &= 0b10111111;			// set the sleep bit to 0

	// write back the value to the register
	ret = HAL_I2C_Master_Transmit(hi2c, MPU6050_ADDRESS, buf, 2, HAL_MAX_DELAY);

	// for debug purposes
	buf[1] = 0x00;
	HAL_I2C_Mem_Read(hi2c, MPU6050_ADDRESS, buf[0], 1, &buf[1], 1,HAL_MAX_DELAY);

	return ret;
}

HAL_StatusTypeDef mpu6050::set_accel_fullscale_2G()
{
	HAL_StatusTypeDef ret;
	ret = set_accel_fullscale_range(MPU6050_ACCEL_FS_2);
	if(ret == HAL_OK){
		this->ACC_FS_VAL = 2;
	}

	return ret;
}

HAL_StatusTypeDef mpu6050::set_accel_fullscale_4G()
{
	HAL_StatusTypeDef ret;
	ret = set_accel_fullscale_range(MPU6050_ACCEL_FS_4);
	if(ret == HAL_OK){
		this->ACC_FS_VAL = 4;
	}

	return ret;
}

HAL_StatusTypeDef mpu6050::set_accel_fullscale_8G()
{
	HAL_StatusTypeDef ret;
	ret = set_accel_fullscale_range(MPU6050_ACCEL_FS_8);
	if(ret == HAL_OK){
		this->ACC_FS_VAL = 8;
	}

	return ret;
}

HAL_StatusTypeDef mpu6050::set_accel_fullscale_16G()
{
	HAL_StatusTypeDef ret;
	ret = set_accel_fullscale_range(MPU6050_ACCEL_FS_16);
	if(ret == HAL_OK){
		this->ACC_FS_VAL = 16;
	}

	return ret;
}

HAL_StatusTypeDef mpu6050::set_gyro_fullscale_250()
{
	HAL_StatusTypeDef ret;
	ret = set_gyro_fullscale_range(MPU6050_GYRO_FS_250);
	if(ret == HAL_OK){
		this->GYRO_FS_VAL = 250; // deg/s
	}

	return ret;
}

HAL_StatusTypeDef mpu6050::set_gyro_fullscale_500()
{
	HAL_StatusTypeDef ret;
	ret = set_gyro_fullscale_range(MPU6050_GYRO_FS_500);
	if(ret == HAL_OK){
		this->GYRO_FS_VAL = 500; // deg/s
	}

	return ret;
}

HAL_StatusTypeDef mpu6050::set_gyro_fullscale_1000()
{
	HAL_StatusTypeDef ret;
	ret = set_gyro_fullscale_range(MPU6050_GYRO_FS_1000);
	if(ret == HAL_OK){
		this->GYRO_FS_VAL = 1000; // deg/s
	}

	return ret;
}

HAL_StatusTypeDef mpu6050::set_gyro_fullscale_2000()
{
	HAL_StatusTypeDef ret;
	ret = set_gyro_fullscale_range(MPU6050_GYRO_FS_2000);
	if(ret == HAL_OK){
		this->GYRO_FS_VAL = 2000; // deg/s
	}

	return ret;
}

/** @brief Get raw 6-axis motion sensor readings (accel/gyro).
 * Retrieves all currently available motion sensor values.
 * @param val 7 uint16_t buffer container for retrieved data
 */
HAL_StatusTypeDef mpu6050::get_data_raw(int16_t val[])
{
	/**
	 * This function fills the buffer with 7 uint16_t values:
	 * - 3DOF acceleration
	 * - 3DOF radial speed
	 * - 1 temperature value
	 */
	HAL_StatusTypeDef ret;
	uint8_t buf[14]={0};
	uint8_t accel_RA = MPU6050_RA_ACCEL_XOUT_H;

	// read values
	ret = HAL_I2C_Master_Transmit(hi2c, MPU6050_ADDRESS, &accel_RA, 1,HAL_MAX_DELAY);
	ret = HAL_I2C_Master_Receive(hi2c, MPU6050_ADDRESS, buf, 14, HAL_MAX_DELAY);

	if(ret == HAL_OK){
		for(int i=0; i<7; i++){
			val[i] = (((int16_t)buf[2*i]) << 8) | buf[2*i+1];
		}
	}

	return ret;
}

HAL_StatusTypeDef mpu6050::get_data()
{
	HAL_StatusTypeDef ret;
	int16_t buf[7];

	ret = get_data_raw(buf);

	if(ret != HAL_OK){
		return ret;
	}

	this->acc_x = ACC_FS_VAL * ((double)buf[0] / (double)INT16_MAX);
	this->acc_y = ACC_FS_VAL * ((double)buf[1] / (double)INT16_MAX);
	this->acc_z = ACC_FS_VAL * ((double)buf[2] / (double)INT16_MAX);
	this->temp = (double)buf[3] / 340 + 36.53;
	this->gyro_x = GYRO_FS_VAL * ((double)buf[4] / (double)INT16_MAX);
	this->gyro_y = GYRO_FS_VAL * ((double)buf[5] / (double)INT16_MAX);
	this->gyro_z = GYRO_FS_VAL * ((double)buf[6] / (double)INT16_MAX);

	return HAL_OK;
}

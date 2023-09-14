/*
 * lsm6ds3.cpp
 *
 *  Created on: Sep 14, 2023
 *      Author: Soltrex
 */

#include "lsm6ds3.h"


lsm6ds3::lsm6ds3(SPI_HandleTypeDef *spi_handle, GPIO_TypeDef *cs_pin_port, uint16_t cs_pin)
{
	// add device SPI handle, cs pin and cs port to constructed class.
	this->_hspi = spi_handle;
	this->_cs_port = cs_pin_port;
	this->_cs_pin = cs_pin;
}

lsm6ds3::~lsm6ds3()
{
	// TODO Auto-generated destructor stub
}

HAL_StatusTypeDef lsm6ds3::init()
{
	HAL_StatusTypeDef ret = HAL_OK;
	uint8_t tx_buf[5] = {0x00};

	tx_buf[0] = LSM6DS3_CTRL1_XL;
	tx_buf[1] = 0b10001101;		// Accelerometer config: 1.66Khz sampling freq, +-8G range, 200Hz anti-aliasing
	tx_buf[2] = 0b10000100;		// Gyro config: 1.66 khz sampling rate, 5000 dps range

	// set CS pin to high as default;
	HAL_GPIO_WritePin(_cs_port, _cs_pin, GPIO_PIN_SET);
	HAL_Delay(100);

	// write status to register via SPI
	HAL_GPIO_WritePin(_cs_port, _cs_pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(_hspi, tx_buf, 3, 100);
	HAL_SPI_Receive(_hspi, tx_buf, 2, 100);




	return ret;

}


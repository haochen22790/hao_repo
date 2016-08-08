/*
 * SPI.h
 *
 *  Created on: Aug 3, 2016
 *      Author: hao
 */

#ifndef SOURCES_SPI_H_
#define SOURCES_SPI_H_

#include <stdint.h>

//initializes KL25z for SPI communication
void SPI_init(void);

//send and receive a byte of data
uint8_t SPI_send_byte(uint8_t data);

#endif /* SOURCES_SPI_H_ */

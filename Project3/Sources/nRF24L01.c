/*
 * nRF24L01.c
 *
 *  Created on: Aug 3, 2016
 *      Author: hao
 */

#include "nRF24L01.h"
#include "SPI.h"
#include <stdint.h>
#include <MKL25Z4.h>

//write a value to a nRF24 register, using SPI
//the value should be a byte length
void nrf_write_register(uint8_t reg, uint8_t data)
{
	uint8_t dummy;

	//set SS low
	PTD_BASE_PTR->PCOR |= 1;
	//send a byte to indicate which register to write to
	dummy = SPI_send_byte(reg|RF24_W_REGISTER);
	//send data to the specified register
	dummy = SPI_send_byte(data);
	//set SS high
	PTD_BASE_PTR->PSOR |= 1;
}

//read from a nRF24 register, using SPI
//output is the read value, which is a byte in length
uint8_t nrf_read_register(uint8_t reg)
{
	uint8_t read;

	//set SS low
	PTD_BASE_PTR->PCOR |= 1;
	//send a byte to indicate which register to read from
	read =  SPI_send_byte(reg|RF24_W_REGISTER);
	//send a dummy value to initiate the read-back
	read = SPI_send_byte(0);
	//set SS high
	PTD_BASE_PTR->PSOR |= 1;

	return read;
}

//send a NOP command to read from STATUS register
uint8_t nrf_status(void)
{
	uint8_t read;

	//set SS low
	PTD_BASE_PTR->PCOR |= 1;
	//send a byte to indicate which register to read from
	read =  SPI_send_byte(RF24_NOP);
	//set SS high
	PTD_BASE_PTR->PSOR |= 1;

	return read;
}

//perform some predefined configuration for the nRF24
//also powers it up
void nrf_config(void)
{
	nrf_write_register(RF24_CONFIG, RF24_EN_CRC|RF24_CRCO|RF24_PWR_UP|RF24_PRIM_TX);
}

//flush the transmitter buffer to empty any existing data
void nrf_flush_tx_fifo(void)
{
	uint8_t dummy;

	//set SS low
	PTD_BASE_PTR->PCOR |= 1;
	//send command to flush the transmitter buffer
	dummy =  SPI_send_byte(RF24_FLUSH_TX);
	//set SS high
	PTD_BASE_PTR->PSOR |= 1;
}

//turn on the transmitter to perform wireless data transmission
void nrf_transmit_data(uint8_t data)
{
	uint32_t i = 0;

	//flush the transmit buffer
	nrf_flush_tx_fifo();
	//put one byte of data in the transmit buffer
	nrf_write_register(RF24_R_RX_PAYLOAD, data);
	//turn on the transmitter by setting CE high
	PTD_BASE_PTR->PSOR |= 8;

	//wait a bit
	while(i<1000)
	{
		i++;
	}

	//turn off the transmitter by setting CE low
	PTD_BASE_PTR->PCOR |= 8;
}

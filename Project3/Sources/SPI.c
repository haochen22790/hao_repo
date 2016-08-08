/*
 * SPI.c
 *
 *  Created on: Aug 3, 2016
 *      Author: hao
 */

#include <stdint.h>
#include <MKL25Z4.h>
#include "SPI.h"

//initializes KL25z for SPI communication
void SPI_init(void)
{
	//enable clock for port D, which will function as SPI pins
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
	//port D pin 1 is SCK
	PORTD_PCR1 = PORT_PCR_MUX(2);
	//port D pin 2 is MOSI
	PORTD_PCR2 = PORT_PCR_MUX(2);
	//port D pin 0 is SS (set to GPIO mode)
	PORTD_PCR0 = PORT_PCR_MUX(1);
	//set port D pin 0 to output mode
	PTD_BASE_PTR->PDDR |= 1;
	//set SS high
	PTD_BASE_PTR->PSOR |= 1;
	//port D pin 3 is nRF24 CE (set to GPIO mode)
	PORTD_PCR3 = PORT_PCR_MUX(1);
	//set port D pin 3 to output mode
	PTD_BASE_PTR->PDDR |= 8;

	//enable clock for SPI module
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;
	//set to SPI master
	SPI0_C1 = SPI_C1_MSTR_MASK;
	//set baud rate to 1MHz
	SPI0_BR = SPI_BR_SPPR(6);
	//enable SPI0
	SPI0_C1 |= SPI_C1_SPE_MASK;
}

//send and receive a byte of data
uint8_t SPI_send_byte(uint8_t data)
{
	volatile char read;

	//wait until it is ready to transmit
	while(!(SPI0_S & SPI_S_SPTEF_MASK)){}
	//send one byte of data
	SPI0_D = data;
	//wait until transmission is complete
	while(!(SPI0_S & SPI_S_SPRF_MASK)){}
	//read the received data byte
	read = SPI0_D;
}

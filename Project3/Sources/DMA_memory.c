/*
 * DMA_memory.c
 *
 *  Created on: Jul 24, 2016
 *      Author: hao
 */

#include "DMA_memory.h"
#include <stdint.h>
#include <MKL25Z4.h>

void DMA_init()
{
	//not sure if needed
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	//enable clock to DMA
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;
	//start in disabled state
	DMAMUX0_BASE_PTR->CHCFG[0] = 0x00u;
	//enable DMA channel 0
	DMAMUX0_BASE_PTR->CHCFG[0] = 0x80u;
	//source and destination size: <00> is 32-bit, <01> is 8-bit
	DMA_DCR0 = DMA_DCR_SSIZE(1)|DMA_DCR_DSIZE(1);
}

int8_t DMA_memmove(uint8_t *src, uint8_t *dst, uint32_t length)
{
	//load source address
	DMA_SAR0 = (uint32_t)src;
	//load destination address
	DMA_DAR0 = (uint32_t)dst;
	//load byte count, this also clears "done" bit
	DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length);
	//start DMA
	DMA_DCR0 |= (1<<DMA_DCR_START_SHIFT)&DMA_DCR_START_MASK;

	//wait until DMA is finished
	volatile uint32_t DMA_done = 0;
	while(DMA_done==0)
	{
		DMA_done = (DMA_DSR_BCR0&DMA_DSR_BCR_DONE_MASK)>>DMA_DSR_BCR_DONE_SHIFT;
	}

	//clear "done" bit
	DMA_DSR_BCR0 &= ~((1<<DMA_DSR_BCR_DONE_SHIFT)&DMA_DSR_BCR_DONE_MASK);

	return 0;
}

int8_t DMA_memmove_32bit(uint8_t *src, uint8_t *dst, uint32_t length)
{
	uint32_t byteCount1;
	uint32_t byteCount2;
	//calculate byte count to be transferred in 8-bit chunks
	byteCount2 = length%4;
	//calculate byte count to be transferred in 32-bit chunks
	byteCount1 = length - byteCount2;

	//set source and destination size to 32-bit, this also clears start bit
	DMA_DCR0 = DMA_DCR_SSIZE(0)|DMA_DCR_DSIZE(0);
	//load source address
	DMA_SAR0 = (uint32_t)src;
	//load destination address
	DMA_DAR0 = (uint32_t)dst;
	//load byte count, this also clears "done" bit
	DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(byteCount1);
	//start DMA
	DMA_DCR0 |= (1<<DMA_DCR_START_SHIFT)&DMA_DCR_START_MASK;

	//wait until DMA is finished
	volatile uint32_t DMA_done = 0;
	while(DMA_done==0)
	{
		DMA_done = (DMA_DSR_BCR0&DMA_DSR_BCR_DONE_MASK)>>DMA_DSR_BCR_DONE_SHIFT;
	}

	//clear "done" bit
	DMA_DSR_BCR0 &= ~((1<<DMA_DSR_BCR_DONE_SHIFT)&DMA_DSR_BCR_DONE_MASK);

	//set source and destination size to 8-bit, this also clears start bit
	DMA_DCR0 = DMA_DCR_SSIZE(1)|DMA_DCR_DSIZE(1);
	//load byte count, this also clears "done" bit
	DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(byteCount2);
	//start DMA
	DMA_DCR0 |= (1<<DMA_DCR_START_SHIFT)&DMA_DCR_START_MASK;

	//wait until DMA is finished
	DMA_done = 0;
	while(DMA_done==0)
	{
		DMA_done = (DMA_DSR_BCR0&DMA_DSR_BCR_DONE_MASK)>>DMA_DSR_BCR_DONE_SHIFT;
	}

	//clear "done" bit
	DMA_DSR_BCR0 &= ~((1<<DMA_DSR_BCR_DONE_SHIFT)&DMA_DSR_BCR_DONE_MASK);

	return 0;
}

int8_t DMA_memzero(uint8_t *src, uint32_t length)
{
	//allocate memory and populate with 0's
	uint8_t zeros[length];

	//call function to move 0's to the input address
	DMA_memmove(zeros, src, length);

	return 0;
}

int8_t DMA_memzero_32bit(uint8_t *src, uint32_t length)
{
	//allocate memory and populate with 0's
	uint8_t zeros[length];

	//call function to move 0's to the input address
	DMA_memmove_32bit(zeros, src, length);

	return 0;
}

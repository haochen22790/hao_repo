/*
 * DMA_memory.h
 *
 *  Created on: Jul 24, 2016
 *      Author: hao
 */

#ifndef SOURCES_DMA_MEMORY_H_
#define SOURCES_DMA_MEMORY_H_

#include <stdint.h>

void DMA_init();
int8_t DMA_memmove(uint8_t *src, uint8_t *dst, uint32_t length);
int8_t DMA_memmove_32bit(uint8_t *src, uint8_t *dst, uint32_t length);
int8_t DMA_memzero(uint8_t *src, uint32_t length);
int8_t DMA_memzero_32bit(uint8_t *src, uint32_t length);

#endif /* SOURCES_DMA_MEMORY_H_ */

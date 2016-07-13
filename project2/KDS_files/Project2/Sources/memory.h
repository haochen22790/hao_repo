/*
 * memory.h
 *
 *  Created on: Jul 10, 2016
 *      Author: hao
 */

#ifndef SOURCES_MEMORY_H_
#define SOURCES_MEMORY_H_

//move a length(input3) of memory from source(input1) to destination(input2)
//returns 0 if successful
int8_t memmove1(uint8_t*, uint8_t*, uint32_t);

//set a length(input2) of bytes in memory(input1) to 0
//returns 0 if successful
int8_t memzero(uint8_t*, uint32_t);

//reverse a length(input2) of bytes in memory(input1)
//returns 0 if successful
int8_t reverse(uint8_t*, uint32_t length);

#endif /* SOURCES_MEMORY_H_ */

#ifndef _MEMORY_H
#define _MEMORY_H

//move a specified length of bytes from source pointer
//to destination pointer
int8_t memmove1(uint8_t*, uint8_t*, uint32_t);

//set a specified number of bytes to 0, at the
//source pointer location
int8_t memzero(uint8_t*, uint32_t);

//reverse a specified number of bytes, starting at
//the source pointer location
int8_t reverse(uint8_t*, uint32_t length);

#endif

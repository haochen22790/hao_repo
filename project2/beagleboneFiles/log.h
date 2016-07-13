#ifndef SOURCES_LOG_H_
#define SOURCES_LOG_H_

#include <stdint.h>

//converts integer to string/ascii
void itoa_uint32(uint32_t n, uint8_t * s);

//reverse all char in an array, terminated by the null terminator
void reverse2(uint8_t * s);

//reverse all all elements in memory, of the specified length
void reverse1(char *str, int len);

//convert integer to string, this is specifically used in ftoa() function
int32_t intToStr1(int32_t x, uint8_t str[], int32_t d);

//converts float to string/ascii, with the specified number of decimal point
void ftoa(float n, uint8_t *res, int32_t afterpoint);

#endif /* SOURCES_LOG_H_ */


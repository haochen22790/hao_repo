#ifndef CONVERT_H
#define CONVERT_H

#include <stdint.h>

void itoa(int8_t n, uint8_t s[]);
void reverse(uint8_t s[]);
void reverse1(char *str, int len);
int32_t intToStr1(int32_t x, uint8_t str[], int32_t d);
void ftoa(float n, uint8_t *res, int32_t afterpoint);

#endif

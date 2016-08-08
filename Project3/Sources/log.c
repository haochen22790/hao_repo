/*
 * log.c
 *
 *  Created on: Jul 3, 2016
 *      Author: hao
 */

#include "log.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <uart.h>

extern UART_Desc deviceData;

void LOG_0(uint8_t * data, uint8_t length)
{
	uint8_t i;

	for (i=0; i<length; i++)
	{
		SendChar(*data, &deviceData);
		data++;
	}
}

//print parameter that is unsigned 32 bit type
void LOG_1(uint8_t * data, uint8_t length, uint32_t * param, uint8_t data_type_size)
{

	uint8_t str[20];
	uint8_t * str_ptr = str;

	LOG_0(data, length);

	itoa_uint32(*param, str);

	while (*str_ptr!='\0')
	{
		SendChar(*str_ptr, &deviceData);
		str_ptr++;
	}

	SendChar('\r', &deviceData);
	SendChar('\n', &deviceData);
}

//print parameter that is float type type
void LOG_2(uint8_t * data, uint8_t length, float * param, uint8_t afterpoint)
{
	uint8_t str[20];
	uint8_t * str_ptr = str;

	LOG_0(data, length);

	ftoa(*param, str, afterpoint);

	while (*str_ptr!='\0')
	{
		SendChar(*str_ptr, &deviceData);
		str_ptr++;
	}

	SendChar('\r', &deviceData);
	SendChar('\n', &deviceData);
}

/* itoa:  convert n to characters in s */
void itoa_uint32(uint32_t n, uint8_t * s)
{
    uint8_t i;

    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */

    s[i] = '\0';
    reverse2(s);
}

/* reverse:  reverse string s in place */
void reverse2(uint8_t * s)
{
    int8_t i, j;
    uint8_t c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

// reverses a string 'str' of length 'len'
void reverse1(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int32_t intToStr(int32_t x, uint8_t str[], int32_t d)
{
    int32_t i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse1(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating point number to string.
void ftoa(float n, uint8_t *res, int32_t afterpoint)
{
    // Extract integer part
    int32_t ipart = (int32_t)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int32_t i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int32_t)fpart, res + i + 1, afterpoint);
    }
}

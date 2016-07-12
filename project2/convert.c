#include "convert.h"
#include <string.h>
#include <math.h>

/* itoa:  convert n to characters in s */
void itoa(int8_t n, uint8_t s[])
{
    int8_t i, sign;
 
    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

/* reverse:  reverse string s in place */
void reverse(uint8_t s[])
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

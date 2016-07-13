#include <stdio.h>
#include "log.h"

//this is the code for emulating the LOG functions on the beaglebone

int main()
{
  //emulating LOG_0()
  printf("Testing123, Serial Print Test, no params\n");

  //emulating LOG_1()
  uint32_t var = 200;
  uint8_t str[20];
  uint8_t *str_ptr = str;
  itoa_uint32(var, str_ptr);
  printf("This is an integer number: ");
  printf("%s\n", str);
  
  var = 4096;
  itoa_uint32(var, str_ptr);
  printf("This is an integer number: ");
  printf("%s\n", str);

  var = 123456;
  itoa_uint32(var, str_ptr);
  printf("This is an integer number: ");
  printf("%s\n", str);
  
  //emulating LOG_2()
  float fvar = 1543.321;
  ftoa(fvar, str_ptr, 3);
  printf("This is a floating point number: ");
  printf("%s\n", str);

  return 0;
}

#include <stdio.h>
#include "convert.h"

int main()
{
  int8_t var = 121;
  uint8_t str[20];

  itoa(var, str);
  printf("string is: %s\n", str);
  
  uint8_t res[20];
  float n = 1543.321;
  ftoa(n, res, 4);
  printf("\n\"%s\"\n", res);

  return 0;
}

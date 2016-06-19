#include <stdint.h>
#include <stdio.h>
#include "project_1.h"
#include "memory.h"

void project_1_report()
{
  int i;
  uint8_t array[32];
  uint8_t* aptr_1;
  uint8_t* aptr_2;
  uint8_t* aptr_3;
  int8_t output;

  aptr_1 = array;
  aptr_2 = &array[8];
  aptr_3 = &array[16];

  //initialize the first 16 bytes to be 1 to 16
  for (i=0; i<16; i++)
  {
    array[i] = i + 1;
  }
  
  //print array
  printf("\ninitialize first 16 bytes\n");
  for (i=0; i<32; i++) printf("%d ", array[i]);
  printf("\n");

  //initialize content of aptr_3 to end of array to 0
  output = memzero(aptr_3, 16);
  
  //print array
  printf("\nuse memzero to clear aptr_3 and beyond\n");
  for (i=0; i<32; i++) printf("%d ", array[i]);
  printf("\n");

  //move 8 bytes from aptr_1 to aptr_3
  output = memmove1(aptr_1, aptr_3, 8);

  //printf array
  printf("\nmove 8 bytes from aptr_1 to aptr_3\n");
  for (i=0; i<32; i++) printf("%d ", array[i]);
  printf("\n");

  //move 16 bytes from aptr_2 to aptr_1
  output = memmove1(aptr_2, aptr_1, 16);
  
  //print array
  printf("\nmove 16 bytes from aptr_2 to aptr_1\n");
  for (i=0; i<32; i++) printf("%d ", array[i]);
  printf("\n");

  //reverse the entire 32 bytes
  output = reverse(aptr_1, 32);

  //print array
  printf("\nreverse the entire 32 bytes\n");
  for (i=0; i<32; i++) printf("%d ", array[i]);
  printf("\n");
 
}

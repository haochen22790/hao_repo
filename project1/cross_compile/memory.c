#include <stdint.h>
#include <stdio.h>
#include "memory.h"

//this function move length of bytes from source to destination
int8_t memmove1(uint8_t* src, uint8_t* dst, uint32_t length)
{
  uint32_t i;

  //return non-zero output if function fails
  if (length < 0)
  {
    return 1;
  }

  //if destination address is greater than source address,
  //then start with the first address
  if (dst < src)
  {
    for (i=0; i<length; i++)
    {
      //move element from source to destination
      *dst = *src;
      
      //increment pointers
      dst++;
      src++;
    }
  }
  //if destination address is less than the source address,
  //then start with the last address
  else if (dst > src)
  {
    //move pointers to the end of the arrays
    src = src + length - 1;
    dst = dst + length - 1;

    for (i=0; i<length; i++)
    { 
      //move element from source to destination
      *dst = *src;

      //decrement pointers
      dst--;
      src--;
    }
  }
  else
  {
    //do not do anything
  }

  return 0;
}

//this function clears length of bytes from source location
int8_t memzero(uint8_t* src, uint32_t length)
{
  uint32_t i;
  
  //return non-zero output if function fails
  if (length < 0)
  {
    return 1;
  }

  //set each element to 0
  for (i=0; i<length; i++)
  {
    *src = 0;
    src++;
  }

  return 0;
}

//this function reverses all bytes at the given location
int8_t reverse(uint8_t* src, uint32_t length)
{
  uint8_t* end_ptr;
  uint8_t temp;
  
  //return non-zero output if function fails
  if (length < 0)
  {
    return 1;
  }

  //define a pointer to point to the last element
  end_ptr = src + length - 1;
  
  //swap elements at the two pointers
  while (end_ptr > src)
  {
    temp = *src;
    *src = *end_ptr;
    *end_ptr = temp;
    src++;
    end_ptr--;
  }

  return 0;
}

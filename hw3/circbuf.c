#include <stdio.h>
#include "circbuf.h"

//returns 1 if buffer is full, returns 0 otherwise
int8_t bufFull(circBuf_t * c)
{
  if (c->num_items >= c->buf_size)
    return 1;
  else
    return 0;
}

//returns 1 if buffer is empty, returns 0 otherwise
int8_t bufEmpty(circBuf_t * c)
{
  if (c->num_items == 0)
    return 1;
  else
    return 0;
}

//add an item to the circular buffer
int8_t bufAddItem(circBuf_t * c, uint8_t item)
{
  //increment head by one
  uint8_t * new_head = c->head + 1;
  
  //wrap around
  if (new_head == (c->buffer + c->buf_size))
    new_head = c->buffer;

  if (new_head == c->tail)
    //error if buffer is full
    return -1;
  else
  {
    //increment head
    c->head = new_head;
    //add item to buffer
    *(c->head) = item;
    //increase num_item by 1, to track the number of items in buffer
    c->num_items++;

    return 0;
  }
}

//remove an item from the circular buffer
int8_t bufRemoveItem(circBuf_t * c, uint8_t * item)
{
  if (c->num_items == 0)
    //error if buffer is empty
    return -1;
  else
  {
    //read the data at tail
    *item = *(c->tail);
    //erase the data at tail (not required, but helpful for debug)
    *(c->tail) = 0;
    //increment tail
    c->tail++;
    //reduce num_item by 1, to track the number of items in buffer
    c->num_items--;

    return 0;
  }
}

#ifndef CIRCBUF_H
#define CIRCBUF_H

#include <stdint.h>

typedef struct circBuf
{
  uint8_t * buffer;
  uint8_t * head;
  uint8_t * tail;
  uint8_t buf_size;
  uint8_t num_items;
} circBuf_t;

//returns 1 if buffer is full, returns 0 otherwise
int8_t bufFull(circBuf_t * c);

//returns 1 if buffer is empty, returns 0 otherwise
int8_t bufEmpty(circBuf_t * c);

//add an item to the circular buffer, returns -1 if failed
//fails if buffer is full
int8_t bufAddItem(circBuf_t * c, uint8_t item);

//remove an item from the circular buffer, returns -1 if failed
//fails if buffer is empty
int8_t bufRemoveItem(circBuf_t * c, uint8_t * item);

#endif

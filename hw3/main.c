#include <stdio.h>
#include "circbuf.h"

int main(void)
{
  circBuf_t * c;
  int8_t output;
  uint8_t * remove_here;
  int i;
  uint8_t buf_start;
  
  c->buffer = &buf_start;
  c->head = c->buffer;
  c->tail = c->buffer;
  c->buf_size = 5;
  c->num_items = 0;
  
  output = bufFull(c);
  printf("is buffer full? %d\n", output);

  output = bufEmpty(c);
  printf("is buffer empty? %d\n", output);

  output = bufAddItem(c, 5);
  output = bufAddItem(c, 10);
  output = bufAddItem(c, 20);
  output = bufAddItem(c, 40);
  output = bufAddItem(c, 23);
  for (i=0; i<(c->buf_size); i++)
    printf("%d ", c->buffer[i]);
  printf("num_item = %d\n", c->num_items);
  
  output = bufFull(c);
  printf("is buffer full? %d\n", output);

  //output = bufRemoveItem(c, remove_here);
  for (i=0; i<(c->buf_size); i++)
    printf("%d ", c->buffer[i]);
  printf("num_item = %d\n", c->num_items);

  return 0;
}

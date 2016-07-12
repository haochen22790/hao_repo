#include <stdio.h>
#include "circbuf.h"

int main(void)
{
  circBuf_t cbuff;
  circBuf_t * c = &cbuff; //pointer to circular buffer parameters
  int8_t output;
  uint8_t remove_here;
  uint8_t i;
  uint8_t buf_start[10]; //allocate memory locations for buffer elements
  
  c->buffer = buf_start;
  c->head = c->buffer;
  c->tail = c->buffer;
  c->buf_size = 10;
  c->num_items = 0;

  int8_t test_result[7];

  //test 1: is buffer empty?
  output = bufEmpty(c);
  test_result[0] = ((output==1)&&(c->num_items==0));
  if (test_result[0]==1)
    printf("CB UNIT TEST: 1/7 - Verify buffer empty .... PASS\n");
  else
    printf("CB UNIT TEST: 1/7 - Verify buffer empty .... FAIL\n");

  //test 2: remove element when buffer is empty
  output = bufRemoveItem(c, &remove_here);
  test_result[1] = ((output==-1)&&(c->num_items==0));
  if (test_result[1]==1)
    printf("CB UNIT TEST: 2/7 - Remove element when empty .... PASS\n");
  else
    printf("CB UNIT TEST: 2/7 - Remove element when empty .... FAIL\n");

  //test 3: fill the buffer to full, is buffer full?
  for (i=0; i<10; i++)
  {
    output = bufAddItem(c, 5);
  }
  output = bufFull(c);
  test_result[2] = ((output==1)&&(c->num_items==10));
  if (test_result[2]==1)
    printf("CB UNIT TEST: 3/7 - Verify buffer full .... PASS\n");
  else
    printf("CB UNIT TEST: 3/7 - Verify buffer full .... FAIL\n");
  
  //test 4: add element when buffer is full
  output = bufAddItem(c, 5);
  test_result[3] = ((output==-1)&&(c->num_items==10));
  if (test_result[3]==1)
    printf("CB UNIT TEST: 4/7 - Add element when full .... PASS\n");
  else
    printf("CB UNIT TEST: 4/7 - Add element when full .... FAIL\n");
  
  //test 5: test wrap around, step 1) remove 2 elements
  output = bufRemoveItem(c, &remove_here);
  output = bufRemoveItem(c, &remove_here);
  test_result[4] = ((output==0)&&(c->num_items==8));
  if (test_result[4]==1)
    printf("CB UNIT TEST: 5/7 - Wrap around part 1: remove .... PASS\n");
  else
    printf("CB UNIT TEST: 5/7 - Wrap around part 1: remove .... FAIL\n");
  
  //test 6: test wrap around, step 2) add 2 elements
  output = bufAddItem(c, 5);
  output = bufAddItem(c, 5);
  test_result[5] = ((output==0)&&(c->num_items==10));
  if (test_result[5]==1)
    printf("CB UNIT TEST: 6/7 - Wrap around part 2: add .... PASS\n");
  else
    printf("CB UNIT TEST: 6/7 - Wrap around part 2: add .... FAIL\n");
  
  //test 7: remove all elements, is buffer empty?
  for (i=0; i<10; i++)
  {
    output = bufRemoveItem(c, &remove_here);
  }
  output = bufEmpty(c);
  test_result[6] = ((output==1)&&(c->num_items==0));
  if (test_result[6]==1)
    printf("CB UNIT TEST: 7/7 - Verify buffer empty .... PASS\n");
  else
    printf("CB UNIT TEST: 7/7 - Verify buffer empty .... FAIL\n");
  
  int8_t num_pass = 0;
  for (i=0; i<7; i++)
  {
    if (test_result[i]==1)
      num_pass++;
  }
  if (num_pass==7)
    printf("CIRCBUFF UNIT TEST SUITE: PASS (7/7 PASS)\n");
  else
    printf("CIRCBUFF UNIT TEST SUITE: FAIL (%d/7 PASS)\n", num_pass);

  return 0;
}

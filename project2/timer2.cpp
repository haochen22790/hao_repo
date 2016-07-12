#include <iostream>
#include <time.h>
#include <stdio.h>
using namespace std;
 
timespec diff(timespec start, timespec end);
 
int main()
{
  timespec time1, time2;
  long Tdiff;

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
  printf("21 character string!\n");
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
  Tdiff = time2.tv_nsec - time1.tv_nsec;
  Tdiff/=1000;
  printf("execution time in ns: %ld\n", Tdiff);

  return 0;
}


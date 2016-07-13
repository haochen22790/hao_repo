#include <iostream>
#include <time.h>
#include <stdio.h>
using namespace std;

//this is the code used to perform time profiling for
//the printf() function on the beaglebone

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
  printf("execution time in us: %ld\n", Tdiff);

  return 0;
}


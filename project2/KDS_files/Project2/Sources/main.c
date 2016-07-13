/* ###################################################################
**     Filename    : main.c
**     Project     : UART_withPE
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-07-03, 12:51, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "AS1.h"
#include "RxBuf.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "log.h"
#include "LED.h"
#include "timer.h"
#include "memory.h"
#include "CB_test.h"
#include "circBuf.h"
#include <stdio.h>
#include <string.h>
#include <uart.h>

//compile time switches
#define DEBUG 0
#define LED_CTRL 0
#define TIME_PROFILE 0
#define UTESTS 1

extern UART_Desc deviceData;

int main(void)
{
  //UART initialization
  Init();

  //-------------- part 1 first half: UART logger ---------------
#if DEBUG == 1
  uint8_t data[] = "Testing123, Serial Print Test, no params\r\n";
  uint8_t length = 42;
  LOG_0(data, length);

  uint8_t data2[] = "This is an integer number: ";
  length = 27;
  uint32_t var = 200;
  LOG_1(data2, length, &var, 1);

  var = 4096;
  LOG_1(data2, length, &var, 2);

  var = 123456;
  LOG_1(data2, length, &var, 4);

  uint8_t data3[] = "This is a floating point number: ";
  length = 33;
  float f = 1543.321;
  LOG_2(data3, length, &f, 3);
#endif

  //-------------- part 1 second half: LED control with PWM ----------------
#if LED_CTRL == 1
  LED_init();
  control_LED();
#endif

  //------------ part 2: execution time profiling -------------
#if TIME_PROFILE == 1
  init_timer();

  volatile uint32_t count1;
  volatile uint32_t count2;
  uint32_t count_diff;
  uint32_t Texec; //execution time

  uint8_t src[5000];
  uint8_t dst[5000];
  uint32_t length = 5000;
  uint32_t i;
  int8_t output;

  //initialize the source array to have nonzero values
  for (i=0; i<5000; i++)
  {
	  src[i] = i;
  }

  count1 = TPM2_BASE_PTR->CNT;
  output = memmove1(src, dst, length);
  count2 = TPM2_BASE_PTR->CNT;
  Texec = get_time(count1, count2);
  LOG_1("execution time in microsecond: ", 31, &Texec, 4);
  LOG_0("\r\n", 2);
#endif

  //--------------- part 3: circular buffer unit test ----------------
#if UTESTS == 1
  circBuf_t cbuff;
  circBuf_t * c = &cbuff; //pointer to circular buffer parameters
  CB_unit_test(c);
#endif

  for (;;){};
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */

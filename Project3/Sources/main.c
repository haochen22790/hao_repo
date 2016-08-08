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

//#pragma GCC optimize ("O0")

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
#include "DMA_memory.h"
#include <malloc.h>
#include "SPI.h"
#include "nRF24L01.h"

//compile time switches
#define DEBUG 0
#define LED_CTRL 0
#define TIME_PROFILE 0
#define UTESTS 0
#define DMA_PROFILE 0
#define MEM_SEG 1
#define SPI_NRF 0

extern UART_Desc deviceData;

#if MEM_SEG
	void TPM2_handler();

	#define STRING_SIZE (12)
	#define RED_LED_PIN (18)

	uint8_t g1;
	uint8_t *g1_ptr = &g1;
	uint16_t g2 = 0;
	uint16_t *g2_ptr = &g2;
	uint32_t g3 = 10;
	uint32_t *g3_ptr = &g3;
	const uint32_t c1 = 9;
	uint32_t *c1_ptr = &c1;
	const uint8_t hstr[STRING_SIZE] = "Hello World";
#endif

int main(void)
{
  //UART initialization
  //Init();

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
  uint32_t length = 100;
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

#if DMA_PROFILE
  init_timer();

  volatile uint32_t count1;
  volatile uint32_t count2;
  uint32_t count_diff;
  uint32_t Texec; //execution time

  DMA_init();

  uint8_t DMA_src[5000];
  uint8_t DMA_dst[5000];
  uint32_t DMA_byteCount = 5000;
  uint32_t j;
  int8_t DMA_output;

  //initialize the source array to have nonzero values
  for (j=0; j<5000; j++)
  {
  	DMA_src[j] = j;
  }

  count1 = TPM2_BASE_PTR->CNT;
  //DMA_output = DMA_memmove_32bit(DMA_src, DMA_dst, DMA_byteCount);
  DMA_output = DMA_memzero_32bit(DMA_src, DMA_byteCount);
  count2 = TPM2_BASE_PTR->CNT;
  Texec = get_time(count1, count2);
  LOG_1("execution time in microsecond: ", 31, &Texec, 4);
  LOG_0("\r\n", 2);
#endif

#if MEM_SEG
  uint8_t * heap_var;
  uint8_t l1;
  uint8_t *l1_ptr = &l1;
  uint16_t l2 = 0;
  uint16_t *l2_ptr = &l2;
  uint32_t l3 = 10;
  uint32_t *l3_ptr = &l3;
  void (*funcPtr)() = init_timer;   // Set this equal to your Timer Initialization function

  uint8_t g1_2 = g1;
  uint8_t *g1_ptr2 = g1_ptr;
  uint16_t g2_2 = g2;
  uint16_t *g2_ptr2 = g2_ptr;
  uint32_t g3_2 = g2;
  uint32_t *g3_ptr2 = g3_ptr;

  const uint32_t c1_2 = c1;
  uint32_t *c1_ptr2 = c1_ptr;
  const uint8_t *hstr2 = hstr;

  //default is aligned attribute
  struct test1{
	  char var1;
	  int var2;
	  char var3;
  };

  struct test1 test1_instance;
  char *var1_ptr = &test1_instance.var1;
  int *var2_ptr = &test1_instance.var2;
  char *var3_ptr = &test1_instance.var3;

  //packed attribute
  struct test2{
	  char var4;
	  int var5;
	  char var6;
  } __attribute__((packed));

  struct test2 test2_instance;
  char *var4_ptr = &test2_instance.var4;
  int *var5_ptr = &test2_instance.var5;
  char *var6_ptr = &test2_instance.var6;

  LED_init();                     // Setup pin control for the Red RGB LED
  TPM2_handler();
  (*funcPtr)();
  heap_var = (uint8_t *) malloc(STRING_SIZE);

  if (!heap_var) {
	  while(1);
  }

  uint8_t *ret;
  //ret = memmove1(hstr, heap_var, STRING_SIZE);
  ret = memmove(heap_var, hstr, STRING_SIZE);

  //---------------------------------------------------------
  // Some code exists here that you do not need to know about
  //---------------------------------------------------------

  free(heap_var);
#endif

#if SPI_NRF
  //store nRF24 read-back data in this variable
  uint8_t read;

  //initialize the SPI module on the KL25z
  SPI_init();

  //write to CONFIG register to power up and configure the nRF24
  nrf_config();
  //send a NOP command to read the STATUS register
  read = nrf_status();
  //write to TX_ADDR register to configure the transmit address
  nrf_write_register(RF24_TX_ADDR, 0);
  //write to RF_SETUP register to configure transmit power
  nrf_write_register(RF24_RF_SETUP, RF24_RF_SETUP_RF_PWR_0);
  //read from FIFO status register
  read = nrf_read_register(RF24_FIFO_STATUS);
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

#if MEM_SEG
	void TPM2_handler()
	{
		uint8_t s1;
		uint16_t s2 = 0;
		uint32_t s3 = 10;

		uint8_t *s1_ptr = &s1;
		uint16_t *s2_ptr = &s2;
		uint32_t *s3_ptr = &s3;

		// More code here

		GPIOB_PTOR |= (1<<RED_LED_PIN);
		TPM2_BASE_PTR->SC |= TPM_SC_TOF_MASK;
	}
#endif

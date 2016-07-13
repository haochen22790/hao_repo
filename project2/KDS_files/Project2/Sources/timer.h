/*
 * timer.h
 *
 *  Created on: Jul 8, 2016
 *      Author: hao
 */

#ifndef SOURCES_TIMER_H_
#define SOURCES_TIMER_H_

#include <stdint.h>

//delay function used to generate PWM output
//input a determines the number of loops
void delay(uint16_t a);

//performs initialization of the registers for RGB LED
void init_timer();

//find the time difference between t1 and t2
//inputs should be the value of timer counter, each count = 8us
uint32_t get_time(volatile uint32_t t1, volatile uint32_t t2);

#endif /* SOURCES_TIMER_H_ */

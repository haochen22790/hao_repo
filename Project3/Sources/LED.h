/*
 * LED.h
 *
 *  Created on: Jul 5, 2016
 *      Author: hao
 */

#ifndef SOURCES_LED_H_
#define SOURCES_LED_H_

#include <stdint.h>

void LED_init();
void PWM_R(uint16_t dc);
void PWM_G(uint16_t dc);
void PWM_B(uint16_t dc);
void PWM_Y(uint16_t dc);
void PWM_C(uint16_t dc);
void PWM_M(uint16_t dc);
void PWM_W(uint16_t dc);
void LED_clear();
void control_LED();

#endif /* SOURCES_LED_H_ */

/*
 * CB_test.h
 *
 *  Created on: Jul 11, 2016
 *      Author: hao
 */

#ifndef SOURCES_CB_TEST_H_
#define SOURCES_CB_TEST_H_

#include "circBuf.h"

//perform circular buffer unit test suite, print pass/fail info
//to virtual serial port using UART
void CB_unit_test(circBuf_t * c);

#endif /* SOURCES_CB_TEST_H_ */

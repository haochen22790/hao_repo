/*
 * timer.c
 *
 *  Created on: Jul 8, 2016
 *      Author: hao
 */

#include "timer.h"
#include "MKL25Z4.h"

void init_timer()
{
	MCG_BASE_PTR->C1 = MCG_C1_IREFS_MASK | MCG_C1_IRCLKEN_MASK;
	MCG_BASE_PTR->C2 = MCG_C2_IRCS_MASK; //Select fast internal clock
	SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM2_MASK; //Enable TPM2 clock
	SIM_BASE_PTR->SOPT2 |= SIM_SOPT2_TPMSRC(3);

	TPM2_BASE_PTR->SC = TPM_SC_CMOD(1) | TPM_SC_PS(32); //8us period
	TPM2_BASE_PTR->MOD = 30000; //reset every 240 milliseconds

	//TPM2_BASE_PTR->SC |= TPM_SC_TOIE_MASK;
	//NVIC_BASE_PTR->ISER = 1 << 19;

	//SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	//PORTB_BASE_PTR->PCR[18] = PORT_PCR_MUX(1);

	//PTB_BASE_PTR->PDDR = 1 << 18;
}

uint32_t get_time(volatile uint32_t t1, volatile uint32_t t2)
{
	uint32_t count_diff;
	if (t2>=t1)
	{
		count_diff = t2 - t1;
	} else
	{
		t2+=30000; //wrap around
		count_diff = t2 - t1;
	}

	count_diff*=8; //multiply by period to get actual time, in microseconds
	return count_diff;
}


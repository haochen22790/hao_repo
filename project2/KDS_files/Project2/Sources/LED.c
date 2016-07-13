/*
 * LED.c
 *
 *  Created on: Jul 5, 2016
 *      Author: hao
 */

#include <uart.h>
#include "LED.h"
#include "RxBuf.h"
#include "AS1.h"
#include "log.h"

extern UART_Desc deviceData;
uint8_t color_code = 0;	//default color is red
uint8_t dc_code = 50;  //default duty cycle is 50%

//delay function used for PWM output
void delay(uint16_t a)
{
	while(a>0)
		a--;
}

//initialization for RBG LED
void LED_init()
{
	//enable clock on LED ports
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

	//mux to GPIO, and enable drive strain
	PORTB_PCR18 = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
	PORTB_PCR19 = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
	PORTD_PCR1 = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);

	//set LED ports to output
	PTB_BASE_PTR->PDDR |= 1 << 18;
	PTB_BASE_PTR->PDDR |= 1 << 19;
	PTD_BASE_PTR->PDDR |= 1 << 1;

	//clear all colors
	PTB_BASE_PTR->PSOR |= 1 << 18;
	PTB_BASE_PTR->PSOR |= 1 << 19;
	PTD_BASE_PTR->PSOR |= 1 << 1;
}

//red, input duty cycle
void PWM_R(uint16_t dc)
{
	LED_clear();

	for(;;)
	{
		PTB_BASE_PTR->PCOR |= 1 << 18;
		delay(dc*10);
		PTB_BASE_PTR->PSOR |= 1 << 18;
		delay(1000-dc*10);
		if (RxBuf_NofElements()!=0)
			break;
	}
}

//green, input duty cycle
void PWM_G(uint16_t dc)
{
	LED_clear();

	for(;;)
	{
		PTB_BASE_PTR->PCOR |= 1 << 19;
		delay(dc*10);
		PTB_BASE_PTR->PSOR |= 1 << 19;
		delay(1000-dc*10);
		if (RxBuf_NofElements()!=0)
			break;
	}
}

//blue, input duty cycle
void PWM_B(uint16_t dc)
{
	LED_clear();

	for(;;)
	{
		PTD_BASE_PTR->PCOR |= 1 << 1;
		delay(dc*10);
		PTD_BASE_PTR->PSOR |= 1 << 1;
		delay(1000-dc*10);
		if (RxBuf_NofElements()!=0)
			break;
	}
}

//yellow = red + green, input duty cycle
void PWM_Y(uint16_t dc)
{
	LED_clear();

	for(;;)
	{
		PTB_BASE_PTR->PCOR |= 1 << 18;
		PTB_BASE_PTR->PCOR |= 1 << 19;
		delay(dc*10);
		PTB_BASE_PTR->PSOR |= 1 << 18;
		PTB_BASE_PTR->PSOR |= 1 << 19;
		delay(1000-dc*10);
		if (RxBuf_NofElements()!=0)
			break;
	}
}

//cyan = green + blue, input duty cycle
void PWM_C(uint16_t dc)
{
	LED_clear();

	for(;;)
	{
		PTB_BASE_PTR->PCOR |= 1 << 19;
		PTD_BASE_PTR->PCOR |= 1 << 1;
		delay(dc*10);
		PTB_BASE_PTR->PSOR |= 1 << 19;
		PTD_BASE_PTR->PSOR |= 1 << 1;
		delay(1000-dc*10);
		if (RxBuf_NofElements()!=0)
			break;
	}
}

//magenta = red + blue, input duty cycle
void PWM_M(uint16_t dc)
{
	LED_clear();

	for(;;)
	{
		PTB_BASE_PTR->PCOR |= 1 << 18;
		PTD_BASE_PTR->PCOR |= 1 << 1;
		delay(dc*10);
		PTB_BASE_PTR->PSOR |= 1 << 18;
		PTD_BASE_PTR->PSOR |= 1 << 1;
		delay(1000-dc*10);
		if (RxBuf_NofElements()!=0)
			break;
	}
}

//white = red + green + blue, input duty cycle
void PWM_W(uint16_t dc)
{
	LED_clear();

	for(;;)
	{
		PTB_BASE_PTR->PCOR |= 1 << 18;
		PTB_BASE_PTR->PCOR |= 1 << 19;
		PTD_BASE_PTR->PCOR |= 1 << 1;
		delay(dc*10);
		PTB_BASE_PTR->PSOR |= 1 << 18;
		PTB_BASE_PTR->PSOR |= 1 << 19;
		PTD_BASE_PTR->PSOR |= 1 << 1;
		delay(1000-dc*10);
		if (RxBuf_NofElements()!=0)
			break;
	}
}

void LED_clear()
{
	//clear all colors
	PTB_BASE_PTR->PSOR |= 1 << 18;
	PTB_BASE_PTR->PSOR |= 1 << 19;
	PTD_BASE_PTR->PSOR |= 1 << 1;
}

//control LED using inputs from virtual serial port
//use 'a' and 'd' to cycle through different colors
//use 'w' and 's' to increase or decrease brightness
void control_LED()
{
	for(;;)
	{
		if (RxBuf_NofElements()!=0)
		{
		      while (RxBuf_NofElements()!=0)
		      {
		        uint8_t ch;

		        (void)RxBuf_Get(&ch);
		        LOG_0("echo: ", 6);
		        LOG_0(&ch, 1);
		        LOG_0("\r\n", 2);

		        if (ch=='w' && dc_code<=90)
		        {
		        	dc_code+=10; //increase brightness
		        	LOG_0("Increase brightness\r\n", 21);
		        } else if (ch=='s' && dc_code>=10)
		        {
		        	dc_code-=10; //decrease brightness
		        	LOG_0("Decrease brightness\r\n", 21);
		        } else if (ch=='d' && color_code<7)
		        {
		        	color_code++;
		        	LOG_0("Change color\r\n", 14);
		        }else if (ch=='a' && color_code>0)
		        {
		        	color_code--;
		        	LOG_0("Change color\r\n", 14);
		        }

		        switch (color_code)
		        {
		        	case 0:
		        		PWM_R(dc_code);
		        		break;
		        	case 1:
		        		PWM_G(dc_code);
		        		break;
		        	case 2:
						PWM_B(dc_code);
						break;
					case 3:
						PWM_Y(dc_code);
						break;
					case 4:
						PWM_C(dc_code);
						break;
					case 5:
						PWM_M(dc_code);
						break;
					case 6:
						PWM_W(dc_code);
						break;
					case 7:
						LED_clear();
						break;
					default:
						break;
		        }
		      }
		}
	}
 }

/*
 * ws2812.c
 *
 *  Created on: 1 Aug 2019
 *      Author: Mario
 */

#include <stddef.h>
#include "stm32f10x.h"


/************************
 * WS2812 prototype functions
 *
 * using PB9
 */
void ws2812_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	GPIOB->CRH &= ~GPIO_CRH_CNF9;
	GPIOB->CRH |= GPIO_CRH_MODE9;
	GPIOB->ODR &= ~GPIO_ODR_ODR9;
}

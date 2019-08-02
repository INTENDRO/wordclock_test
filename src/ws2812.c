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
	GPIO_InitTypeDef gpio_init;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_init.GPIO_Pin = GPIO_Pin_9;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio_init);

	GPIO_ResetBits(GPIOB, GPIO_Pin_9);
}

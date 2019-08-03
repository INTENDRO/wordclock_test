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

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_init.GPIO_Pin = GPIO_Pin_0;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_init);

	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
}

void ws2812_timer_init(void)
{
	TIM_TimeBaseInitTypeDef tim_init;
	TIM_OCInitTypeDef oc_init;
	GPIO_InitTypeDef gpio_init;
	RCC_ClocksTypeDef sys_clocks;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);

	RCC_GetClocksFreq(&sys_clocks);


	TIM_TimeBaseStructInit(&tim_init);
	tim_init.TIM_CounterMode = TIM_CounterMode_Up;
	tim_init.TIM_Prescaler = 0; //prescaler = 1
	tim_init.TIM_Period = 89; // -> 90 steps
	TIM_TimeBaseInit(TIM2, &tim_init);

	TIM_OCStructInit(&oc_init);
	oc_init.TIM_OCMode = TIM_OCMode_PWM1;
	oc_init.TIM_OutputState = TIM_OutputState_Enable;
	oc_init.TIM_OCPolarity = TIM_OCPolarity_High;
	oc_init.TIM_Pulse = 45;
	TIM_OC1Init(TIM2, &oc_init);

	gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_init.GPIO_Pin = GPIO_Pin_0;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_init);

	TIM_Cmd(TIM2, ENABLE);
}

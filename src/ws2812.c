/*
 * ws2812.c
 *
 *  Created on: 1 Aug 2019
 *      Author: Mario
 */

#include <stddef.h>
#include "stm32f10x.h"

uint16_t pwm_values[8] = {30,60,30,60,30,30,60,60};


void ws2812_init_debug_pin(void)
{
	GPIO_InitTypeDef gpio_init;

	GPIO_StructInit(&gpio_init);
	gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_init.GPIO_Pin = GPIO_Pin_1;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_init);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

void ws2812_init(void)
{
	TIM_TimeBaseInitTypeDef tim_init;
	TIM_OCInitTypeDef oc_init;
	GPIO_InitTypeDef gpio_init;
	DMA_InitTypeDef dma_init;

	// enable clocks
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	// initialize timer
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructInit(&tim_init);
	tim_init.TIM_CounterMode = TIM_CounterMode_Up;
	tim_init.TIM_Prescaler = 0; //prescaler = 1
	tim_init.TIM_Period = 89; // -> 90 steps
	TIM_TimeBaseInit(TIM2, &tim_init);

	// initialize PWM
	TIM_OCStructInit(&oc_init);
	oc_init.TIM_OCMode = TIM_OCMode_PWM1;
	oc_init.TIM_OutputState = TIM_OutputState_Disable; // -> pin low
	oc_init.TIM_OCPolarity = TIM_OCPolarity_High;
	oc_init.TIM_Pulse = 0; // dutycycle = 0 -> pin low
	TIM_OC1Init(TIM2, &oc_init);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

	// init DMA to set dutycycle
	TIM_DMAConfig(TIM2, TIM_DMABase_CCR1, TIM_DMABurstLength_1Transfer); // set the address for the dma to be written to (dma should point to DMAR register)
	TIM_DMACmd(TIM2, TIM_DMA_CC1, DISABLE); // activating the dma here would make it possible to generate dma request before the dma is enabled

	// initialize DMA (mode, mem addr and buffer size will be set according to payload in start function)
	DMA_StructInit(&dma_init);
	dma_init.DMA_PeripheralBaseAddr = (uint32_t)(&TIM2->DMAR);
	dma_init.DMA_DIR = DMA_DIR_PeripheralDST;
	dma_init.DMA_BufferSize = 8;
	dma_init.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma_init.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma_init.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	dma_init.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	dma_init.DMA_Priority = DMA_Priority_Low;
	dma_init.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel5, &dma_init);
	DMA_ClearFlag(DMA1_FLAG_GL5 | DMA1_FLAG_TC5 | DMA1_FLAG_HT5 | DMA1_FLAG_TE5);
	DMA_ClearITPendingBit(DMA1_IT_GL5 | DMA1_IT_TC5 | DMA1_IT_HT5 | DMA1_IT_TE5);
	DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);
	DMA_ITConfig(DMA1_Channel5, DMA_IT_HT, ENABLE);

	// enable DMA interrupts in NVIC
	NVIC_SetPriority(DMA1_Channel5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	NVIC_EnableIRQ(DMA1_Channel5_IRQn);

	// setup PWM pin
	gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_init.GPIO_Pin = GPIO_Pin_0;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_init);
}

void ws2812_start(void)
{
	DMA_Cmd(DMA1_Channel5, DISABLE); // Disable to be sure. DMA needs to be disabled for DMA data count to be set (CNDTR)
	DMA1_Channel5->CMAR = (uint32_t)pwm_values;
	DMA1_Channel5->CCR &= ~DMA_CCR5_CIRC; // normal mode
	//DMA1_Channel5->CCR |= DMA_CCR5_CIRC; // circular mode
	DMA1_Channel5->CNDTR = 8;
	TIM_SetCompare1(TIM2, 0);
	TIM_GenerateEvent(TIM2, TIM_EventSource_Update); // reset timer counter, prescaler and load shadow registers
	TIM_DMACmd(TIM2, TIM_DMA_CC1, DISABLE); // Disable to be sure. Clear possible DMA requests
	TIM_DMACmd(TIM2, TIM_DMA_CC1, ENABLE);
	DMA_Cmd(DMA1_Channel5, ENABLE);

	TIM_CCxCmd(TIM2, TIM_Channel_1, TIM_CCx_Enable); // enable PWM output on pin (low because of 0 dutycycle)
	TIM_Cmd(TIM2, ENABLE); // start waveform generation
}

void ws2812_stop(void)
{

}

void DMA1_Channel5_IRQHandler(void)
{
	if(DMA_GetFlagStatus(DMA1_FLAG_HT5) == SET)
	{
		DMA_ClearITPendingBit(DMA1_IT_HT5);
		GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
	}
	else if(DMA_GetFlagStatus(DMA1_FLAG_TC5) == SET)
	{
		DMA_ClearITPendingBit(DMA1_IT_TC5);
		GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
	}
}

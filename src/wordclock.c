/*
 * wordclock.c
 *
 *  Created on: 12 Aug 2019
 *      Author: Mario
 */

#include <stddef.h>
#include "stm32f10x.h"
#include "delay.h"
#include "ws2812.h"
#include "wordclock.h"


void wordclock_init(void)
{
	ws2812_init();
}

void wordclock_demo(void)
{
	ws2812_set_color_all(0x00,0x00,0x00);
	ws2812_update(0);
	wait_1ms(500);
	while(1)
	{
		ws2812_set_color_all(0x0F,0x00,0x00);
		ws2812_update(0);
		wait_1ms(500);
		ws2812_set_color_all(0x00,0x0F,0x00);
		ws2812_update(0);
		wait_1ms(500);
		ws2812_set_color_all(0x00,0x00,0x0F);
		ws2812_update(0);
		wait_1ms(500);
		ws2812_set_color_all(0x0F,0x0F,0x0F);
		ws2812_update(0);
		wait_1ms(500);
		ws2812_set_color(1,0x0F,0x00,0x00);
		ws2812_set_color(2,0x0F,0x00,0x00);
		ws2812_set_color(3,0x0F,0x00,0x00);
		ws2812_set_color(4,0x0F,0x00,0x00);
		ws2812_set_color(5,0x00,0x0F,0x00);
		ws2812_set_color(6,0x00,0x0F,0x00);
		ws2812_set_color(7,0x00,0x0F,0x00);
		ws2812_set_color(8,0x00,0x00,0x0F);
		ws2812_set_color(9,0x00,0x00,0x0F);
		ws2812_set_color(10,0x00,0x00,0x0F);
		ws2812_set_color(11,0x00,0x00,0x0F);
		ws2812_update(0);
		wait_1ms(500);

	}
}

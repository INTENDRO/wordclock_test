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

typedef struct
{
	uint8_t start;
	uint8_t stop;
}word_mapping_minutes_t;


typedef struct
{
	uint8_t start;
	uint8_t stop;
}word_mapping_hours_t;

static const word_mapping_minutes_t word_mapping_minutes[12] = {
		{12, 19}
};

static const word_mapping_hours_t word_mapping_hours[12] = {
		{34, 40}
};

void wordclock_display_word_time(uint16_t time)
{
	uint16_t min_index, hour_index;

	min_index = time%12;
	hour_index = (time/12)%12;

	ws2812_set_color_all(0,0,0);
	ws2812_set_color_range(word_mapping_hours[hour_index].start, word_mapping_hours[hour_index].stop, 0x00, 0x1F, 0x00);
	ws2812_set_color_range(word_mapping_minutes[min_index].start, word_mapping_minutes[min_index].stop, 0x00, 0x1F, 0x00);
	ws2812_update(0);
}

void wordclock_init(void)
{
	ws2812_init();
}

void wordclock_demo(void)
{
	ws2812_set_color_all(0x00,0x00,0x10);
	ws2812_update(0);
	wait_1ms(500);

	//ws2812_set_color_range(4, 8, 0x00, 0x1F, 0x1F);
	//ws2812_update(0);
	//wait_1ms(500);
    //
	//ws2812_set_color_range(4, 18, 0x00, 0x00, 0x1F);
	//ws2812_update(0);
	//wait_1ms(500);

	while(1);

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

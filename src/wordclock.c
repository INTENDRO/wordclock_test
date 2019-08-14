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

#define WORD_TEST_RED 0x7F
#define WORD_TEST_GREEN 0x7F
#define WORD_TEST_BLUE 0x7F


typedef struct
{
	uint8_t start_w1;
	uint8_t stop_w1;
	uint8_t start_w2;
	uint8_t stop_w2;
}word_mapping_minutes_t;


typedef struct
{
	uint8_t start;
	uint8_t stop;
}word_mapping_hours_t;

static const word_mapping_minutes_t word_mapping_minutes[7] = {
		{12, 17, 18, 19},
		{96, 100, 0, 0},
		{81, 84, 0, 0},
		{103, 110, 0, 0},
		{89, 95, 0, 0},
		{89, 95, 96, 100},
		{85, 89, 0, 0}
};

static const word_mapping_hours_t word_mapping_hours[12] = {
		{34, 40},
		{64, 67},
		{61, 64},
		{56, 61},
		{45, 49},
		{49, 53},
		{53, 56},
		{72, 77},
		{23, 28},
		{41, 45},
		{20, 23},
		{28, 34}
};

void wordclock_display_word_time(uint16_t time)
{
	uint16_t min_index, hour_index, past_to, min_show;

	min_index = time%12;
	if(min_index == 0)
	{
		past_to = 0;
	}
	else if(min_index < 7)
	{
		past_to = 1;
	}
	else
	{
		past_to = 2;
	}

	hour_index = (time/12);
	if(min_index >= 7)
	{
		hour_index++;
	}
	hour_index %= 12;

	if(min_index < 7)
	{
		min_show = min_index;
	}
	else
	{
		min_show = 12 - min_index;
	}

	ws2812_set_color_all(0,0,0);
	ws2812_set_color_range(word_mapping_hours[hour_index].start, word_mapping_hours[hour_index].stop, WORD_TEST_RED, WORD_TEST_GREEN, WORD_TEST_BLUE);
	ws2812_set_color_range(word_mapping_minutes[min_show].start_w1, word_mapping_minutes[min_show].stop_w1, WORD_TEST_RED, WORD_TEST_GREEN, WORD_TEST_BLUE);
	ws2812_set_color_range(word_mapping_minutes[min_show].start_w2, word_mapping_minutes[min_show].stop_w2, WORD_TEST_RED, WORD_TEST_GREEN, WORD_TEST_BLUE);
	if(past_to == 1)
	{
		ws2812_set_color_range(67, 71, WORD_TEST_RED, WORD_TEST_GREEN, WORD_TEST_BLUE);
	}
	else if(past_to == 2)
	{
		ws2812_set_color_range(78, 80, WORD_TEST_RED, WORD_TEST_GREEN, WORD_TEST_BLUE);
	}
	ws2812_update(0);
}

void wordclock_init(void)
{
	ws2812_init();
}

void wordclock_demo_time(void)
{
	uint16_t time = 0;

	while(1)
	{
		wordclock_display_word_time(time);
		time = (time+1)%288;
		wait_1ms(3000);
	}
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

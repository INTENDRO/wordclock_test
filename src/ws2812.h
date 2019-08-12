/*
 * ws2812.h
 *
 *  Created on: 1 Aug 2019
 *      Author: Mario
 */

#ifndef WS2812_H_
#define WS2812_H_





void ws2812_init(void);
void ws2812_init_debug_pin(void);
void ws2812_start(void);
void ws2812_stop(void);
int8_t ws2812_set_color(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);
void ws2812_set_color_all(uint8_t red, uint8_t green, uint8_t blue);
int8_t ws2812_set_color_range(uint8_t start, uint8_t stop, uint8_t red, uint8_t green, uint8_t blue);
uint8_t ws2812_update_finished(void);
int8_t ws2812_update(uint8_t block);

#endif /* WS2812_H_ */

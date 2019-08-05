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
uint8_t ws2812_update_finished(void);
int8_t ws2812_update(uint8_t block);

#endif /* WS2812_H_ */

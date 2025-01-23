#ifndef __WS2812B_H__
#define __WS2812B_H__

typedef struct
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
}rgb_color;

typedef struct
{
	uint16_t g[8];
	uint16_t r[8];
	uint16_t b[8];
}neopixel_led;

void setLEDS(rgb_color *led);

#endif

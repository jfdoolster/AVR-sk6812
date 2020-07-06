#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define LED_PRT PORTC
#define LED_DDR DDRC
#define LED_PIN 6

#include "led_sk6812.h"

#define LED_COUNT 1
rgbw_color colors[LED_COUNT];

int main()
{

	char color_name[30] = "white";



	while (1)
	{

		for (uint16_t i = 0; i < LED_COUNT; i++)
		{
			//colors[i] = (rgbw_color){ 24, 221, 196 ,0}; // teal
			if (strcmp(color_name,"teal") == 0)
			{
				colors[i] = (rgbw_color){24,221,196,0};
			}
			if (strcmp(color_name,"red") == 0)
			{
				colors[i] = (rgbw_color){255,0,0,0};
			}
			if (strcmp(color_name,"blue") == 0)
			{
				colors[i] = (rgbw_color){0,0,255,0};
			}
			if (strcmp(color_name,"green") == 0)
			{
				colors[i] = (rgbw_color){0,255,0,0};
			}
			if (strcmp(color_name,"white") == 0)
			{
				colors[i] = (rgbw_color){0,0,0,255};
			}
		}

		// interrupts are not available until after first loop.
		led_strip_write(colors, LED_COUNT);
		_delay_ms(1);


	}
	return 0;
}



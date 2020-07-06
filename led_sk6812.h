#ifndef LED_SK6812
#define LED_SK6812

// based on the excellent pololu/pololu-led-strip-avr.git project
// optimized for SK6812 RGBW 

// create color structure
typedef struct rgbw_color { uint8_t red, green, blue, white; } 
rgbw_color;

void __attribute__((noinline)) led_strip_write(rgbw_color * colors, uint16_t count)
{
	// set output driving low
	LED_PRT &= ~(1<<LED_PIN);
	LED_DDR |=  (1<<LED_PIN);

	while (count--)
	{
	// Send a color to the LED strip.
	// The assembly below also increments the 'colors' pointer,
	// it will be pointing to the next color at the end of this loop.
	// pololu
	asm volatile (
		// remember that memroy is two bytes.
		"ld __tmp_reg__, %a0+\n" //mem0
		"ld __tmp_reg__, %a0\n"  //mem1
		"rcall send_led_byte%=\n"		// Send red component.
		"ld __tmp_reg__, -%a0\n" //mem0
		"rcall send_led_byte%=\n"		// Send green component.
		"ld __tmp_reg__, %a0+\n" //mem0
		"ld __tmp_reg__, %a0+\n" //mem1
		"ld __tmp_reg__, %a0+\n" //mem2
		"rcall send_led_byte%=\n"		// Send blue component.
		"ld __tmp_reg__, %a0\n"  //mem3
		"rcall send_led_byte%=\n"			// Send white component.

		"rjmp led_asm_end%=\n"     // Jump past the assembly subroutines.

		"send_led_byte%=:\n"
		"rcall send_led_bit%=\n"  // Send most-significant bit (bit 7).
		"rcall send_led_bit%=\n"
		"rcall send_led_bit%=\n"
		"rcall send_led_bit%=\n"
		"rcall send_led_bit%=\n"
		"rcall send_led_bit%=\n"
		"rcall send_led_bit%=\n"
		"rcall send_led_bit%=\n"  // Send least-significant bit (bit 0).
		"ret\n"

		// send_led_strip_bit subroutine:  Sends single bit to the LED strip by driving the data line
		// high for some time.  The amount of time the line is high depends on whether the bit is 0 or 1,
		// but this function always takes the same time (2 us).
		"send_led_bit%=:\n"
		"sbi %2, %3\n"                           // Drive the line high.
		"rol __tmp_reg__\n"                      // Rotate left through C bit (SREG).
		"nop\n" "nop\n"
		"brcs .+2\n" "cbi %2, %3\n"              // If C bit is 0, drive the line low.
		"nop\n" "nop\n" "nop\n" "nop\n" "nop\n"
		"brcc .+2\n" "cbi %2, %3\n"              // If C bit is 1, drive the line low.
		"ret\n"

		"led_asm_end%=: " // end of asm

		: "=b" (colors)		// output pointers
		: "0" (colors),     // %a0 points to the next color
		  "I" (_SFR_IO_ADDR(LED_PRT)),   // %2 is the port register
		  "I" (LED_PIN)					// %3 is the pin number
	);

	}
	//_delay_us(80);  // reset
}

#endif


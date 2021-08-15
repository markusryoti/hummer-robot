#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "serial.h"

void init()
{
	// Enable Arduino pin 7 (328p PD7)
	DDRD |= (1 << DDD7);
}

void serial_send(uint8_t data)
{
	uart_send_byte(data);
	_delay_ms(500);
}

void blink_led()
{
	// Set led on for small amount of time and then set off
	PORTD |= (1 << PORTD7);
	_delay_ms(10);
	PORTD &= ~(1 << PORTD7);
}

int main()
{
	uint8_t data;
	uint8_t start[] = "Serial initialized. ";
	uart_init(9600, 0);

	sei(); // enable global interrupts

	uart_send_string(start);

	while (1)
	{
		if (uart_read_count() > 0)
		{
			data = uart_read();
			uart_send_byte(data);

			// Do whatever action with the new data
			blink_led();
		}
	}
}

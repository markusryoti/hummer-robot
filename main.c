#include <stdint.h>
#include <ctype.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "serial.h"
#include "motor_controller.h"

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

void handle_keypress(uint8_t key)
{
	switch (tolower(key))
	{
	case 'w':
		move_forward();
		break;
	case 's':
		break;
	case 'd':
		break;
	case 'a':
		break;
	default:
		break;
	}
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

			// log key to serial
			uart_send_byte(data);
			// blink led to signal
			blink_led();
			//control motors
			handle_keypress(data);
		}
	}
}

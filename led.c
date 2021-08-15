#include <avr/io.h>
#include <util/delay.h>

#define BLINK_RATE 100

int main()
{
	DDRD |= (1 << DDD7);

	while (1)
	{
		PORTD ^= (1 << PORTD7);
		_delay_ms(BLINK_RATE);
	}
}

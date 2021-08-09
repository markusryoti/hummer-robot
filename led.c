#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRB |= (1 << DDB5);

	while (1)
	{
		PORTB |= (1 << PORTB5);
		_delay_ms(250);

		PORTB &= ~(1 << PORTB5);
		_delay_ms(250);
	}
}

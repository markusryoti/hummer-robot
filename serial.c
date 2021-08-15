#include "serial.h"

volatile static uint8_t rx_buffer[RX_BUFFER_SIZE] = {0};
volatile static uint16_t rx_count = 0;
volatile static uint8_t uart_tx_busy = 1; // not busy

ISR(USART_RX_vect)
{
	volatile static uint16_t rx_write_pos = 0;

	// get data from register
	// increment count to signal that data was added to buffer
	// increment write pos for next char that will go to the buffer
	rx_buffer[rx_write_pos] = UDR0;
	rx_count++;
	rx_write_pos++;

	// circular buffer
	if (rx_write_pos >= RX_BUFFER_SIZE)
	{
		rx_write_pos = 0;
	}
}

ISR(USART_TX_vect)
{
	uart_tx_busy = 1;
}

void uart_init(uint32_t baudrate, uint8_t high_speed)
{
	uint8_t speed = 16;

	if (high_speed != 0)
	{
		speed = 8;
		UCSR0A |= 1 << U2X0; // enable high speed
	}

	baudrate = (F_CPU / (speed * baudrate)) - 1;

	UBRR0H = (baudrate & 0x0F00) >> 8; // fit to 8-bit value
	UBRR0L = (baudrate & 0x00FF);			 // filter low bits

	// enable interrupts ?
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0) | (1 << TXCIE0);
}

void uart_send_byte(uint8_t c)
{
	while (uart_tx_busy == 0)
		;
	uart_tx_busy = 0;
	UDR0 = c;
}

void uart_send_array(uint8_t *c, uint16_t len)
{
	for (uint16_t i = 0; i < len; i++)
	{
		uart_send_byte(c[i]);
	}
}

void uart_send_string(uint8_t *c)
{
	uint16_t i = 0;

	do
	{
		uart_send_byte(c[i]);
		i++;
	} while (c[i] != '\0');
}

uint16_t uart_read_count()
{
	return rx_count;
}

uint8_t uart_read()
{
	static uint16_t rx_read_pos = 0;
	uint8_t data = 0;

	// read next character from buffer
	// increment pos to get the next character in buffer
	// decrement count since one item has been removed from the queue
	data = rx_buffer[rx_read_pos];
	rx_read_pos++;
	rx_count--;

	// circular
	if (rx_read_pos >= RX_BUFFER_SIZE)
	{
		rx_read_pos = 0;
	}

	return data;
}

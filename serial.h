#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define RX_BUFFER_SIZE 128

void uart_init(uint32_t baudrate, uint8_t high_speed);
void uart_send_byte(uint8_t c);
void uart_send_array(uint8_t *c, uint16_t len);
void uart_send_string(uint8_t *c);
uint16_t uart_read_count();
uint8_t uart_read();

#endif

default:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -o keyboard.bin serial.c keyboard.c
	avr-objcopy -O ihex -R .eeprom keyboard.bin keyboard.hex

flash:
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:keyboard.hex

clean:
	rm -f *.o *.bin

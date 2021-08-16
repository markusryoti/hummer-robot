default:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -o main.bin serial.c motor_controller.c main.c
	avr-objcopy -O ihex -R .eeprom main.bin main.hex

flash:
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:main.hex

clean:
	rm -f *.o *.bin

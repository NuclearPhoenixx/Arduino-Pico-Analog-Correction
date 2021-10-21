/*
	Arduino Pico Analog Correction
	https://github.com/Phoenix1747/Arduino-Pico-Analog-Correction/
*/

#include "PicoAnalogCorrection.h"


PicoAnalogCorrection::PicoAnalogCorrection(int offset) {
	_offset = offset;
}

int PicoAnalogCorrection::getOffset(uint8_t pin, size_t avg_size) {
	float value = .0;
	
	for(size_t i = 0; i < avg_size; i++) {
		value += float(analogRead(pin));
	}
	
	return round(value/avg_size);
}

int PicoAnalogCorrection::analogRead(uint8_t pin) {
	digitalWrite(PS_PIN, HIGH); // Disable power-saving
	delayMicroseconds(2); // Cooldown, maybe useless?
	
	int value = ::analogRead(pin); // Use normal Arduino analogRead func
	
	digitalWrite(PS_PIN, LOW); // Re-enable power-saving
	
	return value;
}

int PicoAnalogCorrection::analogCRead(uint8_t pin, size_t avg_size) {
	float value = .0;
	
	for(size_t i = 0; i < avg_size; i++) {
		value += float(analogRead(pin) - _offset);
	}
	
	return round(value/avg_size);
}



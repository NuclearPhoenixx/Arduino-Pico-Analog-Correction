/*
	Arduino Pico Analog Correction
	https://github.com/Phoenix1747/Arduino-Pico-Analog-Correction/
*/

#ifndef PicoAnalogCorrection_H
#define PicoAnalogCorrection_H

#include "Arduino.h"


#define PS_PIN 23 // Power Save Pin, H to disable, L default

class PicoAnalogCorrection {
		private:
			int _offset;
			
		public:
			PicoAnalogCorrection(int offset=0);
			
			int getOffset(uint8_t pin, size_t avg_size=100);
			
			int analogRead(uint8_t pin);
			int analogCRead(uint8_t pin, size_t avg_size=1);
};
#endif

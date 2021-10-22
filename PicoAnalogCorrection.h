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
		int _gnd_offset, _vcc_offset;
		float _a, _d;
		
		void setCorrectionValues();
		
	public:
		PicoAnalogCorrection(int gnd_val=0, int vcc_val=0);
		
		void calibrateAdc(uint8_t gnd_pin, uint8_t vcc_pin, size_t avg_size=100);
		void returnCalibrationValues();
		
		int analogRead(uint8_t pin);
		int analogCRead(uint8_t pin, size_t avg_size=1);
};
#endif

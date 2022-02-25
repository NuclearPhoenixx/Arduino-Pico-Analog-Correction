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
		int _max_channel, _gnd_offset, _vcc_offset;
		float _a, _d;

		void setCorrectionValues();

	public:
		PicoAnalogCorrection(size_t adc_res=12, size_t gnd_val=0, size_t vcc_val=0);

		void calibrateAdc(size_t gnd_pin, size_t vcc_pin, size_t avg_size=100);
		void returnCalibrationValues();

		int analogRead(size_t pin);
		int analogCRead(size_t pin, size_t avg_size=1);
};
#endif

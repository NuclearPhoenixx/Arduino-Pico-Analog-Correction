/*
	Arduino Pico Analog Correction
	https://github.com/NuclearPhoenixx/Arduino-Pico-Analog-Correction/
*/

#include "PicoAnalogCorrection.h"


PicoAnalogCorrection::PicoAnalogCorrection(size_t adc_res, float vref) {
	_adc_init = false;
	_adc_res = adc_res;
	_max_channel = pow(2, adc_res) - 1;
	_gnd_offset = 0;
	_vcc_offset = 0;
	_vref = vref;
	setCorrectionValues();
}


PicoAnalogCorrection::PicoAnalogCorrection(size_t adc_res, size_t gnd_val, size_t vcc_val) {
	_adc_init = false;
	_adc_res = adc_res;
	_max_channel = pow(2, adc_res) - 1;
	_gnd_offset = gnd_val;
	_vcc_offset = vcc_val;
	_vref = 3.3;
	setCorrectionValues();
}


PicoAnalogCorrection::PicoAnalogCorrection(size_t adc_res, float vref, size_t gnd_val, size_t vcc_val) {
	_adc_init = false;
	_adc_res = adc_res;
	_max_channel = pow(2, adc_res) - 1;
	_vref = vref;
	_gnd_offset = gnd_val;
	_vcc_offset = vcc_val;
	setCorrectionValues();
}


void PicoAnalogCorrection::setCorrectionValues() {
	if(_vcc_offset == 0) {
		_a = 1.0;
	} else {
		_a = _max_channel / (_vcc_offset - _gnd_offset);
	}
	_d = - _a * _gnd_offset;
	return;
}


void PicoAnalogCorrection::calibrateAdc(size_t gnd_pin, size_t vcc_pin, size_t avg_size) {
	float gnd_value = .0;

	for(size_t i = 0; i < avg_size; i++) {
		gnd_value += float(analogRead(gnd_pin));
	}
	_gnd_offset = gnd_value/avg_size;

	float vcc_value = .0;

	for(size_t i = 0; i < avg_size; i++) {
		vcc_value += float(analogRead(vcc_pin));
	}
	_vcc_offset = vcc_value/avg_size;

	setCorrectionValues();
	return;
}


void PicoAnalogCorrection::returnCalibrationValues() {
	Serial.println("(" + String(_gnd_offset) + ", " + String(_vcc_offset) + ")");
	return;
}


void PicoAnalogCorrection::analogReadResolution(size_t adc_res) {
	_adc_res = adc_res;
	::analogReadResolution(adc_res);
}


int PicoAnalogCorrection::analogRead(size_t pin) {
	digitalWrite(PS_PIN, HIGH); // Disable power-saving
	//delayMicroseconds(2); // Cooldown for the converter to stabilize?

	int value = ::analogRead(pin); // Use normal Arduino analogRead func

	digitalWrite(PS_PIN, LOW); // Re-enable power-saving

	return value;
}


int PicoAnalogCorrection::analogCRead(size_t pin, size_t avg_size) {
	float value = .0;

	for(size_t i = 0; i < avg_size; i++) {
		//value += float( map(analogRead(pin), _gnd_offset, _vcc_offset, 0, _max_channel) );
		value += float( _a * analogRead(pin) + _d );
	}

	return round(value/avg_size);
}


float PicoAnalogCorrection::analogReadTemp(pactemp_t type) {
	if (!_adc_init) {
		adc_init();
		_adc_init = true;
	}
	adc_set_temp_sensor_enabled(true);
	delay(1); // Allow things to settle.  Without this, readings can be erratic
	adc_select_input(4); // Temperature sensor is analog pin 4
	int v = adc_read();
	adc_set_temp_sensor_enabled(false);
	float t = 27.0f - ((v * _vref / pow(2, _adc_res)) - 0.706f) / 0.001721f; // From the datasheet with custom values for ADC res and Vref voltage
	
	if (type == PAC_F) {
		return t * 1.8f + 32.0f;
	} else {
		return t;
	}
}

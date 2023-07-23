/*
 * Analog Correction For Raspberry Pi Pico
 * https://github.com/NuclearPhoenixx/Arduino-Pico-Analog-Correction
 *
 * Connect A1 to GND and A0 to VCC (3.3V), then
 * upload this sketch and restart the Pico.
 * The connections should be as short as possible!
 * Your calibration values will be printed to the
 * Serial Monitor. Paste them into the
 * PicoAnalogCorrection constructor and you're done.
 *
 * You can also define a custom ADC resolution.
 * You can also read the correct temp from the sensor using the Vref value.
 *
 * MIT, 2022, NuclearPhoenix
 */

#include <PicoAnalogCorrection.h>

const uint8_t GND_PIN = A1;  // GND meas pin
const uint8_t VCC_PIN = A0;  // VCC meas pin
const uint8_t ADC_RES = 12;  // ADC bits
const float VREF = 3.0;      // Analog reference voltage

PicoAnalogCorrection pico(ADC_RES, VREF);

void setup() {
  pinMode(GND_PIN, INPUT);
  pinMode(VCC_PIN, INPUT);

  analogReadResolution(ADC_RES);

  // Needs to be called only if ADC_RES changes after the initial declaration of PicoAnalogCorrection.
  // You can also use this method instead of the stock analogReadResolution() version if you want to change the
  // resolution on the go. This will automatically call analogReadResolution(ADC_RES) too.
  // pico.analogReadResolution(ADC_RES);

  // Calibrate ADC using an average of 5000 measurements
  pico.calibrateAdc(GND_PIN, VCC_PIN, 5000);

  Serial.begin();

  while (!Serial) {
    ;  // Wait for Serial
  }
}

void setup1() {
}

void loop() {
  Serial.print("Offset Values: ");
  pico.returnCalibrationValues();

  Serial.print("Uncalibrated GND: ");
  Serial.println(pico.analogRead(GND_PIN));
  Serial.print("Calibrated GND: ");
  Serial.println(pico.analogCRead(GND_PIN, 10));

  Serial.print("Uncalibrated VCC: ");
  Serial.println(pico.analogRead(VCC_PIN));
  Serial.print("Calibrated VCC: ");
  Serial.println(pico.analogCRead(VCC_PIN, 10));
  Serial.println();

  Serial.print("Temperature (C): ");
  Serial.println(pico.analogReadTemp());
  Serial.print("Temperature (F): ");
  Serial.println(pico.analogReadTemp(PAC_F));
  Serial.println();

  delay(1000);
}

void loop1() {
}

/*
 * Analog Correction For Raspberry Pi Pico
 * https://github.com/Phoenix1747/Arduino-Pico-Analog-Correction
 *
 * Connect A1 to GND and A0 to VCC (3.3V), then
 * upload this sketch and restart the Pico.
 * The connections should be as short as possible!
 * Your calibration values will be printed to the
 * Serial Monitor. Paste them into the
 * PicoAnalogCorrection constructor and you're done.
 *
 * MIT, 2021, Phoenix1747
 */

#include <PicoAnalogCorrection.h>

const uint8_t GND_PIN = A1; // GND meas pin
const uint8_t VCC_PIN = A0; // VCC meas pin

PicoAnalogCorrection pico;

void setup() {
  pinMode(GND_PIN, INPUT);
  pinMode(VCC_PIN, INPUT);

  analogReadResolution(12); // 12-bit ADC, 4096 channels

  // Calibrate ADC using an average of 5000 measurements
  pico.calibrateAdc(GND_PIN, VCC_PIN, 5000);

  Serial.begin();

  while(!Serial) {
    ; // Wait for Serial
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
  Serial.println(pico.analogCRead(GND_PIN,10));

  Serial.print("Uncalibrated VCC: ");
  Serial.println(pico.analogRead(VCC_PIN));
  Serial.print("Calibrated VCC: ");
  Serial.println(pico.analogCRead(VCC_PIN,10));
  Serial.println();

  delay(1000);
}

void loop1() {
}

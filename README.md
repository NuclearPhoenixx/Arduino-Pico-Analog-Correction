# Arduino-Pico-Analog-Correction

![latest version](https://img.shields.io/github/release/Phoenix1747/Arduino-Pico-Analog-Correction.svg?style=for-the-badge) ![issues](https://img.shields.io/github/issues/Phoenix1747/Arduino-Pico-Analog-Correction.svg?style=for-the-badge) ![open pr](https://img.shields.io/github/issues-pr-raw/phoenix1747/Arduino-Pico-Analog-Correction.svg?style=for-the-badge)

Arduino library to calibrate and improve ADC measurements with the Raspberry Pi Pico. Can compensate ADC offsets, take arbitrary average measurements and temporarily disables the power-saving mode when analog-reading to improve the power supply ripple and noise.

This library is also available in the Arduino IDE, see [Arduino Library List](https://www.arduinolibraries.info/libraries/pico-analog-correction).

## Using

You can use the [example calibration sketch](examples/SimpleCalibration) to grab the calibration values, just follow the instructions given in the sketch.

You can serial print the calibration values anytime using this command:

```cpp
void returnCalibrationValues();
```

Other than that, you can take non-calibrated and calibrated measurements using the corresponding functions:

```cpp
int analogRead(uint8_t pin);
int analogCRead(uint8_t pin, size_t avg_size=1);
```

Both of these temporarily disable the power-saving mode to improve noise. Only the second function allows for taking arbitrarily large average measurements while also using the linear calibration.

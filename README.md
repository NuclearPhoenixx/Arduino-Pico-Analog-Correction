# Arduino-Pico-Analog-Correction

![latest version](https://img.shields.io/github/release/Phoenix1747/Arduino-Pico-Analog-Correction.svg?style=for-the-badge) ![issues](https://img.shields.io/github/issues/Phoenix1747/Arduino-Pico-Analog-Correction.svg?style=for-the-badge) ![open pr](https://img.shields.io/github/issues-pr-raw/phoenix1747/Arduino-Pico-Analog-Correction.svg?style=for-the-badge)

Arduino library to calibrate and improve ADC measurements with the Raspberry Pi Pico. Can compensate ADC offsets, calculate the arithmetic mean of any number of measurements and temporarily disable the power-saving mode when analog-reading to improve the power supply ripple and noise.

This library is also available in the Arduino IDE, see [Arduino Library List](https://www.arduinolibraries.info/libraries/pico-analog-correction).

## Using

You can use the [example calibration sketch](examples/SimpleCalibration) to grab the calibration values, just follow the instructions given in the sketch.

You can serial print the calibration values anytime using this command:

```cpp
void returnCalibrationValues();
```

Other than that, you can take non-calibrated and calibrated measurements using the corresponding functions:

```cpp
int analogRead(size_t pin);
int analogCRead(size_t pin, size_t avg_size=1);
```

Both of these temporarily disable the power-saving mode to improve noise. Only the second function allows taking an arbitrary number of measurements and returning the arithmetic mean while also using the linear calibration.

## Limitation

This library is limited to a very simple linear calibration since there are practically only two trusted voltages available to be measured: GND (0V) and VCC (3.3V). This means that the calibration will ensure that the ADC measures GND as 0 and VCC as 4095 with any value in between beeing distributed linearly within these two.

In addition, as the very helpful [Raspberry Pi Pico datasheet](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf) suggests, the on-board power supply noise and accuracy are not the best. To get the best results possible, you need to use an external voltage reference. This, however, introduces additonal drawbacks.

(Temporarily) Disabling the power-saving mode of the regulator is therefore a must-have to significantly reduce ripple on the ADC supply and is exactly what this library does independently from the calibration.

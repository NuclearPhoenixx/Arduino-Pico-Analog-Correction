# Arduino-Pico-Analog-Correction

![arduino-library-badge](https://www.ardu-badge.com/badge/PicoAnalogCorrection.svg?) ![latest version](https://img.shields.io/github/release/NuclearPhoenixx/Arduino-Pico-Analog-Correction.svg?) ![issues](https://img.shields.io/github/issues/NuclearPhoenixx/Arduino-Pico-Analog-Correction.svg?) ![open pr](https://img.shields.io/github/issues-pr-raw/NuclearPhoenixx/Arduino-Pico-Analog-Correction.svg?)

Arduino library to calibrate and improve ADC measurements with the Raspberry Pi Pico. Can compensate ADC offsets, calculate the arithmetic mean of any number of measurements and temporarily disable the power-saving mode when analog-reading to improve the power supply ripple and noise.
There is also a function for reading the temperature sensor depending on your ADC resolution and reference voltage.

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

You can also read the correct temperature from the temp sensor, even if you're not using the default resolution and reference voltage. Be sure that you supply the constructor with the correct values, then simply call:

```cpp
float analogReadTempCorrect();
```

This defaults to Celsius, you can also print Fahrenheit:

```cpp
float analogReadTempCorrect(PAC_F);
```

## Limitations

This library is limited to a very simple linear calibration since there are practically only two trusted voltages available to be measured: GND (0V) and VCC (3.3V). This means that the calibration will ensure that the ADC measures GND as 0 and VCC as the maximum channel number (depending on your resolution, e.g. 4095) with any value in between being distributed linearly within these two.

In addition, as the very helpful [Raspberry Pi Pico datasheet](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf) suggests, the on-board power supply noise and accuracy are not the best. To get the best results possible, you need to use an external voltage reference. This, however, introduces additonal drawbacks.

(Temporarily) Disabling the power-saving mode of the regulator is therefore a must-have to significantly reduce ripple on the ADC supply and is exactly what this library does independently from the calibration.

More info about the Pico's ADC can be found [on this website](https://pico-adc.markomo.me/) by [@ferret-guy](https://github.com/ferret-guy), who did extensive testing to find out the exact specifications.

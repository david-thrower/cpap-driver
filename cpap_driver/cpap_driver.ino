
/*
    bmp280_example.ino
    Example sketch for BMP280
    Copyright (c) 2016 seeed technology inc.
    Website    : www.seeedstudio.com
    Author     : Lambor, CHN
    Create Time:
    Change Log :
    The MIT License (MIT)
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/
#include "Seeed_BMP280.h"
#include <Wire.h>

BMP280 bmp280;

void setup() {
    Serial.begin(9600);
    if (!bmp280.init()) {
        Serial.println("Device not connected or broken!");
    }
  pinMode(9,OUTPUT);
}

float normal_pressure = 1034.9;
int pump_pwm_level = 20;

void loop() {


    float pressure;

    //get and print temperatures
    Serial.print("Temp: ");
    Serial.print(bmp280.getTemperature());
    Serial.println("C"); // The unit for  Celsius because original arduino don't support speical symbols

    //get and print atmospheric pressure data
    Serial.print("Pressure: ");
    pressure = bmp280.getPressure() * 0.010197162129779; // pressure converted to CmH20
    Serial.print(pressure);
    Serial.println("InH2O");

    if (pressure > normal_pressure + 20) {
      pump_pwm_level -= 10;
      }
    if (pressure < normal_pressure + 20) {
      pump_pwm_level += 10;
      }
    if (pump_pwm_level < 20) {
      pump_pwm_level = 20;
      }
    if (pump_pwm_level > 255) {
      pump_pwm_level = 255;
      }

    Serial.print(pump_pwm_level);
    analogWrite(9,pump_pwm_level);

    //get and print altitude data
//    Serial.print("Altitude: ");
//    Serial.print(bmp280.calcAltitude(pressure));
// Serial.println("m");

    Serial.print("\n");//add a line between output of different times.

    delay(1000);
}

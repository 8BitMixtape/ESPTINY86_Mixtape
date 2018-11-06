/*
  neo pixel test

  This example uses the NeoPixelBus library instead of the Adafruit library.

  At the moment the Adafruit library does not work with 160MHz ESP8266 setup.
  The NeoPixelBus library works but violates Arduino naming conventions like

  neoPixel.Begin // NeoPixelBus: wrong
  neoPixel.begin // Adafruit NeoPixel: right

  Please install the  library first!
  https://github.com/Makuna/NeoPixelBus

  ************************************************************************
  This sketch is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  ********************* list of outhors **********************************

  v0.1   6. November 2018  ChrisMicro  initial version

*/

#include <Arduino.h>
#include "ESP8266WiFi.h"
#include <i2s.h>
#include <i2s_reg.h>
#include <NeoPixelBus.h>

#define BBC_LED             D6 // low active
#define BBC_NEOPIXELPIN     D7
#define BBC_NEOPIXELNUMLEDS 8

//declare
NeoPixelBus<NeoRgbFeature, NeoEsp8266BitBang400KbpsMethod> neoPixel(BBC_NEOPIXELNUMLEDS, BBC_NEOPIXELPIN);

void setup()
{
  WiFi.forceSleepBegin(); // turn of wifi to reduce power consumption
  delay(1);
  system_update_cpu_freq(160); // run MCU core with full speed

  //setup
  neoPixel.Begin();
}

void loop()
{
  static int pixelNumber = 0; // 
  pixelNumber++;
  if (pixelNumber > BBC_NEOPIXELNUMLEDS)pixelNumber = 0;

  RgbColor red(10, 0, 0);
  RgbColor dark(0, 0, 0);
  //update
  neoPixel.SetPixelColor(pixelNumber, red);
  neoPixel.Show();

  delay(100);
  neoPixel.SetPixelColor(pixelNumber, dark);
  neoPixel.Show();

}

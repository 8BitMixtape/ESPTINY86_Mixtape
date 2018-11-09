/*
  neo pixel test

  This example uses the Adafruit library.

  Important:
  !! setup CPUFrequency in Arduino IDE firtst !!
  !! Tools=>CPUFrequency=160MHz               !!

  Please install the  library first.
  

  ************************************************************************
  This sketch is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  ********************* list of outhors **********************************

  v0.1   6. November 2018  ChrisMicro  initial version NeoPixelBus library
  v0.2   7. November 2018  ChrisMicro  changed to Adafruit_NeoPixel library
*/


#include <Arduino.h>
#include "ESP8266WiFi.h"
#include <Adafruit_NeoPixel.h>

#define LED             D6 // low active
#define NEOPIXELPIN     D7
#define NEOPIXELNUMLEDS 8


Adafruit_NeoPixel neoPixel = Adafruit_NeoPixel(NEOPIXELNUMLEDS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  WiFi.forceSleepBegin(); // turn of wifi to reduce power consumption
  delay(1);
  system_update_cpu_freq(160); // run MCU core with full speed

  neoPixel.begin();
}

void loop()
{
  static int pixelNumber = 0; 
  
  pixelNumber++;
  if (pixelNumber > NEOPIXELNUMLEDS)pixelNumber = 0;

  uint32_t red=neoPixel.Color(10,0,0);
  uint32_t dark=neoPixel.Color(0,0,0);
  
  //update
  neoPixel.setPixelColor(pixelNumber, red);
  neoPixel.show();

  delay(100);
  neoPixel.setPixelColor(pixelNumber, dark);
  neoPixel.show();

}

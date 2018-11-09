/*
  sound and neopixel

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

  v0.1   9. November 2018  ChrisMicro  initial version NeoPixelBus library

*/

#include "neolib.h"
#include "synthx.h"


Adafruit_NeoPixel neoPixel = Adafruit_NeoPixel(NEOPIXELNUMLEDS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);
SynthTest mysynth;

I2SClass I2S;

#define SAMPLINGFREQUENCY 44100

void slowLoop()
{
  mysynth.param[0].setValue(getPoti(POTI_LEFT));
  mysynth.param[1].setValue(getPoti(POTI_RIGHT));
  mysynth.param[2].setValue(getPoti(POTI_LEFT_UNDER));
  mysynth.param[3].setValue(getPoti(POTI_RIGHT_UNDER));
}

void ICACHE_RAM_ATTR updateSound()
{
  static int16_t cycle = 0;

  while (!i2s_is_full())
  {
    static int16_t dacValue;
    // stereo output
    dacValue = (int32_t)mysynth.run(cycle++) - 0x8000; //convert unsigned with offset to zero line centered signed
    I2S.write(dacValue, dacValue);
  }
}

void setup()
{
  WiFi.forceSleepBegin(); // turn of wifi to reduce power consumption
  delay(1);
  system_update_cpu_freq(160); // run MCU core with full speed

  neoPixel.begin();
  neoPixel.setBrightness(BRIGHTNESS);

    // PT8211 needs I2S_LEFT_JUSTIFIED_MODE
  I2S.begin(I2S_LEFT_JUSTIFIED_MODE, SAMPLINGFREQUENCY, 16);
  I2S.onTransmit(updateSound);
  neobegin();
}

void wait_ms(int milliSeconds)
{
  for(int n=0;n<milliSeconds;n++)
  {
    updateNeolib();
    slowLoop();
    delay(1);
  }
}

void loop()
{
  static int pixelNumber = 0; 
  
  pixelNumber++;
  if (pixelNumber > NEOPIXELNUMLEDS)pixelNumber = 0;
  
  //update
  neoPixel.setPixelColor(pixelNumber, COLOR_GREEN);
  neoPixel.show();

  wait_ms(100);
  neoPixel.setPixelColor(pixelNumber, COLOR_BLACK);
  neoPixel.show();
}

/*
  basic sound generation


  ************************************************************************
  This sketch is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  ********************* list of authors **********************************


  v0.5   8.November 2018 ChrisMicro initial version

  It is mandatory to keep the list of authors in this code.
  Please add your name if you improve/extend something

*/

#include "neolib.h"
//#include "I2S.h"
#include "synthx.h"
//#include <Adafruit_NeoPixel.h> 

Adafruit_NeoPixel neoPixel = Adafruit_NeoPixel(NEOPIXELNUMLEDS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);
//I2SClass I2S;

#define SAMPLINGFREQUENCY 44100

SynthTest mysynth;

void toggleLed(uint8_t pin)
{
  static boolean flag;
  flag ^= 1;
  digitalWrite(pin, flag);
}

void slowLoop()
{
  mysynth.param[0].setValue(getPoti(POTI_LEFT));
  mysynth.param[1].setValue(getPoti(POTI_RIGHT));
  mysynth.param[2].setValue(getPoti(POTI_LEFT_UNDER));
  mysynth.param[3].setValue(getPoti(POTI_RIGHT_UNDER));
}
/*

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
  updateNeolib();
  slowLoop();

}
*/
#define CPUFREQUENCY 160



void setup()
{
  WiFi.forceSleepBegin(); // turn of wifi to reduce power consumption
  delay(1);
  system_update_cpu_freq(CPUFREQUENCY); // run MCU core with full speed

  // PT8211 needs I2S_LEFT_JUSTIFIED_MODE
  //I2S.begin(I2S_LEFT_JUSTIFIED_MODE, SAMPLINGFREQUENCY, 16);
  //I2S.onTransmit(updateSound);
  //Serial.begin(115200);
  //neobegin();
  //pinMode(LED, OUTPUT);

  neoPixel.begin();
}


//******************************************************************************

#define LEDDELAY_MS 100

void testNeoPixel()
{
  uint32_t red = neoPixel.Color(10, 0, 0);
  uint32_t dark = neoPixel.Color(0, 0, 0);

  for (int n = 0; n < NEOPIXELNUMLEDS; n++)
  {
    neoPixel.setPixelColor(n, red);
    neoPixel.show();
    delay(LEDDELAY_MS);

    neoPixel.setPixelColor(n, dark);
    neoPixel.show();
    delay(LEDDELAY_MS);
  }
}

void loop()
{
  testNeoPixel();

  //toggleLed(LED);

}






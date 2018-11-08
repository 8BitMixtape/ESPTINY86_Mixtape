/*
  basic sound generation


  ************************************************************************
  This sketch is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  ********************* list of outhors **********************************


  v0.5   8.November 2018  initial version

  It is mandatory to keep the list of authors in this code.
  Please add your name if you improve/extend something

*/

#include "hardwarePlatform.h"
#include "I2S.h"
#include "synthx.h"

I2SClass I2S;

#define SAMPLINGFREQUENCY 44100

SynthTest mysynth;


#define UPDATERATE_MS 1

void updateSound()
{
  static int16_t cycle = 0;
  uint32_t count = 0;
  
  count = SAMPLINGFREQUENCY / 1000 * UPDATERATE_MS; // approximatelly 1ms
  for (int n = 0; n < count; n++)
  {
    int16_t dacValue;
    dacValue = (int32_t)mysynth.run(cycle++) - 0x8000; //convert unsigned with offset to zero line centered signed
    // stereo output
    I2S.write(dacValue, dacValue);
  }
}

#define CPUFREQUENCY 160

void setup()
{
  WiFi.forceSleepBegin(); // turn of wifi to reduce power consumption
  delay(1);
  system_update_cpu_freq(CPUFREQUENCY); // run MCU core with full speed

  // PT8211 needs I2S_LEFT_JUSTIFIED_MODE
  I2S.begin(I2S_LEFT_JUSTIFIED_MODE, SAMPLINGFREQUENCY, 16);

  //Serial.begin(115200);
}


void loop()
{
  updateSound();

}





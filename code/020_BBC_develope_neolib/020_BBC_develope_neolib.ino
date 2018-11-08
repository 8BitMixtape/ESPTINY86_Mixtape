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
#include "I2S.h"
#include "synthx.h"

I2SClass I2S;

#define SAMPLINGFREQUENCY 44100

SynthTest mysynth;

#define UPDATERATE_MS 5
#define NUMBERFASTUPDATES (SAMPLINGFREQUENCY / 1000 * UPDATERATE_MS) // approximatelly 1ms

void updateSound()
{
  static int16_t cycle = 0;

  for (int n = 0; n < NUMBERFASTUPDATES; n++)
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
  neobegin();
}

void slowLoop()
{
  mysynth.param[0].setValue(getPoti(POTI_LEFT));
  mysynth.param[1].setValue(getPoti(POTI_RIGHT));
  mysynth.param[2].setValue(getPoti(POTI_LEFT_UNDER));
  mysynth.param[3].setValue(getPoti(POTI_RIGHT_UNDER));
}

void loop()
{
  for(int n=0;n<10;n++)
  {
    // millisecond loops
    updateSound();
    updateNeolib();
  }
  slowLoop();
}





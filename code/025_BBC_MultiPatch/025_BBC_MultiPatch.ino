/*
  sound and neopixel and buttons

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

// various synthesizer patches
#include "synthx.h"
#include "SynthPatch1.h"


Adafruit_NeoPixel neoPixel = Adafruit_NeoPixel(NEOPIXELNUMLEDS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);
SynthTest   patch0;
SynthPatch1 patch1;

I2SClass I2S;

#define SAMPLINGFREQUENCY 44100

volatile uint8_t SelectedSynth = 0;
volatile uint32_t Amplitude = 1;

//************* I2S sound generator call back ( time critical ************************************
void ICACHE_RAM_ATTR updateSound()
{
  static int16_t cycle = 0;
  int16_t value;
  int16_t dacLeft, dacRight;
  if (SelectedSynth == 0)
  {
    while (!i2s_is_full())
    {
      //get new synthesizer sample and
      //convert to zero line centered signed value
      value = (int32_t)patch0.run(cycle++) - 0x8000;

      dacLeft = value;
      dacRight = value;

      // stereo output
      I2S.write(dacLeft, dacRight);
    }

    // sample potis and scan button states
    updateNeolib();

    // copy poti values to synthesizer
    patch0.param[0].setValue(getPoti(POTI_LEFT));
    patch0.param[1].setValue(getPoti(POTI_RIGHT));
    patch0.param[2].setValue(getPoti(POTI_LEFT_UNDER));
    patch0.param[3].setValue(getPoti(POTI_RIGHT_UNDER));
  }
  if (SelectedSynth)
  {
    while (!i2s_is_full())
    {
      //get new synthesizer sample and
      //convert to zero line centered signed value
      value = (int32_t)patch1.run(cycle++) - 0x8000;

      dacLeft = 0;
      dacRight = value * Amplitude;

      // stereo output
      I2S.write(dacLeft, dacRight);
    }

    // sample potis and scan button states
    updateNeolib();

    // copy poti values to synthesizer
    patch1.param[0].setValue(getPoti(POTI_LEFT)); // frequency
    patch1.param[1].setValue(getPoti(POTI_LEFT_UNDER)); // waveform
    patch1.param[2].setValue(getPoti(POTI_RIGHT));
    patch1.param[3].setValue(getPoti(POTI_RIGHT_UNDER));
  }
}
//***********************************************************************************************

void setup()
{
  //pointerToSynth=&synthPatch1;//mysynth;

  WiFi.forceSleepBegin(); // turn of wifi to reduce power consumption
  delay(1);
  system_update_cpu_freq(160); // run MCU core with full speed

  neoPixel.begin();
  neoPixel.setBrightness(BRIGHTNESS);

  /* i2s_mode

    I2S audio dacs from different manufacturers need dedicated setups.

    i2s mode                     DAC
    =========================    ============================
    I2S_PHILIPS_MODE             MAS98357a,UDA1334A
    I2S_RIGHT_JUSTIFIED_MODE,    PT8211
    I2S_PDM_MODE                 pulse density mode for direct RC-low
                                 pass connection at pin and no hardware DAC

  */
  I2S.begin(I2S_LEFT_JUSTIFIED_MODE, SAMPLINGFREQUENCY, 16);
  I2S.onTransmit(updateSound); // attache call back

  neobegin();
}

static int pixelNumber = 0;

// you can place your fast update functions here
void wait_ms(int milliSeconds)
{
  for (int n = 0; n < milliSeconds; n++)
  {

    if (getButton() == BUTTON_LEFT)  neoPixel.setPixelColor(pixelNumber, COLOR_GREEN);
    if (getButton() == BUTTON_RIGHT) neoPixel.setPixelColor(pixelNumber, COLOR_YELLOW);
    if (getButton() == BUTTON_LEFT + BUTTON_RIGHT) neoPixel.setPixelColor(pixelNumber, COLOR_PINK);

    if (wasButtonPressed() == BUTTON_LEFT)
    {
      toggleLed();
      SelectedSynth++;
      if (SelectedSynth > 2)SelectedSynth = 0;
    }
    delay(1);
  }
}

// just some basic example on how to read buttons and
// control the neoPixels

void loop()
{
  pixelNumber++;
  if (pixelNumber > NEOPIXELNUMLEDS-1)pixelNumber = 0;


  neoPixel.setPixelColor(pixelNumber, COLOR_BLUE);
  if (SelectedSynth == 2)
  {
    if (pixelNumber & 1)
    {
      Amplitude = 1;
      neoPixel.setPixelColor(pixelNumber, COLOR_RED);
    }
    else
    {
      Amplitude = 0;

    }
  }


  neoPixel.show();

  wait_ms(getPoti(POTI_RIGHT));

  neoPixel.setPixelColor(pixelNumber, COLOR_BLACK);
  neoPixel.show();
}

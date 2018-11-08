/*
  synthesizer with potis

  Due to the fact that the ESP8266 has only one ADC a external
  multiplexer ( CD4051 ) is used to get more ADC channels.
  The multiplexer selection channels are connected to the ESP-Pins.
  Pinout see definitions below in the code.

  This sketch uses the Eqation composer files originally from
  Microbe modular
  http://www.microbemodular.com/products/equation-composer

  ************************************************************************
  This sketch is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  ********************* list of outhors **********************************

  v0.1   24.August.2018   ChrisMicro  initial version
  v0.2   xxOctober 2018   badgeek, multiplexer moved to library
  v0.3   5.November.2018  ChrisMicro, I2S format addapted to PT8211 I2S DAC
  v0.4   6.November 2018  dusjagr adding NEO-pixel, PDM and serial
  v0.5   8.November 2018  stereo with Arduino compatible I2S and 2 synth opjects

  It is mandatory to keep the list of authors in this code.
  Please add your name if you improve/extend something

*/

#include "hardwarePlatform.h"
#include "AnalogMultiplexer.h"
#include "synthx.h" // change this for other synth patch
#include "I2S.h"


#include <Adafruit_NeoPixel.h>

I2SClass I2S;

#define BRIGHTNESS 30

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NEOPIXELNUMLEDS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);

byte neopix_gamma[] = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
  2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
  10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
  17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
  25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
  37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
  51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
  69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
  90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
  115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
  144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
  177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
  215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};

#define SAMPLINGFREQUENCY 44100

AnalogMultiplexerPin multiplexer;

SynthTest synthLeft;
SynthTest synthRight;

void setup()
{
  WiFi.forceSleepBegin(); // turn of wifi to reduce power consumption
  delay(1);
  system_update_cpu_freq(160); // run MCU core with full speed
  Serial.begin(115200);

  // PT8211 needs I2S_LEFT_JUSTIFIED_MODE
  I2S.begin(I2S_LEFT_JUSTIFIED_MODE, SAMPLINGFREQUENCY, 16);

  multiplexer.setup(MULTIPLEXER_PINA, MULTIPLEXER_PINB, MULTIPLEXER_PINC, ADC);

  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  pinMode(D6, OUTPUT);
  digitalWrite(D6, LOW); // turn on LED
  rainbowCycle (3);
}

void slowLoop()
{
  static uint8_t count = 0;
  if(count==POTI1)  synthLeft.param[0].setValue(multiplexer.read(count, 2));
  if(count==POTI2)  synthRight.param[0].setValue(multiplexer.read(count, 2)+10);
  if(count==POTI3)
  {
    uint16_t value=multiplexer.read(count, 2);
    synthLeft.param[1].setValue(value);
    synthRight.param[1].setValue(value); 
  }
  count++;
  if (count > 7) count = 0;
}

void loop()
{
  static int16_t cycle = 0;
  static uint16_t counter = 0;
  uint16_t left,right;

  left = (int32_t)synthLeft.run(cycle) - 0x8000;
  right = (int32_t)synthRight.run(cycle++) - 0x8000;

  // stereo output
  I2S.write(left,right);

  counter++;

  if (counter > SAMPLINGFREQUENCY / 250)
  {
    counter = 0;
    slowLoop();
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3, 0);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0, 0);
}

uint8_t red(uint32_t c) {
  return (c >> 16);
}
uint8_t green(uint32_t c) {
  return (c >> 8);
}
uint8_t blue(uint32_t c) {
  return (c);
}

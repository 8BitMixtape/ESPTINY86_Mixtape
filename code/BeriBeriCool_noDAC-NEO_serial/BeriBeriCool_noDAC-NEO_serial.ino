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

  v0.1   24.August.2018  ChrisMicro  initial version

  It is mandatory to keep the list of authors in this code.
  Please add your name if you improve/extend something

*/

#include <Arduino.h>
#include <i2s.h>
#include <i2s_reg.h>
#include "AnalogMultiplexer.h"
#include "synthx.h" // change this for other synth patch
#include "ESP8266WiFi.h" // wifi header only needed to turn it off
#include <Adafruit_NeoPixel.h> 

#define PIN D7

#define NUM_LEDS 8

#define BRIGHTNESS 30

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

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
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };


//#include <OSCMessage.h>
//#include <OSCBundle.h>
//#include <OSCData.h>

extern "C" {
#include "user_interface.h"
}


#define SAMPLINGFREQUENCY 44100

// multipexer select pins
#define MULTIPLEXED_ANALOG_INPUT A0
#define MUX_A D0
#define MUX_B D1
#define MUX_C D2

//PDM From Jan Ostman
uint32_t i2sACC;
uint16_t err;

AnalogMultiplexerPin multiplexer;

SynthTest mysynth;

void writeDAC(uint16_t DAC) {
  for (uint8_t i=0;i<32;i++) {
    i2sACC=i2sACC<<1;
    if(DAC >= err) {
      i2sACC|=1;
      err += 0xFFFF-DAC;
    } else {
      err -= DAC;
    }
  }
  bool flag=i2s_write_sample(i2sACC);
}


void setup()
{
  WiFi.forceSleepBegin(); // turn of wifi to reduce power consumption
  delay(1);
  system_update_cpu_freq(160); // run MCU core with full speed
  Serial.begin(230400);
  pinMode(2, INPUT); //restore GPIOs taken by i2s
  pinMode(15, INPUT);
  
  i2s_begin();
  i2s_set_rate(SAMPLINGFREQUENCY);

  // synthesizer input parameters
  // usually connected to potis
  // range: 0..1024
  // this parameters can be set on the fly in the slow loop

  multiplexer.setup(MUX_A, MUX_B, MUX_C, MULTIPLEXED_ANALOG_INPUT);
  
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  pinMode(D6, OUTPUT);
  digitalWrite(D6, LOW); // turn on LED
  //rainbowCycle (2);
}


void slowLoop()
{
  static uint8_t count = 0;
  mysynth.param[count].setValue(multiplexer.read(count,8));
  if(count==0) analogWrite (D6,1023 - (multiplexer.read(count,8)));
  
  Serial.print(multiplexer.read(count,8));
  Serial.print (" \t");
  
  if(count==6) {
    //Serial.println(multiplexer.read(count,8));
    //if(multiplexer.read(count,8)<300) rainbowCycle (1);
  }
  count++;
  if (count > 7) Serial.println();
  if (count > 7) count = 0;
  

}


void loop()
{
  static int16_t cycle = 0;
  static uint16_t counter = 0;
  uint16_t dacValue;

  dacValue = mysynth.run(cycle++);
  writeDAC(dacValue^0x8000);
  //i2s_write_sample(dacValue ^ 0x8000);

  counter++;

  if (counter > SAMPLINGFREQUENCY/250)
  {
    counter = 0;
    slowLoop();
  }


}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256 * 5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
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

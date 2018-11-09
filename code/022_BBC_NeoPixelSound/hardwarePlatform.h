/*
  BerryBerryCool platfomr pin definitions


  ************************************************************************
  This sketch is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  ********************* list of authors **********************************

  v0.1   7. November 2018  ChrisMicro  changed to Adafruit_NeoPixel library
*/

#include <Arduino.h>
#include "ESP8266WiFi.h"
#include "I2S.h"
#include <Adafruit_NeoPixel.h>

#define BRIGHTNESS 30

// BeriBeriCool pin definitions
#define LED               D6 // LED on Mixtape board, low active
#define NEOPIXELPIN       D7
#define NEOPIXELNUMLEDS   8
#define MULTIPLEXER_PINA  D0
#define MULTIPLEXER_PINB  D1
#define MULTIPLEXER_PINC  D2
#define I2S_DATA          RX
#define I2S_BCLK          D8
#define I2S_WS            D4
#define ADC               A0
#define BUTTONS_ADC       ADC

#define POTI_RIGHT         POTI2
#define POTI_LEFT          POTI1
#define POTI_RIGHT_UNDER   POTI4
#define POTI_LEFT_UNDER    POTI3

//MULTIPLEXER_CHANNEL
#define POTI1   0
#define POTI2   1
#define POTI3   2
#define POTI4   3
#define CV1     4
#define CV2     5
#define BUTTONS 6



/*
  neolib revival


  ************************************************************************
  This sketch is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  ********************* list of authors **********************************


  v0.x  16.03.2017 -H-A-B-E-R-E-R-  various routines to read the 8Bit Mixtape NEO
  v0.1   8.November 2018 ChrisMicro initial version

  It is mandatory to keep the list of authors in this code.
  Please add your name if you improve/extend something

*/

#include "neolib.h"

#define NUMBERMULTIPLEXERCHANNELS 6
uint16_t Multiplexervalues[NUMBERMULTIPLEXERCHANNELS];

void initMultiplexer()
{
  pinMode(MULTIPLEXER_PINA, OUTPUT);
  pinMode(MULTIPLEXER_PINB, OUTPUT);
  pinMode(MULTIPLEXER_PINC, OUTPUT);
}

void selectMultiplexer(uint8_t channel)
{
  digitalWrite(MULTIPLEXER_PINA, (channel & 1) != 0);
  digitalWrite(MULTIPLEXER_PINB, (channel & 2) != 0);
  digitalWrite(MULTIPLEXER_PINC, (channel & 4) != 0);
}

uint16_t analogReadScaled(uint8_t channel)
{
  uint16_t value = analogRead(channel);
  value = Multiplexervalues[channel];
  return value;
}

uint16_t getPoti(uint8_t channel)
{
  analogReadScaled(channel);
}

void updateNeolib()
{
  static uint8_t count = 0;
  selectMultiplexer(count);
  Multiplexervalues[count] = analogRead(ADC);
  count++;
  if (count > NUMBERMULTIPLEXERCHANNELS) count = 0;

}

void neobegin()
{
  //pinMode(SPEAKERPIN, OUTPUT);

  //pixels.begin();                                           // This initializes the NeoPixel library.
  //pixels.setBrightness(40);                                 // Woooowww!! They are sooo bright!
  initMultiplexer();
}



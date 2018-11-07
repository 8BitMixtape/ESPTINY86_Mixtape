/*
  test all

  Blinks all leds, reads potis to serial interface, makes sound.


  ************************************************************************
  This sketch is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  ********************* list of outhors **********************************


  v0.1   7. November 2018  ChrisMicro  changed to Adafruit_NeoPixel library
*/


#include "hardwarePlatform.h"
#include "I2S.h"


I2SClass I2S;


Adafruit_NeoPixel neoPixel = Adafruit_NeoPixel(NEOPIXELNUMLEDS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);


#define LEDDELAY_MS 100

//******************************************************************************
// BeryBeryCool on board led
void testLed(int repetitions)
{
  for (int n = 0; n < repetitions; n++)
  {
    digitalWrite(LED, LOW);
    delay(LEDDELAY_MS);
    digitalWrite(LED, HIGH);
    delay(LEDDELAY_MS);
  }
}

//******************************************************************************
// Wemos D1 mini on board led, probably not visible due to board orientation
// it is not working when I2S sound is active
void initLed_BUILTIN()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // led off ( led is low active )
}

void testLed_BUILTIN(int repetitions)
{
  for (int n = 0; n < repetitions; n++)
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(LEDDELAY_MS);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(LEDDELAY_MS);
  }
}

//******************************************************************************
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

//******************************************************************************
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

//******************************************************************************
void showAnalogChannels()
{
  selectMultiplexer(POTI1); Serial.print("POTI1: "); Serial.print(analogRead(ADC)); Serial.print("  ");
  selectMultiplexer(POTI2); Serial.print("POTI2: "); Serial.print(analogRead(ADC)); Serial.print("  ");
  selectMultiplexer(POTI3); Serial.print("POTI3: "); Serial.print(analogRead(ADC)); Serial.print("  ");
  selectMultiplexer(POTI4); Serial.print("POTI4: "); Serial.print(analogRead(ADC)); Serial.print("  ");
  selectMultiplexer(BUTTONS); Serial.print("BUTTON ADC: "); Serial.print(analogRead(ADC)); Serial.print("  ");
  Serial.println("");
}

//******************************************************************************
#define SAMPLINGFREQUENCY 44100

void initSound()
{
  // PT8211 needs I2S_LEFT_JUSTIFIED_MODE
  I2S.begin(I2S_LEFT_JUSTIFIED_MODE, SAMPLINGFREQUENCY, 16);
}

void endSound()
{
  I2S.end();
}

void testSound(uint8_t type)
{
  int16_t dacValue;

  for (int n = 0; n < SAMPLINGFREQUENCY / 5; n++)
  {
    dacValue = random(-32768, +32767);
    if (type == 0)I2S.write(dacValue, 0);
    if (type == 1)I2S.write(0, dacValue);
    if (type == 2)I2S.write(dacValue);
  }
}

//******************************************************************************

void setup()
{
  WiFi.forceSleepBegin(); // turn of wifi to reduce power consumption
  delay(1);
  system_update_cpu_freq(160); // run MCU core with full speed

  initLed_BUILTIN();

  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH); // led off ( led is low active )

  initMultiplexer();

  Serial.begin(115200);
  neoPixel.begin();

  initSound();
}

void loop()
{
  showAnalogChannels();

  testLed(5);

  testSound(0);

  showAnalogChannels();

  endSound();  // the I2S interface has to be stopped when using the LED_BUILTIN
  initLed_BUILTIN();
  testLed_BUILTIN(5);
  initSound(); // after LED_BUILTIN test turn on the sound again

  testSound(1);

  showAnalogChannels();

  testNeoPixel();
}

/*
  Button Test

  You can use this program to check the correct function of the buttons and
  buttons on your BeryBeryCool Mixtape.

  Hardware:
  The two buttons are connected to one analog channel of the multiplexer.
  There are different voltage levels is no-, left-, right- or both buttons are pressed.

  Read button channel and send them to the serial interface.
  You may want to use the serial plotter in the Arduino IDE to visuallize the poti values.

  Due to the fact that the ESP8266 has only one ADC a external
  multiplexer ( CD4051 ) is used to get more ADC channels.
  The multiplexer selection channels are connected to the ESP-Pins.
  Pinout see definitions below in the code.


  ************************************************************************
  This sketch is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  ********************* list of outhors **********************************

  The original version of the button algorithmen was develope for the 8BitMixtape
  and located in the _8Bit-Mixtape-NEO-Lib.

  v0.1   6.November 2018  ChrisMicro  initial version

  It is mandatory to keep the list of authors in this code.
  Please add your name if you improve/extend something

*/

// BeriBeriCool pin definitions
#define BBC_LED               D6 // LED on Mixtape board, low active
#define BBC_NEOPIXELPIN       D7
#define BBC_NEOPIXELNUMLEDS   8
#define BBC_MULTIPLEXER_PINA  D0
#define BBC_MULTIPLEXER_PINB  D1
#define BBC_MULTIPLEXER_PINC  D2
#define BBC_I2S_DATA          RX
#define BBC_I2S_BCLK          D8
#define BBC_I2S_WS            D4
#define BBC_ADC               A0
#define BUTTONS_ADC           BBC_ADC

#define MULTIPLEXER_CHANNEL_POTI1   0
#define MULTIPLEXER_CHANNEL_POTI2   1
#define MULTIPLEXER_CHANNEL_POTI3   2
#define MULTIPLEXER_CHANNEL_POTI4   3
#define MULTIPLEXER_CHANNEL_CV1     4
#define MULTIPLEXER_CHANNEL_CV2     5
#define MULTIPLEXER_CHANNEL_BUTTONS 6

#include <Arduino.h>
#include "ESP8266WiFi.h" // wifi header only needed to turn it off

void selectMultiplexer(uint8_t channel)
{
  digitalWrite(BBC_MULTIPLEXER_PINA, (channel & 1) != 0);
  digitalWrite(BBC_MULTIPLEXER_PINB, (channel & 2) != 0);
  digitalWrite(BBC_MULTIPLEXER_PINC, (channel & 4) != 0);
}

void setup()
{
  Serial.begin(115200);
  WiFi.forceSleepBegin(); // turn of wifi to reduce power consumption
  delay(1);
  system_update_cpu_freq(160); // run MCU core with full speed

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BBC_LED, OUTPUT);

  pinMode(BBC_MULTIPLEXER_PINA, OUTPUT);
  pinMode(BBC_MULTIPLEXER_PINB, OUTPUT);
  pinMode(BBC_MULTIPLEXER_PINC, OUTPUT);

  selectMultiplexer(MULTIPLEXER_CHANNEL_BUTTONS);
}

#define Vbutton_releaseLevel  800
#define Vbutton_left          700
#define Vbutton_right         420
#define Vbutton_both          300
#define Vbutton_pressedLevel Vbutton_left

#define BUTTON_NONE         0
#define BUTTON_LEFT         1
#define BUTTON_RIGHT        2

uint8_t getButton()
{
  uint8_t  button = BUTTON_NONE;
  uint16_t pinVoltage;

  pinVoltage = analogRead(BUTTONS_ADC);

  if ( pinVoltage < Vbutton_left  ) button = BUTTON_LEFT;
  if ( pinVoltage < Vbutton_right ) button = BUTTON_RIGHT;
  if ( pinVoltage < Vbutton_both  ) button = BUTTON_LEFT + BUTTON_RIGHT;

  return button;
}

/*
  uint8_t wasButtonPressed()

  returns the button which was pressed when the button is released.

  return values:

  BUTTON_LEFT
  BUTTON_RIGHT
  BUTTON_LEFT+BUTTON_RIGHT

  One of the most underestimated tasks is debouncing a button.
  This routine works in the most cases. It could be useful to
  add some time delay after the button is released to prevent
  bouncing.

  v0.1  16.03.2017 -H-A-B-E-R-E-R-  first version

*/

#define BUTTON_NOTPRESSED   0
#define BUTTON_PRESSED      1

uint8_t wasButtonPressed()
{
  static uint8_t buttonPressed    = false;
  static uint8_t buttonState      = 0;
  static uint8_t buttonValue      = BUTTON_NONE;
  static uint8_t buttonMaxValue   = 0;

  uint8_t        buttonReturnValue;
  uint16_t       pinVoltage;

  pinVoltage = analogRead( BUTTONS_ADC );

  // hysteresis switch
  if ( pinVoltage > Vbutton_releaseLevel ) buttonPressed = false;
  if ( pinVoltage < Vbutton_pressedLevel ) buttonPressed = true;

  buttonReturnValue = BUTTON_NONE;

  switch ( buttonState )
  {
    case BUTTON_NOTPRESSED:
      {
        buttonMaxValue = 0;

        if ( buttonPressed )
        {
          buttonState = BUTTON_PRESSED;
        }
      }; break;

    case BUTTON_PRESSED:
      {
        if ( buttonPressed ) // find minimum volage level during button pressed period
        {
          buttonValue = BUTTON_NONE;

          if ( pinVoltage < Vbutton_both  )      buttonValue = BUTTON_LEFT + BUTTON_RIGHT;
          else if ( pinVoltage < Vbutton_right ) buttonValue =               BUTTON_RIGHT;
          else if ( pinVoltage < Vbutton_left  ) buttonValue = BUTTON_LEFT               ;

          if ( buttonValue > buttonMaxValue ) buttonMaxValue = buttonValue;

        } else
        {
          buttonState = BUTTON_NOTPRESSED;
          buttonReturnValue = buttonMaxValue;
        }; break;
      }
  }
  return buttonReturnValue;
}

void loop()
{
  static uint8_t counter = 0;
  uint16_t value;

  uint8_t buttonState=wasButtonPressed();
  if ( buttonState== BUTTON_LEFT) counter++;
  if ( buttonState == BUTTON_RIGHT) counter--;
  Serial.print(counter); Serial.print(" ");

  value = analogRead(BBC_ADC);
  Serial.println(value);
  delay(10);

  value = getButton();
  if (value & BUTTON_RIGHT) digitalWrite(BBC_LED, LOW);
  else digitalWrite(BBC_LED, HIGH);
  if (value & BUTTON_LEFT) digitalWrite(LED_BUILTIN, LOW);
  else digitalWrite(LED_BUILTIN, HIGH);
}





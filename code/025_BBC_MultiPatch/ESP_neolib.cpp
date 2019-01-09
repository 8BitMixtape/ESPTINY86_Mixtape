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
volatile uint16_t Multiplexervalues[NUMBERMULTIPLEXERCHANNELS];
uint8_t ButtonWasPressedValue = BUTTON_NONE;


void toggleLed()
{
  static boolean flag;
  flag ^= 1;
  digitalWrite(LED, flag);
}

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
  uint16_t value;
  value = Multiplexervalues[channel];
  return value;
}

uint16_t getPoti(uint8_t channel)
{
  analogReadScaled(channel);
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
 
 v0.1  16.03.2017 first version 
 
*/

#define BUTTON_NOTPRESSED   0
#define BUTTON_PRESSED      1

void wasButtonPressedUpdate()
{
  static uint8_t buttonPressed    = false;
  static uint8_t buttonState      = 0;
  static uint8_t buttonValue      = BUTTON_NONE;
  static uint8_t buttonMaxValue   = 0;

  uint8_t        buttonReturnValue;  
  uint16_t       pinVoltage;
    
  //pinVoltage = analogRead( BUTTONS_ADC );
  pinVoltage = Multiplexervalues[BUTTONS];
  
  // hysteresis switch
  if( pinVoltage > Vbutton_releaseLevel ) buttonPressed = false;
  if( pinVoltage < Vbutton_pressedLevel ) buttonPressed = true;

  buttonReturnValue = BUTTON_NONE;
  
  switch( buttonState )
  {
    case BUTTON_NOTPRESSED:
    {
      buttonMaxValue = 0;      
      
      if( buttonPressed )
      {      
        buttonState = BUTTON_PRESSED;
      }
    };break;
    
    case BUTTON_PRESSED:
    {
      if( buttonPressed ) // find minimum volage level during button pressed period
      {
        buttonValue = BUTTON_NONE; 
        
             if ( pinVoltage < Vbutton_both  ) buttonValue = BUTTON_LEFT + BUTTON_RIGHT;
        else if ( pinVoltage < Vbutton_right ) buttonValue =               BUTTON_RIGHT;
        else if ( pinVoltage < Vbutton_left  ) buttonValue = BUTTON_LEFT               ;      
        
        if( buttonValue > buttonMaxValue ) buttonMaxValue = buttonValue;                                
      }else
      {
        buttonState = BUTTON_NOTPRESSED;
        buttonReturnValue = buttonMaxValue;
        
        ButtonWasPressedValue=buttonReturnValue; 
      }
      ;break;

    }
  }
  
  //return buttonReturnValue; 
}

uint8_t getButton()
{
  uint8_t  button = BUTTON_NONE;
  uint16_t pinVoltage;

  pinVoltage = Multiplexervalues[BUTTONS];

  if ( pinVoltage < Vbutton_left  ) button = BUTTON_LEFT;
  if ( pinVoltage < Vbutton_right ) button = BUTTON_RIGHT;
  if ( pinVoltage < Vbutton_both  ) button = BUTTON_LEFT + BUTTON_RIGHT;

  return button;
}

uint8_t wasButtonPressed()
{
  uint8_t buttonReturnValue;
  buttonReturnValue = ButtonWasPressedValue;
  ButtonWasPressedValue = BUTTON_NONE;
  return buttonReturnValue;
}

void updateNeolib()
{
  static uint8_t count = 0;

  Multiplexervalues[count] = analogRead(ADC);
  count++;
  if (count > NUMBERMULTIPLEXERCHANNELS) count = 0;

  selectMultiplexer(count);

  if(count==BUTTONS) wasButtonPressedUpdate();
}

void neobegin()
{
  pinMode(LED, OUTPUT);

  //pixels.begin();                                           // This initializes the NeoPixel library.
  //pixels.setBrightness(40);                                 // Woooowww!! They are sooo bright!
  initMultiplexer();
}



/*
  Blink for BeryBeryCool (BBC) Mixtape

  Turns the LEDs on, then off repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman
  modified 6 Nov 2018
  by ChrisMicro

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
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

// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BBC_LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() 
{
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on ( WEMOS D1 MINI LED is active low )
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED off 
  delay(1000);                      // wait for a second
  digitalWrite(BBC_LED, LOW);       // turn the LED on ( BBC Mixtape on board led is active low )
  delay(1000);                      // wait for a second
  digitalWrite(BBC_LED, HIGH);      // turn the LED off
  delay(1000);                      // wait for a second

}

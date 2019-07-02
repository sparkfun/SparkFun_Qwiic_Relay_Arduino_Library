/*
  The Qwiic Quad relay is a product with four channels for switching high AC voltge.
  This example code takes advantage of the SparkFun Qwiic Relay Arduino
  Library to control the relays. 
  By: Elias Santistevan
  SparkFun Electronics
  Date: July 2019

  License: This code is public domain but you buy me a beer if you use 
	this and we meet someday (Beerware license).

	This example attaches three buttons to three digital I/O pins. Each button
  completes a different action: that is turning on or off a relay. 

*/

#include <Wire.h>
#include "SparkFun_Qwiic_Relay.h"

#define RELAY_ADDR 0x6D

Qwiic_Relay quadRelay(RELAY_ADDR);


// Three buttons
const int yellow_btn = 2;
const int red_btn    = 3;
const int blue_btn   = 4;

void setup()
{
  Wire.begin(); 
  Serial.begin(115200);

  if(!quadRelay.begin())
    Serial.println("Check connections to Qwiic Relay.");
  else
    Serial.println("Ready to flip some switches.");

	//Use internal resitors to keep them in a known high state. 
  pinMode(yellow_btn, INPUT_PULLUP);
  pinMode(blue_btn, INPUT_PULLUP);
  pinMode(red_btn, INPUT_PULLUP);

}

void loop()
{
	// Button one turns on relay one....
  if(digitalRead(yellow_btn) == LOW){
		delay(400);
    quadRelay.turnRelayOn(1);
    Serial.println("Yellow Button");
  }

	// Button two turns on relay two....
  if(digitalRead(blue_btn) == LOW){
		delay(400);
    quadRelay.turnRelayOn(2);
    Serial.println("Blue Button");
  }

  // Button three turns off relay one and two...
  if(digitalRead(red_btn) == LOW){
		delay(400);
    quadRelay.turnRelayOff(1);
    quadRelay.turnRelayOff(2);
    Serial.println("Red Button");
  }

}

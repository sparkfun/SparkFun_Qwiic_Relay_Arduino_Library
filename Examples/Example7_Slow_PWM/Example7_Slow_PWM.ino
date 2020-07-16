/*
  This example code gives you all the functionality of the SparkFun Qwiic Quad Relay
  Arduino Library. It gives you the function to turn on and off each relay, toggle
  each relay, turn them all on and off, toggle them all, and how to check their
  state (on or off?). In general each function needs the number of the relay
  to activate.  
  By: Elias Santistevan
  SparkFun Electronics
  Date: July 2019

  License: This code is public domain but you buy me a beer if you use 
	this and we meet someday (Beerware license).
*/

#include <Wire.h>
#include "SparkFun_Qwiic_Relay.h"

#define RELAY_ADDR 0x08 // Alternate address 0x6C


Qwiic_Relay quadRelay(RELAY_ADDR); 

void setup()
{
  Wire.begin(); 
  Serial.begin(115200);
  
  // Let's make sure the hardware is set up correctly.
  if(!quadRelay.begin())
    Serial.println("Check connections to Qwiic Relay.");
  else
    Serial.println("Ready to flip some switches.");

  Serial.println("Let's turn each relay on, one at a time.");
  // To turn on a relay give the function the number you want to turn on (or
  // off).

 quadRelay.setSlowPWM(1, 75);
 quadRelay.setSlowPWM(2, 75);
 quadRelay.setSlowPWM(3, 75);
 quadRelay.setSlowPWM(4, 75);
 Serial.println(quadRelay.getSlowPWM(1));
 Serial.println(quadRelay.getSlowPWM(2));
 Serial.println(quadRelay.getSlowPWM(3));
 Serial.println(quadRelay.getSlowPWM(4));


}

void loop()
{
}

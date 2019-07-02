/*
  This example code gives you all the functionality of the SparkFun Qwiic Relay
  Arduino Library. It shows you how to get the firmware version of the board
  you're using, how to turn on and off a relay, toggle a relay, and get the
  status of the relay.
  By: Elias Santistevan
  SparkFun Electronics
  Date: July 2019

  License: This code is public domain but you buy me a beer if you use 
	this and we meet someday (Beerware license).
*/

#include <Wire.h>
#include "SparkFun_Qwiic_Relay.h"

#define RELAY_ADDR 0x18 // Alternate address 0x19


Qwiic_Relay relay(RELAY_ADDR); 

void setup()
{
  Wire.begin(); 
  Serial.begin(115200);
  
  // Let's see
  if(!relay.begin())
    Serial.println("Check connections to Qwiic Relay.");
  else
    Serial.println("Ready to flip some switches.");

  float version = relay.singleRelayVersion();
  Serial.print("Firmware Version: ");
  Serial.println(version);
 
  // Let's turn on the relay...
  relay.turnRelayOn(); 
  delay(500);
  // Let's turn that relay off...
  relay.turnRelayOff(); 
  delay(500);
  // Let's 'toggle' the relay; if it's off turn it on and vice versa.
  relay.toggleRelay(); 
  delay(500);
  // Toggle the relay back off.
  relay.toggleRelay();
  delay(500);
  
  Serial.print("The Relay is now: ");
  // Is the relay on or off?
  int state = relay.getState();
  if(state == 1)
    Serial.print("On!");
  else if(state == 0)
    Serial.print("Off!");

}

void loop()
{
}

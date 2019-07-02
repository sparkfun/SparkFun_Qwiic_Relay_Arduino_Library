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

#define RELAY_ADDR 0x6D // Alternate address 0x6C


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
  quadRelay.turnRelayOn(1); 
  delay(200);
  quadRelay.turnRelayOn(2); 
  delay(200);
  quadRelay.turnRelayOn(3); 
  delay(200);
  quadRelay.turnRelayOn(4); 
  delay(1000);

  // You can turn off all relays at once with the following function...
  Serial.println("Now let's turn them all off.");
  quadRelay.turnAllRelaysOff(); 
  delay(1000);

  // Toggle is a bit different then using the on and off functions. It will
  // check the current state of the relay (on or off) and turn it to it's
  // opposite state: on ---> off or off -----> on.
  Serial.println("Toggle relay one and two.");
  quadRelay.toggleRelay(1); 
  delay(200);
  quadRelay.toggleRelay(2); 
  delay(1000);

  // Let's turn off relay one and two....
  Serial.println("Turn off relay one and two.");
  quadRelay.turnRelayOff(1);
  delay(200);
  quadRelay.turnRelayOff(2);
  delay(1000);

  // You can turn all the relays on at once with this function.
  Serial.println("Turn them all on once again.");
  quadRelay.turnAllRelaysOn();
  delay(1000);

  // And finally you can toggle each relay at once. It's helpful when you have 
  // two relays on but need them off, and also need the other two relays on.
  Serial.println("....and turn them off again.");
  quadRelay.toggleAllRelays();
  
  // Finally we can see if the relays are on or off without physically looking
  // at them. Once again, give the function the number of the relay you want to
  // check.
  Serial.print("Relay One is now: ");
  // Is the relay on or off?
  int state = quadRelay.getState(1);
  if(state == 1)
    Serial.println("On!");
  else if(state == 0)
    Serial.println("Off!");
  delay(1000);
  
  // Turn on relay two just to get a sense of how this works.
  Serial.print("Relay two is now: ");
  quadRelay.turnRelayOn(2); 
  state = quadRelay.getState(2);
  if(state == 1)
    Serial.println("On!");
  else if(state == 0)
    Serial.println("Off!");
  
  Serial.println("Now they're all off...");
  // Show's over people...
  quadRelay.turnAllRelaysOff(); 

}

void loop()
{
}

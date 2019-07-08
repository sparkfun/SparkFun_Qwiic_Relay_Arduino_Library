/*
  This example code demonstrates how to change the address of the Single or
  Quad Qwiic Relay to one of your choosing. There is a set range of available
  addresses from 0x07 to 0x78, so make sure your chosen address falls within
  this range. The next thing to note is that when you change the address you'll
  need to call an instance of the Qwiic_Relay class that includes your new
  address: "Qwiic_Relay relay(YOUR_NEW_ADDRESS_HERE);" so that the new address
  is fed to all the available functions. Finally if for some reason you've
  forgotten your new address. No big deal, load up the I2C scanner example code
  and find out where your product's address is at. 
  By: Elias Santistevan
  SparkFun Electronics
  Date: July 2019

  License: This code is public domain but you buy me a beer if you use 
	this and we meet someday (Beerware license).
*/

#include <Wire.h>
#include "SparkFun_Qwiic_Relay.h"

// All available product addresses labeled below. Close the onboard jumpers if
// you want to access the alternate addresses. 
#define SINGLE_DEFAULT_ADDR 0x18 // Alternate jumper address 0x19
#define QUAD_DEFAULT_ADDR 0x6D // Alternate jumper address 0x6C


// After changing the address you'll need to apply that address to a new
// instance of the Qwiic_Relay class: "Qwiic_Relay relay(YOUR_NEW_ADDRESS_HERE)".
Qwiic_Relay relay(QUAD_DEFAULT_ADDR); // Change to Single Relay Address if using Quad Relay

void setup()
{
  Wire.begin(); 
  Serial.begin(115200);
  
  // Let's see.....
  if(relay.begin())
    Serial.println("Ready to flip some switches.");
  else
    Serial.println("Check connections to Qwiic Relay.");

  // There is a not so limited but still limited range of
  // addresses that are available to you 0x07 -> 0x78.
  if(relay.changeAddress(0x09)) // Put the address you want here. 
    Serial.println("Address changed successfully."); 
  else
    Serial.println("Address change failed...");
  
  delay(2000);

  
}

void loop()
{
}

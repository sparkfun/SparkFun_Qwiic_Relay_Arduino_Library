/*
Example 6 Change I2C Address

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
#define NEW_ADDR 0x09

// After changing the address you'll need to apply that address to a new
// instance of the Qwiic_Relay class: "Qwiic_Relay relay(YOUR_NEW_ADDRESS_HERE)".
Qwiic_Relay relay(QUAD_DEFAULT_ADDR); // Change to Single Relay Address if using single relay

void setup()
{
    Wire.begin(); 

    Serial.begin(115200);

    if(!relay.begin())
    {
        Serial.println("Can't communicate with Relay. Check wiring or that you have the correct I2C address.");
        while(1)
            ;
    }

    Serial.println("Example 6 Changing the relay's I2C address.");

    // There is a not so limited but still limited range of
    // addresses that are available to you 0x07 -> 0x78.

    // If you're using a single relay, indicate it by adding "true" as a second argument.
    //if(relay.changeAddress(NEW_ADDR, true) 

    if(relay.changeAddress(NEW_ADDR)) // Put the address you want here. 
        Serial.println("Address changed successfully."); 
    else
        Serial.println("Address change failed...");

    delay(2000);


}

void loop()
{
}

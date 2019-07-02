/*
  This example sketch uses interrupts to toggle two seperate relays on and off.
  By using interrupts we can do other things in code while two buttons are
  silently being monitored for presses in the background. This sketch takes
  advantage of the SparkFun Qwiic Relay Arduino Library. 
  By: Elias Santistevan
  SparkFun Electronics
  Date: July 2019

  License: This code is public domain but you buy me a beer if you use
  this and we meet someday (Beerware license).

*/
#include <Wire.h>
#include "SparkFun_Qwiic_Relay.h"

#define RELAY_ADDR 0x6D 

Qwiic_Relay quadRelay(RELAY_ADDR);

const int yellow_btn = 2;
const int blue_btn = 3;

volatile int yellowFlag = 0;
volatile int blueFlag = 0;

// This will keep track of the state of the relay that is on or off. 
volatile int yellowState = 0;
volatile int blueState = 0;

int relayState; 

void setup()
{
  Wire.begin(); 
  Serial.begin(115200);

  if(!quadRelay.begin())
    Serial.println("Check connections to Qwiic Relay.");
  else
    Serial.println("Ready to flip some switches.");

  pinMode(yellow_btn, INPUT_PULLUP);
  pinMode(blue_btn, INPUT_PULLUP);

  // Since we're using buttons, we want to see when the button goes from high,
  // to low. In other words, when the button is pressed. If I were using a
  // switch, then I would change the FALLING parameter, to LOW. 
  attachInterrupt(digitalPinToInterrupt(yellow_btn), turn_off_yellow, FALLING);
  attachInterrupt(digitalPinToInterrupt(blue_btn), turn_off_blue, FALLING);
  
}

void loop()
{
  // If the flag was tripped, then that means a button or switch was flipped.
  // The "state" tells us whether the relay is on or off. If one is flipped
  // than the other will be flipped to match. We then save the new 'state' of
  // the product.  
  if(yellowFlag != yellowState){
    yellowState = !yellowState; 
    Serial.println("Yellow Button");
    quadRelay.toggleRelay(1);

    Serial.print("Relay is now: "); 
    relayState = quadRelay.getState(2);
    if(relayState == 1)
      Serial.println("On");
    else if(relayState == 0)
      Serial.println("Off");
  }

  if(blueFlag != blueState){
    blueState = !blueState; 
    Serial.println("Blue Button");
    quadRelay.toggleRelay(2);

    Serial.print("Relay is now: "); 
    relayState = quadRelay.getState(2);
    if(relayState == 1)
      Serial.println("On");
    else if(relayState == 0)
      Serial.println("Off");
  }

}

// The following are interrupt service routine functions. Keep them super
// brief!
void turn_off_yellow()
{
  yellowFlag = !yellowFlag; 
}

void turn_off_blue()
{
  blueFlag = !blueFlag; 
}


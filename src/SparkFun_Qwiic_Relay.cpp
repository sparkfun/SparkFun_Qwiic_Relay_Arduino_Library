/*
  This is a library for both the Qwiic Single and Qwiic Quad Relay. It gives basic
  functionality for turning on and off your relays and getting their statuses. 
  By: Elias Santistevan
  Date: July 2019 
  License: This code is public domain but you buy me a beer if you use this and 
  we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
 */

#include "SparkFun_Qwiic_Relay.h"

Qwiic_Relay::Qwiic_Relay( uint8_t address ){  _address = address; } //Constructor for I-squared-C

bool Qwiic_Relay::begin( TwoWire &wirePort )
{
  
  _i2cPort = &wirePort;

  _i2cPort->beginTransmission(_address);
  uint8_t _ret = _i2cPort->endTransmission();
  if( !_ret )
    return true; 
  else 
    return false; 

}

//****----THE FOLLOWING FIVE FUNCTIONS ARE TO BE USED WITH THE SPARKFUN SINGLE RELAY-----****

// This function turns the single relay board on. 
void Qwiic_Relay::turnRelayOn()
{
  _writeCommandOn(TURN_RELAY_ON);
}

// This function turns the single relay board off. 
void Qwiic_Relay::turnRelayOff() 
{
  _writeCommandOff(TURN_RELAY_OFF);
}

// This function gives toggle functionality to the single relay. First the
// status of the relay is checked and is toggled according to what the status
// of the relay: on ---> off or off ----> on.
void Qwiic_Relay::toggleRelay()
{
  uint8_t status = _readCommand(STATUS);
  if (status == SING_RELAY_ON)
    turnRelayOff();
  else  
    turnRelayOn();
}

// This function for the SparkFun Single Relay, gets the status of the relay:
// whether on: 1 or off: 0;
uint8_t Qwiic_Relay::getState()
{
  uint8_t status =  _readCommand(STATUS);
  return status; 
}

// This function gets the version number of the SparkFun Single Relay.
float Qwiic_Relay::singleRelayVersion()
{
  float version = _readVersion(FIRMWARE_VERSION);
  return(version);
}

//*****----THE FOLLOWING FUNCTIONS ARE TO BE USED WITH THE SPARKFUN QUAD RELAY------*****
 
// This function turns the given relay on.
void Qwiic_Relay::turnRelayOn(uint8_t relay)
{
  _writeCommandOn(relay);
}

// This function turns the given relay off.
void Qwiic_Relay::turnRelayOff(uint8_t relay)
{
  _writeCommandOff(relay);
}

// This function toggles the given relay. If the relay is on then it will turn
// it off, and if it is off then it will turn it on. 
void Qwiic_Relay::toggleRelay(uint8_t relay)
{
  if (relay == RELAY_ONE)
    _writeCommandToggle(TOGGLE_RELAY_ONE);
  else if (relay == RELAY_TWO)
    _writeCommandToggle(TOGGLE_RELAY_TWO);
  else if (relay == RELAY_THREE)
    _writeCommandToggle(TOGGLE_RELAY_THREE);
  else if(relay == RELAY_FOUR)
    _writeCommandToggle(TOGGLE_RELAY_FOUR);
  else 
    return;
}

// This function for the SparkFun Quad Relay, turns on all relays on the
// board. 
void Qwiic_Relay::turnAllRelaysOn()
{
  _writeCommandOn(TURN_ALL_ON);
}

// This function for the SparkFun Quad Relay, turns off all relays on the
// board. 
void Qwiic_Relay::turnAllRelaysOff()
{
  _writeCommandOff(TURN_ALL_OFF);
}

// This function for the SparkFun Quad Relay, turns off all relays on the
// board. 
void Qwiic_Relay::toggleAllRelays()
{
  _writeCommandOn(TOGGLE_ALL);
}

// This function for the SparkFun Quad Relay, gets the status of the relay:
// whether on: 1 or off: 0;
uint8_t Qwiic_Relay::getState(uint8_t relay)
{

  uint8_t status; 
  if(relay == RELAY_ONE)
    status =  _readCommand(RELAY_ONE_STATUS);
  else if(relay == RELAY_TWO)
    status =  _readCommand(RELAY_TWO_STATUS);
  else if(relay == RELAY_THREE)
    status =  _readCommand(RELAY_THREE_STATUS);
  else if(relay == RELAY_FOUR)
    status =  _readCommand(RELAY_FOUR_STATUS);
  else
    return;
  
  if( status == QUAD_RELAY_ON ) // Relay status should be consistent
    return 1; // Relay on
  else
    return QUAD_RELAY_OFF;
}


// This function handles I-squared-C write commands for turning the relays on. 
// The quad relay relies on the current state of the relay to determine whether
// or not to turn the respective relay on (or off) and so the current state of
// the relay is checked before attempting to send a command. 
void Qwiic_Relay::_writeCommandOn(uint8_t _command)
{

  uint8_t _status; 
  if (_command == RELAY_ONE){
    _status = _readCommand(RELAY_ONE_STATUS);
    if( _status == QUAD_RELAY_ON ){ // Is it on? Then....
      return; // Do nothing....
    }
    else { // Off?
      _i2cPort->beginTransmission(_address); // Start communication.
      _i2cPort->write(TOGGLE_RELAY_ONE); // Toggle it on....
      _i2cPort->endTransmission(); // End communcation.
    }
  }
  // Repeat for relay two....
  else if (_command == RELAY_TWO){
    _status = _readCommand(RELAY_TWO_STATUS);
    if( _status == QUAD_RELAY_ON ){
      return;
    }
    else {
      _i2cPort->beginTransmission(_address);
      _i2cPort->write(TOGGLE_RELAY_TWO); 
      _i2cPort->endTransmission(); 
    }
  }
  // Relay three..
  else if (_command == RELAY_THREE){
    _status = _readCommand(RELAY_THREE_STATUS);
    if( _status == QUAD_RELAY_ON ){
      return;
    }
    else {
      _i2cPort->beginTransmission(_address); 
      _i2cPort->write(TOGGLE_RELAY_THREE);
      _i2cPort->endTransmission(); 
    }
  }
  // Relay four.... 
  else if (_command == RELAY_FOUR){
    _status = _readCommand(RELAY_FOUR_STATUS);
    if( _status == QUAD_RELAY_ON ){
      return;
    }
    else {
      _i2cPort->beginTransmission(_address);
      _i2cPort->write(TOGGLE_RELAY_FOUR);
      _i2cPort->endTransmission(); 
    }
  }
  // If it's not 1-4 then it must be for the single relay....
  else {
    _i2cPort->beginTransmission(_address);
    _i2cPort->write(_command);
    _i2cPort->endTransmission(); 
  }
     
}

// This function handles I-squared-C write commands for toggling the relays from their
// current state. If the relay is on then it will be turned off and vice versa. 
void Qwiic_Relay::_writeCommandToggle(uint8_t _command){

    _i2cPort->beginTransmission(_address);
    _i2cPort->write(_command);
    _i2cPort->endTransmission(); 

}

// This function handles I-squared-C write commands for turning the relays off. 
// The quad relay relies on the current state of the relay to determine whether
// or not to turn the respective relay off (or on) and so the current state of
// the relay is checked before attempting to toggle it.
void Qwiic_Relay::_writeCommandOff(uint8_t _command)
{

  uint8_t _status;
  if( _command == RELAY_ONE ){
    _status = _readCommand(RELAY_ONE_STATUS);
    if( _status == QUAD_RELAY_OFF ){ // Is the board off?
      return; // Do nothing...
    }
    else { // Then it must be on...
      _i2cPort->beginTransmission(_address); // Start communication.
      _i2cPort->write(TOGGLE_RELAY_ONE); // Toggle it off....
      _i2cPort->endTransmission(); // End communcation.
    }
  }
  // Repeat for relay two....
  else if( _command == RELAY_TWO ){
    _status = _readCommand(RELAY_TWO_STATUS);
    if( _status == QUAD_RELAY_OFF ){
      return;
    }
    else {
      _i2cPort->beginTransmission(_address); // Start communication.
      _i2cPort->write(TOGGLE_RELAY_TWO); 
      _i2cPort->endTransmission(); // End communcation.
    }
  }
  // Relay three...
  else if( _command == RELAY_THREE ){
    _status = _readCommand(RELAY_THREE_STATUS);
    if( _status == QUAD_RELAY_OFF ){
      return;
    }
    else {
      _i2cPort->beginTransmission(_address); // Start communication.
      _i2cPort->write(TOGGLE_RELAY_THREE);
      _i2cPort->endTransmission(); // End communcation.
    }
  }
  // Relay four....
  else if( _command == RELAY_FOUR ){
    _status = _readCommand(RELAY_FOUR_STATUS);
    if( _status == QUAD_RELAY_OFF ){
      return;
    }
    else {
      _i2cPort->beginTransmission(_address); // Start communication.
      _i2cPort->write(TOGGLE_RELAY_FOUR);
      _i2cPort->endTransmission(); // End communcation.
    }
  }
  // If it's not 1-4 then it must be for the single relay...
  else {
    _i2cPort->beginTransmission(_address);
    _i2cPort->write(_command);
    _i2cPort->endTransmission(); 
  }
     
}

// This function requests information from the product with a simple
// I-squared-C transaction.
uint8_t Qwiic_Relay::_readCommand(uint8_t _command)
{

  _i2cPort->beginTransmission(_address); 
  _i2cPort->write(_command);
  _i2cPort->endTransmission();

  _i2cPort->requestFrom(_address, 1);  
  uint8_t status = _i2cPort->read();
  return(status);

}

// The function reads thee version number of the Single Quad Relay.
float Qwiic_Relay::_readVersion(uint8_t _command)
{
  _i2cPort->beginTransmission(_address); 
  _i2cPort->write(_command); 
  _i2cPort->endTransmission();

  _i2cPort->requestFrom(_address, 2); 
  float _versValue = _i2cPort->read();
  _versValue += (float)_i2cPort->read() / 10.0 ;
  return(_versValue);
  
}


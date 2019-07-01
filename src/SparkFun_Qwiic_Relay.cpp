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

Qwiic_Relay::Qwiic_Relay( uint8_t address ){  _address = address; } //Constructor for I2C

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

//****----THE FOLLOWING FOUR FUNCTION ARE TO BE USED WITH THE SPARKFUN SINGLE RELAY-----****

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
    turnRelayOn();
  else  
    turnRelayOff();
}

// This function for the SparkFun Single Relay, gets the status of the relay:
// whether on: 1 or off: 0;
uint8_t Qwiic_Relay::getRelayStatus()
{
  uint8_t status =  _readCommand(STATUS);
  return status; 
}

// This function gets the version number of the SparkFun Single Relay.
float Qwiic_Relay::getSingleRelayVersion()
{
  float version = _readVersion(FIRMWARE_VERSION);
  return(version);
}

//*****----THE FOLLOWING FUNCTIONS ARE TO BE USED WITH THE SPARKFUN QUAD RELAY------*****
 
// This function turns the given relay on. While this also works for the
// SparkFun Single Relay, it is meant for the SparkFun Quad Relay. 
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
  if(relay == RELAY_ONE)
    _writeCommandOn(TOGGLE_RELAY_ONE);
  else if(relay == RELAY_TWO)
    _writeCommandOn(TOGGLE_RELAY_TWO);
  else if(relay == RELAY_THREE)
    _writeCommandOn(TOGGLE_RELAY_THREE);
  else if(relay == RELAY_FOUR)
    _writeCommandOn(TOGGLE_RELAY_FOUR);
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
// whether on: 15 or off: 0;
uint8_t Qwiic_Relay::getRelayStatus(uint8_t relay)
{
  uint8_t status =  _readCommand(relay);
  return status; 
}


// This function handles I2C write commands for turning the relays on. 
// The quad relay relies on the current state of the relay to determine whether
// or not to turn the respective relay on (or off) and so the current state of
// the relay is checked before attempting to send a command. 
void Qwiic_Relay::_writeCommandOn(uint8_t _command)
{

  if( _command == RELAY_ONE ){
    uint8_t _status = _readCommand(RELAY_ONE_STATUS);
    if( _status == QUAD_RELAY_ON ){
      return;
    }
    else {
      _i2cPort->beginTransmission(_address); // Start communication.
      _i2cPort->write(TOGGLE_RELAY_ONE); 
      _i2cPort->endTransmission(); // End communcation.
    }
  }

  else if( _command == RELAY_TWO ){
    uint8_t _status = _readCommand(RELAY_TWO_STATUS);
    if( _status == QUAD_RELAY_ON ){
      return;
    }
    else {
      _i2cPort->beginTransmission(_address); // Start communication.
      _i2cPort->write(TOGGLE_RELAY_TWO); 
      _i2cPort->endTransmission(); // End communcation.
    }
  }

  else if( _command == RELAY_THREE ){
    uint8_t _status = _readCommand(RELAY_THREE_STATUS);
    if( _status == QUAD_RELAY_ON ){
      return;
    }
    else {
      _i2cPort->beginTransmission(_address); // Start communication.
      _i2cPort->write(TOGGLE_RELAY_THREE);
      _i2cPort->endTransmission(); // End communcation.
    }
  }

  else if( _command == RELAY_FOUR ){
    uint8_t _status = _readCommand(RELAY_FOUR_STATUS);
    if( _status == QUAD_RELAY_ON ){
      return;
    }
    else {
      _i2cPort->beginTransmission(_address); // Start communication.
      _i2cPort->write(TOGGLE_RELAY_FOUR);
      _i2cPort->endTransmission(); // End communcation.
    }
  }

  else {
    _i2cPort->beginTransmission(_address);
    _i2cPort->write(_command);
    _i2cPort->endTransmission(); 
  }
     
}

// This function handles I2C write commands for turning the relays off. 
// The quad relay relies on the current state of the relay to determine whether
// or not to turn the respective relay off (or on) and so the current state of
// the relay is checked before attempting to toggle it.
void Qwiic_Relay::_writeCommandOff(uint8_t _command)
{

  if( _command == RELAY_ONE ){
    uint8_t _status = _readCommand(RELAY_ONE_STATUS);
    if( _status == QUAD_RELAY_OFF ){
      return;
    }
    else {
      _i2cPort->beginTransmission(_address); // Start communication.
      _i2cPort->write(TOGGLE_RELAY_ONE); 
      _i2cPort->endTransmission(); // End communcation.
    }
  }

  else if( _command == RELAY_TWO ){
    uint8_t _status = _readCommand(RELAY_TWO_STATUS);
    if( _status == QUAD_RELAY_OFF ){
      return;
    }
    else {
      _i2cPort->beginTransmission(_address); // Start communication.
      _i2cPort->write(TOGGLE_RELAY_TWO); 
      _i2cPort->endTransmission(); // End communcation.
    }
  }

  else if( _command == RELAY_THREE ){
    uint8_t _status = _readCommand(RELAY_THREE_STATUS);
    if( _status == QUAD_RELAY_OFF ){
      return;
    }
    else {
      _i2cPort->beginTransmission(_address); // Start communication.
      _i2cPort->write(TOGGLE_RELAY_THREE);
      _i2cPort->endTransmission(); // End communcation.
    }
  }

  else if( _command == RELAY_FOUR ){
    uint8_t _status = _readCommand(RELAY_FOUR_STATUS);
    if( _status == QUAD_RELAY_OFF ){
      return;
    }
    else {
      _i2cPort->beginTransmission(_address); // Start communication.
      _i2cPort->write(TOGGLE_RELAY_FOUR);
      _i2cPort->endTransmission(); // End communcation.
    }
  }

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
  _i2cPort->write(_command); // Moves pointer to register.
  _i2cPort->endTransmission();

  _i2cPort->requestFrom(_address, 1); 
  uint8_t status = _i2cPort->read();
  return(status);

}

// The function reads thee version number of the Single Quad Relay.
float Qwiic_Relay::_readVersion(uint8_t _command)
{
  _i2cPort->beginTransmission(_address); 
  _i2cPort->write(_command); // Moves pointer to register.
  _i2cPort->endTransmission();

  _i2cPort->requestFrom(_address, 2); 
  float _versValue = _i2cPort->read();
  _versValue += float(_i2cPort->read());
  _versValue = _versValue/10;
  return(_versValue);
  
}


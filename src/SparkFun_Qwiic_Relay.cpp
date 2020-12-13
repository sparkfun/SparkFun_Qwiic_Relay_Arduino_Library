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
  _writeCommand(TURN_RELAY_ON);
}

// This function turns the single relay board off. 
void Qwiic_Relay::turnRelayOff() 
{
  _writeCommand(TURN_RELAY_OFF);
}

// This function gives toggle functionality to the single relay. First the
// status of the relay is checked and is toggled according to what the status
// of the relay: on ---> off or off ----> on.
void Qwiic_Relay::toggleRelay()
{
  uint8_t status = _readCommand(MYSTATUS);
  if (status == SING_RELAY_ON)
    turnRelayOff();
  else  
    turnRelayOn();
}

// This function for the SparkFun Single Relay, gets the status of the relay:
// whether on: 1 or off: 0;
uint8_t Qwiic_Relay::getState()
{
  uint8_t status = _readCommand(MYSTATUS);
  return status; 
}

// This function gets the version number of the SparkFun Single Relay.
float Qwiic_Relay::singleRelayVersion()
{
  float version = _readVersion(FIRMWARE_VERSION);
  return(version);
}


//This function starts a slow PWM (1Hz) with a range from 0-100 so as this is the maximum PWM resolution for Zero-crossing SSR's at 50Hz
bool Qwiic_Relay::setSlowPWM(uint8_t relay, uint8_t pwmValue)
{
  return _writeAddress(RELAY_ONE_PWM + relay - 1, pwmValue);
}

//This function starts a slow PWM (1Hz) with a range from 0-100 so as this is the maximum PWM resolution for Zero-crossing SSR's at 50Hz
uint8_t Qwiic_Relay::getSlowPWM(uint8_t relay)
{
  return _readCommand(RELAY_ONE_PWM + relay - 1);
}

//*****----THE FOLLOWING FUNCTIONS ARE TO BE USED WITH THE SPARKFUN QUAD RELAY------*****
 
// This function turns the given relay on.
void Qwiic_Relay::turnRelayOn(uint8_t relay)
{
  _setRelayStatus(relay, QUAD_RELAY_ON);
}

// This function turns the given relay off.
void Qwiic_Relay::turnRelayOff(uint8_t relay)
{
  _setRelayStatus(relay, QUAD_RELAY_OFF);
}

// This function toggles the given relay. If the relay is on then it will turn
// it off, and if it is off then it will turn it on. 
void Qwiic_Relay::toggleRelay(uint8_t relay)
{
  if (relay == RELAY_ONE)
    _writeCommand(TOGGLE_RELAY_ONE);
  else if (relay == RELAY_TWO)
    _writeCommand(TOGGLE_RELAY_TWO);
  else if (relay == RELAY_THREE)
    _writeCommand(TOGGLE_RELAY_THREE);
  else if(relay == RELAY_FOUR)
    _writeCommand(TOGGLE_RELAY_FOUR);
  else 
    return;
}

// This function for the SparkFun Quad Relay, toggles all relays on the
// board. 
void Qwiic_Relay::toggleAllRelays()
{
  _writeCommand(TOGGLE_ALL);
}

// This function for the SparkFun Quad Relay, turns on all relays on the
// board. 
void Qwiic_Relay::turnAllRelaysOn()
{
  _writeCommand(TURN_ALL_ON);
}

// This function for the SparkFun Quad Relay, turns off all relays on the
// board. 
void Qwiic_Relay::turnAllRelaysOff()
{
  _writeCommand(TURN_ALL_OFF);
}

// This function for the SparkFun Quad Relay, gets the status of the relay:
// whether on: 1 or off: 0;
uint8_t Qwiic_Relay::getState(uint8_t relay)
{

  uint8_t status; 
  if(relay == RELAY_ONE)
    status = _readCommand(RELAY_ONE_STATUS);
  else if(relay == RELAY_TWO)
    status = _readCommand(RELAY_TWO_STATUS);
  else if(relay == RELAY_THREE)
    status = _readCommand(RELAY_THREE_STATUS);
  else if(relay == RELAY_FOUR)
    status = _readCommand(RELAY_FOUR_STATUS);
  else
    return INCORR_PARAM;
  
  if( status == QUAD_RELAY_ON ) // Relay status should be consistent
    return 1; // Relay on
  else
    return QUAD_RELAY_OFF;
}

// This function changes the I-squared-C address of the Qwiic RFID. The address
// is written to the memory location in EEPROM that determines its address.
bool Qwiic_Relay::changeAddress(uint8_t newAddress) 
{

  if (newAddress < 0x07 || newAddress > 0x78) // Range of legal addresses
        return false; 

  return (_writeCommand(ADDRESS_LOCATION));

}

// This function writes a value to an address
bool Qwiic_Relay::_writeAddress(uint8_t addressToWrite, uint8_t value)
{
  _i2cPort->beginTransmission(_address); // Start communication.
  _i2cPort->write(addressToWrite); // Toggle it on....
  _i2cPort->write(value);
  if (_i2cPort->endTransmission() != 0)
  {
    return false; //Transaction failed
  } // End communcation.
  else
  {
    return true;
  }
  
}

// This function handles I-squared-C write commands for changing a relay's state. 
// The quad relay relies on the current state of the relay to determine whether
// or not to turn the respective relay on (or off) and so the current state of
// the relay is checked before attempting to send a command.
void Qwiic_Relay::_setRelayStatus(uint8_t _relay, uint8_t _desiredState)
{
  uint8_t _status;

  if (_relay == RELAY_ONE){
    _status = _readCommand(RELAY_ONE_STATUS);
    if( _status != _desiredState){ // Toggle relay if it doesn't match the desired state
      _writeCommand(TOGGLE_RELAY_ONE);
    }
  }
  else if (_relay == RELAY_TWO){
    _status = _readCommand(RELAY_TWO_STATUS);
    if( _status != _desiredState){ // Repeat for all four relays
      _writeCommand(TOGGLE_RELAY_TWO);
    }
  }
  else if (_relay == RELAY_THREE){
    _status = _readCommand(RELAY_THREE_STATUS);
    if( _status != _desiredState){ 
      _writeCommand(TOGGLE_RELAY_THREE);
    }
  }
  else if (_relay == RELAY_FOUR){
    _status = _readCommand(RELAY_FOUR_STATUS);
    if( _status != _desiredState){ 
      _writeCommand(TOGGLE_RELAY_FOUR);
    }
  }
}

// This function requests information from the product with a simple
// I-squared-C transaction.
uint8_t Qwiic_Relay::_readCommand(uint8_t _command)
{
  _writeCommand(_command);

  _i2cPort->requestFrom(_address, (uint8_t)1);
  uint8_t status = _i2cPort->read();
  return(status);

}

// The function reads the version number of the Single Quad Relay.
float Qwiic_Relay::_readVersion(uint8_t _command)
{
  _writeCommand(_command);

  _i2cPort->requestFrom(_address, (uint8_t)2); 
  float _versValue = _i2cPort->read();
  _versValue += (float)_i2cPort->read() / 10.0 ;
  return(_versValue);
  
}

// This function writes information to the product with a simple
// I-squared-C transaction.
bool Qwiic_Relay::_writeCommand(uint8_t _command)
{
  _i2cPort->beginTransmission(_address); 
  _i2cPort->write(_command);
  return (_i2cPort->endTransmission() == 0);

}
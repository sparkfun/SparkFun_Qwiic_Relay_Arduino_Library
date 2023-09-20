#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>

enum SF_AVAILABLE_QUAD_RELAYS
{

    RELAY_ONE = 0x01,
    RELAY_TWO,
    RELAY_THREE,
    RELAY_FOUR,
};

enum SF_QUAD_RELAY_COMMANDS
{

    TOGGLE_RELAY_ONE = 0x01,
    TOGGLE_RELAY_TWO,
    TOGGLE_RELAY_THREE,
    TOGGLE_RELAY_FOUR,
    RELAY_ONE_STATUS,
    RELAY_TWO_STATUS,
    RELAY_THREE_STATUS,
    RELAY_FOUR_STATUS,
    TURN_ALL_OFF = 0xA,
    TURN_ALL_ON,
    TOGGLE_ALL,
    RELAY_ONE_PWM = 0x10,
    RELAY_TWO_PWM,
    RELAY_THREE_PWM,
    RELAY_FOUR_PWM
};

enum SF_QUAD_RELAY_STATUS
{

    QUAD_RELAY_OFF = 0,
    QUAD_RELAY_ON = 15
};

enum SF_SINGLE_RELAY_COMMANDS
{

    TURN_RELAY_OFF = 0x00,
    TURN_RELAY_ON,
    SFE_SINGLE_FIRMWARE_VERSION = 0x04,
    MYSTATUS
};

enum SF_SINGLE_RELAY_STATUS
{

    SING_RELAY_OFF = 0,
    SING_RELAY_ON = 1
};

#define QUAD_DEFAULT_ADDRESS 0x6D
#define QUAD_ALTERNATE_ADDRESS 0x6C
#define SINGLE_DEFAULT_ADDRESS 0x18
#define SINGLE_ALTERNATE_ADDRESS 0x19

#define QUAD_SSR_DEFAULT_ADDRESS 0x08
#define QUAD_SSR_ALTERNATE_ADDRESS 0x09
#define DUAL_SSR_DEFAULT_ADDRESS 0x0A
#define DUAL_SSR_ALTERNATE_ADDRESS 0x0B

#define QUAD_CHANGE_ADDRESS 0xC7
#define SINGLE_CHANGE_ADDRESS 0x03
#define INCORR_PARAM 0xFF

class Qwiic_Relay
{
  public:
    Qwiic_Relay(uint8_t address); // I-squared-C Constructor

    bool begin(TwoWire &wirePort = Wire); // begin function

    //****----THE FOLLOWING FIVE FUNCTIONS ARE TO BE USED WITH THE SPARKFUN SINGLE RELAY-----****

    // This function turns the single relay board on.
    void turnRelayOn();

    // This function turns the single relay board off.
    void turnRelayOff();

    // This function gives toggle functionality to the single relay. First the
    // status of the relay is checked and is toggled according to what the status
    // of the relay: on ---> off or off ----> on.
    void toggleRelay();

    // This function for the SparkFun Single Relay, gets the status of the relay:
    // whether on: 1 or off: 0;
    uint8_t getState();

    // This function gets the version number of the SparkFun Single Relay.
    float singleRelayVersion();

    // This function starts a slow PWM (1Hz) with a range from 0-100 as this is the maximum PWM resolution for
    // Zero-crossing SSR's at 50Hz
    bool setSlowPWM(uint8_t relay, uint8_t pwmValue);

    // This function starts a slow PWM (1Hz) with a range from 0-100 as this is the maximum PWM resolution for
    // Zero-crossing SSR's at 50Hz
    uint8_t getSlowPWM(uint8_t relay);

    //*****----THE FOLLOWING FUNCTIONS ARE TO BE USED WITH THE SPARKFUN QUAD RELAY------*****

    // This function turns the given relay on. While this also works for the
    // SparkFun Single Relay, it is meant for the SparkFun Quad Relay.
    void turnRelayOn(uint8_t relay);

    // This function turns the given relay off.
    void turnRelayOff(uint8_t relay);

    // This function toggles the given relay. If the relay is on then it will turn
    // it off, and if it is off then it will turn it on.
    void toggleRelay(uint8_t relay);

    // This function for the SparkFun Quad Relay, turns on all relays on the
    // board.
    void turnAllRelaysOn();

    // This function for the SparkFun Quad Relay, turns off all relays on the
    // board.
    void turnAllRelaysOff();

    // This function for the SparkFun Quad Relay, turns off all relays on the
    // board.
    void toggleAllRelays();

    // This function for the SparkFun Quad Relay, gets the status of the relay:
    // whether on: 1 or off: 0;
    uint8_t getState(uint8_t relay);

    // This function changes the I-squared-C address of the Qwiic RFID. The address
    // is written to the memory location in EEPROM that determines its address.
    bool changeAddress(uint8_t newAddress, bool singleRelay = false);

  private:
    uint8_t _address;

    // This function writes a value to an address in the relay, used to set PWM values
    bool _writeAddress(uint8_t address, uint8_t value);

    // This function handles I-squared-C write commands for turning the relays on.
    // The quad relay relies on the current state of the relay to determine whether
    // or not to turn the respective relay on (or off) and so the current state of
    // the relay is checked before attempting to send a command.
    void _writeCommandOn(uint8_t _command);

    // This function handles I-squared-C write commands for turning the relays off.
    // The quad relay relies on the current state of the relay to determine whether
    // or not to turn the respective relay off (or on) and so the current state of
    // the relay is checked before attempting to toggle it.
    void _writeCommandOff(uint8_t _command);

    // This command sends the I-squared-C write command to toggle relays from their
    // current state.
    void _writeCommandToggle(uint8_t _command);

    // This function requests information from the product with a simple
    // I-squared-C transaction.
    uint8_t _readCommand(uint8_t _command);

    // The function reads thee version number of the Single Quad Relay.
    float _readVersion(uint8_t _command);

    TwoWire *_i2cPort;
};

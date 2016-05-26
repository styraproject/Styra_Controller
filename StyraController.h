/* StyraController.h
 * Author:  Luke Hindman
 * Date: Fri Sep  4 11:49:53 MDT 2015
 * Description:  This library provides a clean interface for accessing
 *   button state from the custom Styra hardware controllers */

#ifndef __StyraController__
#define __StyraController__

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_MCP23017.h>
 
#define RELEASED 0
#define PRESSED 1
#define NONE_PRESSED 255

/* This is a limit based upon the number of MCP23017 devices
 * that can be connected to a single i2c bus. */
#define MAX_CONTROLLERS 8
#define DISPLAY_BUFFER 80

class StyraController
{
public:
    StyraController();
    /* Return next byte of macro or 0 when finished */
    void setupController(byte address);
    void pollControllers();
    uint16_t getControllerState(byte index);
    byte getButtonState(byte button);
    uint8_t getPressedButton();
    void displayButtonPress();
    void detectControllers();


private:
    uint8_t _num_controllers;
    Adafruit_MCP23017 _controller[MAX_CONTROLLERS];
    uint16_t _button_bits[MAX_CONTROLLERS];
    uint16_t _last_button_bits[MAX_CONTROLLERS];

};
 
 #endif /* __StyraController__ */
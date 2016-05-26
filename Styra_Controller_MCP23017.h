/**
 * Styra_Controller_MCP23017 provides to custom MCP23017 controller
 *   board with hardware debouncing.
 * 
 * Copyright (C) 2016  Luke Hindman <luke@platypuscreations.net>
 * 
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */ 

#ifndef __STYRA_CONTROLLER_MCP23017_H__
#define __STYRA_CONTROLLER_MCP23017_H__

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include "Styra_Controller.h"
 
#define RELEASED 0
#define PRESSED 1
#define NONE_PRESSED 255

/* This is a limit based upon the number of MCP23017 devices
 * that can be connected to a single i2c bus. */
#define MAX_CONTROLLERS 8
#define DISPLAY_BUFFER 80

class StyraControllerMCP23017: public StyraController
{
public:
    StyraControllerMCP23017();
    void begin();
    void update();
    byte getButtonState(byte button);
    uint8_t getPressedButton();
    void displayButtonPress();



private:

    void _setupController(byte address);
    void _pollControllers();
    void _detectControllers();
    uint16_t _getControllerState(byte index);
    uint8_t _num_controllers;
    Adafruit_MCP23017 _controller[MAX_CONTROLLERS];
    uint16_t _button_bits[MAX_CONTROLLERS];
    uint16_t _last_button_bits[MAX_CONTROLLERS];

};
 
 #endif /* __STYRA_CONTROLLER_MCP23017_H__ */
/**
 * Styra_Controller_Basic provides software debouncing for up to 8 GPIO pins.
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


#ifndef __STYRA_CONTROLLER_BASIC_H__
#define __STYRA_CONTROLLER_BASIC_H__

#include <Arduino.h>
//#include <stdarg.h>
#include "debounced_input.h"
#include "Styra_Controller.h"


#define DISPLAY_BUFFER 80

class StyraControllerBasic: public StyraController
{
public:
  //StyraNativeController( uint8_t * button_pins, const uint8_t num_buttons );
  //StyraControllerBasic( uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
  StyraControllerBasic( uint8_t num_buttons, ...);
  void begin();
  void update();
  uint8_t getButtonState(uint8_t button);
  uint8_t getPressedButton();
  void displayButtonPress();

private:
  uint8_t _button_pin_mapping[8];
  uint8_t _num_buttons;
  DebouncedInput * _dbi;
  uint8_t _button_state[8];
  uint8_t _last_button_state[8];



};

#endif /* __STYRA_CONTROLLER_BASIC_H__ */

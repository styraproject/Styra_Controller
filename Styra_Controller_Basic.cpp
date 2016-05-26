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

#include "Styra_Controller_Basic.h"
#include <stdio.h>
#include <stdarg.h>
//#define SERIAL_DEBUG


// StyraControllerBasic::StyraControllerBasic(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4) {

//   //memcpy(_button_pin_mapping,button_pins,num_buttons * sizeof(uint8_t));
//   _button_pin_mapping[0] = b0;
//   _button_pin_mapping[1] = b1;
//   _button_pin_mapping[2] = b2;
//   _button_pin_mapping[3] = b3;
//   _button_pin_mapping[4] = b4;
//   _num_buttons = 5;

//   _dbi = new DebouncedInput [8];

// }

StyraControllerBasic::StyraControllerBasic(uint8_t num_buttons, ...) {

  va_list ap;
  va_start(ap,num_buttons);
  if (num_buttons < 8) {
    _num_buttons = num_buttons;
  } else {
    _num_buttons = 8;
  }
  Serial.print("Num Buttons: ");
  Serial.println(_num_buttons);
  Serial.println("platypuscreations");

  for (int i=0; i < _num_buttons; i++ ) {
    _button_pin_mapping[i] = (uint8_t) va_arg(ap,int);
    Serial.print(i);
    Serial.print(",");
    Serial.println(_button_pin_mapping[i]);
  }
  va_end(ap);

  _dbi = new DebouncedInput [8];

}

void StyraControllerBasic::begin() {
  for (int i = 0; i < _num_buttons; i++) {
    _dbi[i].begin(_button_pin_mapping[i]);
    _button_state[i] = RELEASED;
  }
#ifdef SERIAL_DEBUG  
  Serial.println("\tStyraControllerBasic Initialized");
#endif

}
void StyraControllerBasic::update(){
  for (int i = 0; i < _num_buttons; i++){
    // Serial.print("Calling update for button: ");
    // Serial.println(_button_pin_mapping[i]);
    _dbi[i].update();
    if (_dbi[i].button_pressed == TRUE && _button_state[i] == RELEASED) {
      _button_state[i] = PRESSED;
#ifdef SERIAL_DEBUG 
      Serial.print("Button ");
      Serial.print(i);
      Serial.println(" pressed");
#endif
    } else if (_dbi[i].button_pressed == FALSE && _button_state[i] == PRESSED) {
      _button_state[i] = RELEASED;
    }
  }
}

uint8_t StyraControllerBasic::getButtonState(uint8_t button){
  uint8_t result = RELEASED;
  if (button < _num_buttons) {
    result =  _button_state[button];
  }
  return result;

}
uint8_t StyraControllerBasic::getPressedButton(){
  uint8_t result = NONE_PRESSED;
  for (int i = 0; i < _num_buttons; i++) {
    if (_button_state[i] == PRESSED) {
       result = i;
       break;
    }
  }
  return result;

}

void StyraControllerBasic::displayButtonPress() {
    char b[DISPLAY_BUFFER];
    
    bool change_detected = memcmp(_last_button_state,_button_state,8 * sizeof (uint8_t));
    
    if (change_detected != false) {
        
      Serial.print("Buttons Detected: ");
      memset(b,0,sizeof(char) * DISPLAY_BUFFER);
      for (int i=0; i < _num_buttons; i++) {
        if (getButtonState(i) == PRESSED) {
          sprintf(b,"%s%d ",b,i);  
          _last_button_state[i] = PRESSED;
        } else {
          _last_button_state[i] = RELEASED;
        }
        
      }
      Serial.print(b);
          Serial.println("");
    }
}

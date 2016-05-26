/**
 * Debounce_input provides a single input debouncer using begin->update design pattern
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
 
#include "debounced_input.h"

DebouncedInput::DebouncedInput() {

}

void DebouncedInput::begin(uint8_t pin) {
  _button_pin = pin;
  pinMode(_button_pin,INPUT_PULLUP);
  _button_state = 0;
  button_pressed = FALSE;
  
}

void DebouncedInput::update() {
  unsigned long current_time = millis();
  if (current_time - _last_update > _check_msec) {
    _button_state=(_button_state<<1) | digitalRead(_button_pin) | 0xe000;
    //Serial.println(_button_state,HEX);
    if(_button_state==0xffff) {
      button_pressed = FALSE;
    } else if(_button_state==0xe000) {
      button_pressed = TRUE;
    }
    _last_update = current_time;
  }
  
}

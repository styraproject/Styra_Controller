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

#ifndef __DEBOUNCED_INPUT_H__
#define __DEBOUNDED_INPUT_H__

#include <Arduino.h>

#define TRUE 1
#define FALSE 0


class DebouncedInput
{
  public:
    DebouncedInput();
    void begin(uint8_t pin);
    void update();
    uint8_t button_pressed;
    

  private:
    uint8_t _button_pin;
    const uint8_t _check_msec = 1;
    unsigned long _last_update;
    uint16_t _button_state;
};

#endif /* __DEBOUNCED_INPUT_H__*/

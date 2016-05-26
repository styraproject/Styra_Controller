
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

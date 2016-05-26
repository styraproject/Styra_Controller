/* Author:  Luke Hindman
 * Date: Sun May  1 09:05:59 MDT 2016
 * Description:  Implementation of StyraController interface that utilizes
 *   Software debouncing with up to 8 GPIO pins on the microcontroller.
 */

#include "StyraNativeController.h"
//#define SERIAL_DEBUG


StyraNativeController::StyraNativeController(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4) {

  //memcpy(_button_pin_mapping,button_pins,num_buttons * sizeof(uint8_t));
  _button_pin_mapping[0] = b0;
  _button_pin_mapping[1] = b1;
  _button_pin_mapping[2] = b2;
  _button_pin_mapping[3] = b3;
  _button_pin_mapping[4] = b4;
  _num_buttons = 5;

  _dbi = new DebouncedInput [8];

}
void StyraNativeController::begin() {
  for (int i = 0; i < _num_buttons; i++) {
    _dbi[i].begin(_button_pin_mapping[i]);
    _button_state[i] = RELEASED;
  }
#ifdef SERIAL_DEBUG  
  Serial.println("\tStyraNativeController Initialized");
#endif

}
void StyraNativeController::update(){
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

uint8_t StyraNativeController::getButtonState(uint8_t button){
  uint8_t result = RELEASED;
  if (button < _num_buttons) {
    result =  _button_state[button];
  }
  return result;

}
uint8_t StyraNativeController::getPressedButton(){
  uint8_t result = NONE_PRESSED;
  for (int i = 0; i < _num_buttons; i++) {
    if (_button_state[i] == PRESSED) {
       result = i;
       break;
    }
  }
  return result;

}

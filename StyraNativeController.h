/* Author:  Luke Hindman
 * Date: Sun May  1 09:05:59 MDT 2016
 * Description:  Implementation of StyraController interface that utilizes
 *   Software debouncing with up to 8 GPIO pins on the microcontroller.
 */

#ifndef __StyraNativeController__
#define __StyraNativeController__

#include <Arduino.h>
#include "debounced_input.h"

#define RELEASED 0
#define PRESSED 1
#define NONE_PRESSED 255

class StyraController
{
public:
    virtual void begin()= 0;
    /* Return next byte of macro or 0 when finished */
    virtual void update() = 0;
    virtual uint8_t getButtonState(uint8_t button) = 0;
    virtual uint8_t getPressedButton() = 0;

};

class StyraNativeController: public StyraController
{
public:
  //StyraNativeController( uint8_t * button_pins, const uint8_t num_buttons );
  StyraNativeController( uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
  void begin();
  void update();
  uint8_t getButtonState(uint8_t button);
  uint8_t getPressedButton();

private:
  uint8_t _button_pin_mapping[8];
  uint8_t _num_buttons;
  DebouncedInput * _dbi;
  uint8_t _button_state[8];



};

#endif /* __StyraNativeController__ */

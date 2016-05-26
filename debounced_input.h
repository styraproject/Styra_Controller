/* Author:  Luke Hindman
 * Date: Thu Feb 11 11:39:13 MST 2016
 * Description:  Single input debouncer using begin->update design pattern
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

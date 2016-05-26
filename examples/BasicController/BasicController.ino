/**
 * BasicController example code
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
#include <Arduino.h>
#include <Wire.h>


#include <Styra_Controller_Basic.h>
#include <Adafruit_MCP23017.h>

//StyraControllerBasic basic_controller = StyraControllerBasic(5,10,11,9,6,5);
StyraControllerBasic basic_controller = StyraControllerBasic(8,5,6,7,8,9,10,11,12);

void setup() {
  Serial.begin(115200);
  /* Wait for the serial terminal to connect before starting */
  while (!Serial) ;
  Serial.println("Basic Controller Library");
  basic_controller.begin();
  Serial.println("READY...");
}

void loop() {
  basic_controller.update();
  basic_controller.displayButtonPress();

}

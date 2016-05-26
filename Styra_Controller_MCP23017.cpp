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

#include "Styra_Controller_MCP23017.h"

//Adafruit_MCP23017 _controller[MAX_CONTROLLERS];
//uint16_t _button_bits[MAX_CONTROLLERS];
//byte _num_controllers;

StyraControllerMCP23017::StyraControllerMCP23017() {
    _num_controllers = 0;
    memset(_button_bits,1,sizeof(uint16_t) * MAX_CONTROLLERS);
    memset(_last_button_bits,0,sizeof(uint16_t) * MAX_CONTROLLERS);
    Wire.begin();
}

void StyraControllerMCP23017::begin() {
    this->_detectControllers();
}

void StyraControllerMCP23017::update() {
    this->_pollControllers();
}

void StyraControllerMCP23017::_detectControllers() {
	byte error, address;
	int nDevices;
	
	Serial.println("Scanning...");
	
	nDevices = 0;
	for(int i = 0; i < 8; i++ ) 
	{
        address = MCP23017_ADDRESS | i;
	  // The i2c_scanner uses the return value of
	  // the Write.endTransmisstion to see if
	  // a device did acknowledge to the address.
	  Wire.beginTransmission(address);
	  error = Wire.endTransmission();
	
	  if (error == 0)
	  {
		Serial.print("\ti2c device found at address 0x");
		if (address<16) 
		  Serial.print("0");
		Serial.print(address,HEX);
		Serial.println("  !");
	    nDevices++;
		this->_setupController(i);
	  }
	  else if (error==4) 
	  {
		Serial.print("Unknow error at address 0x");
		if (address<16) 
		  Serial.print("0");
		Serial.println(address,HEX);
	  }    
	}
	if (nDevices == 0)
	  Serial.println("No i2c devices found");
	else
	  Serial.println("Scanning complete");
}

void StyraControllerMCP23017::_setupController(byte address) {
    if (_num_controllers < MAX_CONTROLLERS) {
        _controller[_num_controllers].begin(address);      // use default address 0
        _controller[_num_controllers].setupInterrupts(true,false,LOW);
        for (int i=0; i < 16; i++) {
            _controller[_num_controllers].pinMode(i, INPUT);
            _controller[_num_controllers].pullUp(i, HIGH);  // turn on a 100K pullup internally
            _controller[_num_controllers].setupInterruptPin(i,FALLING); 
        }
        _num_controllers++;
    }
}

void StyraControllerMCP23017::_pollControllers() {
    for (int i = 0; i < _num_controllers; i++) {
        _button_bits[i] = _controller[i].readGPIOAB();
    }
    
}

uint16_t StyraControllerMCP23017::_getControllerState(byte index){
    if (index < _num_controllers) {
        return _button_bits[index];
    } else {
        return 0;
    }
}

byte StyraControllerMCP23017::getButtonState(byte button) {
    uint16_t controller_index = button / 16;
    uint16_t mask = 1 << int (button % 16);
    if (!( _button_bits[controller_index] & mask)) {
        return PRESSED;
    }
    return RELEASED;
}

uint8_t StyraControllerMCP23017::getPressedButton() {
	uint8_t button = NONE_PRESSED;
	uint16_t mask = 1;
    for (int j = 0; j < _num_controllers; j++ ) {
        if (_button_bits[j] == 65535) {
            continue;
        }
		mask = 1;
        for (int i = 0; i < 16; i++) {
            if (!( _button_bits[j] & mask)) {
              button = i+(j*16);
			  break;
            }
            mask <<=1;
        }
		if (button != NONE_PRESSED) {
			break;
		}
	}
	return button;
}

void StyraControllerMCP23017::displayButtonPress() {
    char b[DISPLAY_BUFFER];
    bool title_displayed = false;
    
    bool button_state_changed = false;
    for (int j = 0; j < _num_controllers; j++ ) {
        if (_last_button_bits[j] != _button_bits[j]) {
            button_state_changed = true;
            _last_button_bits[j] = _button_bits[j];
        }
    }
    
    if (! button_state_changed) {
        return;
    }
    
    
    for (int j = 0; j < _num_controllers; j++ ) {
        if (_button_bits[j] == 65535) {
            continue;
        }
        if (! title_displayed) {
            Serial.print("Buttons Detected: ");
            title_displayed = true;
        }
        uint16_t mask = 1;

        memset(b,0,sizeof(char) * DISPLAY_BUFFER);
        for (int i = 0; i < 16; i++) {
            if (!( _button_bits[j] & mask)) {
              sprintf(b,"%s%d ",b,i+(j*16));
            }
            mask <<=1;
        }
        Serial.print(b);

	}
    if (title_displayed) {
        Serial.println("");
    }
}
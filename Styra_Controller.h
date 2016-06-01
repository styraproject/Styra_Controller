/**
 * Styra_Controller provides a standard controller interface for Styra prototypes
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

#ifndef __STYRA_CONTROLLER_H__
#define __STYRA_CONTROLLER_H__

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
    virtual void displayButtonPress() = 0;
};

#endif /*__STYRA_CONTROLLER_H__*/
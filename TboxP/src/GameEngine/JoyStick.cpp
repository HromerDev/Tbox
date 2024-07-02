#include "JoyStick.h"

/*
JoyStick::JoyStick(int _xPin, int _yPin) //joystick that doesn't use button
{  
    xPin = _xPin;
    yPin = _yPin;

    pinMode(xPin, OUTPUT);
    pinMode(yPin, OUTPUT); 
}
*/
JoyStick::JoyStick(int _xPin, int _yPin, int _buttonPin) // joystick which uses button
{
    xPin = _xPin;
    yPin = _yPin;
    buttonPin = _buttonPin;

    pinMode(buttonPin, INPUT_PULLUP);
}

JoyStick::JoyStick(int _xPin, int _yPin) // joystick which does not use button
{
    xPin = _xPin;
    yPin = _yPin;
}

void JoyStick::JoyStickUpdateData() 
{
    data.x = (analogRead(yPin) / 4095.0 * 2 - 1) * -1; //jostick voltage readings (X and Y)
    data.y = (analogRead(xPin) / 4095.0 * 2 - 1) * -1;
    data.button = !(analogRead(buttonPin));      
}
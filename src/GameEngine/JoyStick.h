#ifndef JOYSTICK_H
#define JOYSTICK_H
#include "Arduino.h"

class JoyStick 
{
    public:
        struct JoystickData 
        {
            float x;
            float y;
            int button;
        };
        JoystickData data;
        
        JoyStick(int _xPin, int _yPin);
        JoyStick(int _xPin, int _yPin, int _buttonPin);
        void JoyStickUpdateData();
    protected:
        int xPin;
        int yPin;
        int buttonPin;

};
#endif
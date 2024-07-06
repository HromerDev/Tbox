#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "LedControl.h"
#include "Timer/timer.h"
#include "JoyStick.h"
#include "GameObjects/GameObject_Children/DynamicObject.h"
#include "GameObjects/GameObject_Children/Point.h"

void returnInputData();
void renderScreen();
void nanoSecondCalculate();

extern bool matrixArea[8][16];
extern bool aspectRatio; 

extern JoyStick leftJoyStick;
extern JoyStick rightJoyStick;

extern bool canRun;

#endif
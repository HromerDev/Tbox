#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "LedControl.h"
#include "Timer/timer.h"
#include "JoyStick.h"
#include "GameObjects/GameObject_Children/DynamicObject.h"
#include "GameObjects/GameObject_Children/Point.h"


#define DIN 14
#define CS 12
#define CLK 13

//left is right and right is left, sorry :3
#define LpinX 26
#define LpinY 27                                

#define RpinX 32
#define RpinY 33
#define RpinJoyStickButtonRead 25

void returnInputData();
void renderScreen();
void nanoSecondCalculate();

extern bool matrixArea[8][16];
extern bool aspectRatio; 

extern JoyStick leftJoyStick;
extern JoyStick rightJoyStick;

extern bool canRun;

#endif
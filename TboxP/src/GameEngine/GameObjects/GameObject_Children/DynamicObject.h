#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H
#include "GameEngine/GameObjects/GameObject.h"
#include "GameEngine/GameEngine.h"
class DynamicObject : public GameObject 
{
    public:
    int objectHeight;
    int objectWidth;
    bool surface[64];
    DynamicObject();
    DynamicObject(int _objectWidth, int _objectHeight, bool _surface[64], int _x = -1, int _y = -1);
    void setPosition(int _x = -1, int _y = -1);
};
#endif
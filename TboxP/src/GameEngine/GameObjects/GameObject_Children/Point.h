#ifndef POINT_H
#define POINT_H
#include "GameEngine/GameObjects/GameObject.h"
#include "GameEngine/GameEngine.h"

class Point : public GameObject 
{
    public:
    Point(int _x = -1, int _y = -1);
    void setPosition(int _x = -1000, int _y = -1000);
};
#endif
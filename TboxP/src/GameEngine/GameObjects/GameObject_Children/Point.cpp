#include "GameEngine/GameObjects/GameObject_Children/Point.h"

Point::Point(int _x, int _y) : GameObject(_x,_y) {}

void Point::setPosition(int _x, int _y) 
    {
      if(_x == -1000)
        _x = position.x;
      if(_y == -1000)
        _y = position.y;

      position.x = _x;
      position.y = _y;

      if(aspectRatio) 
      {
        int c = _x;
        _x = _y;
        _y = 7 - c;      
      }   
      
      if((_x >= 0 && _x < 16) && (_y >= 0 && _y < 8))
          matrixArea[_y][_x] = true;      
    }
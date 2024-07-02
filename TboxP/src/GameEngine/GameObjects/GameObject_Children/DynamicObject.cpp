#include "GameEngine/GameObjects/GameObject_Children/DynamicObject.h" 

DynamicObject::DynamicObject(int _objectWidth, int _objectHeight, bool _surface[64], int _x, int _y) 
{
    objectWidth = _objectWidth;
    objectHeight = _objectHeight;
    
    for (int i = 0; i < (objectWidth * objectHeight); i++)    
        surface[i] = _surface[i];        
    
    position.x = _x;
    position.y = _y; 
}

  DynamicObject::DynamicObject() {}
  void DynamicObject::setPosition(int _x, int _y)
  {
    if(_x == -1)
      _x = position.x;
    if(_y == -1)
      _y = position.y;

    position.x = _x;
    position.y = _y;

    if(aspectRatio) 
    {
      int c = _x;
      _x = _y;
      _y = 7 - c; 
    }   
    
    int arrayIndex = 0; 
    for(int height = 0; height < objectHeight; height++) 
    {
      for(int width = 0; width < objectWidth; width++) 
      {
        if(!aspectRatio) 
        {
          if((_x + width >= 0 && _x + width < 16) && (height + _y >= 0 && height + _y < 8) && surface[arrayIndex])        
            matrixArea[_y + height][_x + width] = surface[arrayIndex];
        }
        else if((_x + height >= 0 && _x + height < 16) && (_y - width >= 0 && _y - width < 8) && surface[arrayIndex])
          matrixArea[_y - width][_x + height] = surface[arrayIndex];
   
        arrayIndex++;
      }      
    }          
  }  
#include "GameObject.h"

    GameObject::GameObject(int _x, int _y) 
    {
      position.x = _x;
      position.y = _y; 
    } 
    void GameObject::moveXY(int _x, int _y) 
    {                         
      position.x += _x;
      position.y += _y;
    }
    void GameObject::moveX(int _x) 
    {
      position.x += _x;
    } 
    void GameObject::moveY(int _y) 
    {     
      position.y += _y;
    }   
    bool GameObject::comparePosition(Position pos2) 
    {
      if(position.x == pos2.x && position.y == pos2.y)
        return true;

      return false;
    }    
    void GameObject::setCoords(Position pos2)
    {
      position.x = pos2.x;
      position.y = pos2.y;
    }
    void GameObject::setCoords(int x, int y) 
    {
      position.x = x;
      position.y = y;
    }

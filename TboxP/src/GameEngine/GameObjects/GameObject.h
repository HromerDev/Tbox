#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


class GameObject 
{
    public:
    
    struct Position 
    {
        int x;
        int y;
    };

    Position position; 
    
    bool comparePosition(Position pos2);
    void setCoords(Position pos2);
    void setCoords(int x, int y);    
    GameObject(int _x = 0, int _y = 0);
    void moveXY(int _x, int _y);
    void moveX(int _x);
    void moveY(int _y);
};
#endif
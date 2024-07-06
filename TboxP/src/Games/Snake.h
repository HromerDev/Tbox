#ifndef SNAKE_H
#define SNAKE_H
#include "GameEngine/GameObjects/GameObject_Children/Point.h"

class Snake_Game
{
    protected:

    struct coords 
    {
        int x;
        int y;
    };   

    coords speed;
    coords anchor;
    Point snakeHead;
    Point snakeBody[128];
    Point apple;
    int applesEaten = 1;
    
    void generateApple();
    void snakeLooping();
    void eatApple();
    void moveTail();
    
    public:
    Snake_Game();
    void gameRun();  

    
};
#endif

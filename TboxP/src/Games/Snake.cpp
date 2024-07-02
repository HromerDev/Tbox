#include "Snake.h"
#include "Arduino.h"

int currentX;
int currentY;
Timer movementTime(200);
Point snakeHead;
Point snakeBody[128];
Point apple;
Snake_Game::Snake_Game() //game's constructor
{   
    delay(1000);
    aspectRatio = true;
    
    currentX = (aspectRatio) ? 8 : 16;
    currentY = (aspectRatio) ? 16 : 8;    
    

}

void Snake_Game::gameRun() // this runs in loop()
{    
    
    if(movementTime.isReady()) //movement
    {
        //x constant velocity
        if(leftJoyStick.data.x > 0.9 && speed.x != -1) 
        {
            speed.x = 1;
            speed.y = 0;
        }
        else if(leftJoyStick.data.x < -0.9 && speed.x != 1) 
        {
            speed.x = -1;
            speed.y = 0; 
        }
        //y constant velocity
        else if(leftJoyStick.data.y > 0.6 && speed.y != -1) 
        {
            speed.x = 0;
            speed.y = 1;
        }        
        else if(leftJoyStick.data.y < -0.6 && speed.y != 1)
        {
            speed.x = 0;
            speed.y = -1;
        }
        else if(speed.x == 0 && speed.y == 0) 
        {
            snakeHead.setCoords(1,5);
            apple.setCoords(6,5);
        }
            
        //anchoring the anchor
        anchor.x = snakeHead.position.x;
        anchor.y = snakeHead.position.y;

        //applying speed
        if(speed.x != 0) 
        {
            snakeHead.moveX(speed.x);
            moveTail();
        }       
        else if(speed.y != 0) 
        {
            snakeHead.moveY(speed.y);
            moveTail();
        }
    }

    for(int i = 1; i < applesEaten; i++)
        if(snakeHead.comparePosition(snakeBody[i].position))  //self destruct 
        {
            delay(2000);
            ESP.restart();
        }     
                
    for (int i = 1; i < applesEaten; i++)        
        snakeBody[i].setPosition();

    eatApple();      
    snakeLooping(); 
    snakeHead.setPosition();    
    apple.setPosition();
} 
void Snake_Game::generateApple()
{
    int _x = random(0, currentX);
    int _y = random(0, currentY);

    while (matrixArea[_y][_x]) 
    {
        _x = random(0, currentX);
        _y = random(0, currentY);
    }

    apple.position.x = _x;
    apple.position.y = _y;
}
void Snake_Game::eatApple() 
{
    if(snakeHead.comparePosition(apple.position)) 
    {
        generateApple();
        applesEaten++;
    }
}
void Snake_Game::moveTail() 
{
    if(applesEaten > 0)    
        snakeBody[0].setCoords(anchor.x,anchor.y);
    
    for(int i = applesEaten - 1; i >= 0; i--)     
        snakeBody[i].setCoords(snakeBody[i - 1].position);            
}
void Snake_Game::snakeLooping() 
{
    if(snakeHead.position.x < 0)
        snakeHead.position.x = currentX - 1;
    else if(snakeHead.position.x > currentX - 1)
        snakeHead.position.x = 0;

    if(snakeHead.position.y < 0)
        snakeHead.position.y = currentY - 1;
    else if(snakeHead.position.y > currentY - 1)
        snakeHead.position.y = 0;
}
#include "Games/Snake.h"
#include "Games/Tetris.h"
#include "Main.h"

short chosenGame = 0;
short gameToChoose = 0;


bool snakeIconSurface[64] = 
{
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,1,1,1,1,0,0,
  0,0,1,0,0,1,0,0,
  0,0,0,0,0,1,0,0,
  0,0,1,0,0,1,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0
};

bool tetrisIconSurface[64] = 
{
  0,0,0,0,0,0,0,0,
  0,1,1,1,0,0,1,0,
  0,0,1,0,0,0,1,0,
  0,0,0,0,1,0,1,0,
  0,0,0,1,1,0,1,0,
  0,0,0,1,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
};

bool chooseIconSurface[64] = 
{
  1,1,1,1,1,1,1,1,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  1,1,1,1,1,1,1,1,
};

DynamicObject snakeIcon(8,8,snakeIconSurface,0,8);
DynamicObject tetrisIcon(8,8,tetrisIconSurface,0,0); 
DynamicObject chooseIcon(8,8,chooseIconSurface,0,16); 

Snake_Game snake;
Tetris_Game tetris;
 


void Main()  
{
  switch (chosenGame)
  {    
    case 1:
      snake.gameRun();
      break; 
    case 2:
      tetris.gameRun();
      break;
    case 0:
      if(leftJoyStick.data.y > 0.8 || rightJoyStick.data.y > 0.8) 
      {
        gameToChoose = 1;
        chooseIcon.setCoords(0, 8);
      }      
      else if(leftJoyStick.data.y < -0.8 || rightJoyStick.data.y < -0.8) 
      {
        gameToChoose = 2;
        chooseIcon.setCoords(0, 0);
      }

      chosenGame = (rightJoyStick.data.button && gameToChoose != 0) ? gameToChoose : 0;

      snakeIcon.setPosition();
      tetrisIcon.setPosition();
      chooseIcon.setPosition();
      break;
  } 
}
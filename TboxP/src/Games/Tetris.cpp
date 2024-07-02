#include "Tetris.h"

Timer initialTimer(1000);
Timer droptime(1500);
Timer fasterDropTime(150);
Timer moveTime(250);
Timer coyoteMoveTimeSlow(5000);
Timer coyoteMoveTimeFast(1000);
bool canPlay = false;

Tetris_Game::Tetris_Game() 
{  
    holdTimeJoystick = 2;
    aspectRatio = true; 

    for (short i = 0; i < 7; i++)    
        tetrominoSack[i] = false;

    for (int i = 0; i < 18; i++) // prepares tetris board Point array for use, inefficient, but sufficient   
        for (int j = 0; j < 10; j++)        
            tetrisBoard[i][j] = Point(j - 1,i - 1);            
                    
    coyoteMoveTimeFast.timerDeactivate();
    coyoteMoveTimeSlow.timerDeactivate();
    
    for (int i = 0; i < 10; i++) // creating a 10x18 collision box outside the 8x16 "tilemap" or "grid", I couldn't be bothered with actual collision (spoiler, I regret this and am too lazy to remake)
        for (int j = 0; j < 18; j++)       
            if((j == 0 || j == 17 || i == 0 || i == 9))
                gameArea[j][i] = true;

    for (short i = 0; i < 7; i++) // loads default tetromino faces
    {   
        if(i == 6)    
            availableTetrominos[6] = DynamicObject(4,4,tetrominoFaceI);       
        else
            availableTetrominos[i] = DynamicObject(3,3,tetrominoFace3[i]);      
    }       
    regenerateTetromino();
    initialTimer.timerActivate();
}
void Tetris_Game::gameRun() //this runs in loop 50 frames a second
{   
    inputHandling(); //inputs
    tetrominoMovement(); //tetromino movement and rotations
    
    clearLanes(); // process lanes, probably expensive, brain, remember to move this function call somewhere after I collide with the tilemap and change it :3
    for (int i = 0; i < 18; i++) // render tetris board    
        for (int j = 0; j < 10; j++)     
            if(gameArea[i][j])        
                tetrisBoard[i][j].setPosition();                       
                    
    availableTetrominos[currentTetromino].setPosition(); //tetromino rendering
}
void Tetris_Game::rotate(bool surfaceToRotate[64], bool direction) 
{
    if(currentTetromino == 0) // the cube just doesn't rotate 
        return;

    
    bool surfaceHolder[64];
    int new_i;
    int new_j;

    for (int i = 0; i < availableTetrominos[currentTetromino].objectHeight * availableTetrominos[currentTetromino].objectWidth; i++) // stores an array onto temporary array
        surfaceHolder[i] = surfaceToRotate[i];
       
    for (int i = 0; i < availableTetrominos[currentTetromino].objectHeight; i++) //rotation logic
        for (int j = 0; j < availableTetrominos[currentTetromino].objectWidth; j++) 
        {
            if(direction) //rotate right I think
            {
                new_i = availableTetrominos[currentTetromino].objectWidth - 1 - j;
                new_j = i;
            }
            else //rotate left
            {
                new_i = j;
                new_j = availableTetrominos[currentTetromino].objectWidth - 1 - i;
            }
            
            surfaceToRotate[new_i * availableTetrominos[currentTetromino].objectHeight + new_j] = surfaceHolder[i * availableTetrominos[currentTetromino].objectWidth + j]; // load rotated array into current tetromino face
        }

    if(!collision(0, 0, surfaceToRotate, true)) // check if no collision 
        for (int i = 0; i < availableTetrominos[currentTetromino].objectHeight * availableTetrominos[currentTetromino].objectWidth; i++) 
            availableTetrominos[currentTetromino].surface[i] = surfaceToRotate[i]; // stores rotated face as the current piece
    else // ABORT, ABORT, ABORT
        for (int i = 0; i < availableTetrominos[currentTetromino].objectHeight * availableTetrominos[currentTetromino].objectWidth; i++) 
            surfaceToRotate[i] = availableTetrominos[currentTetromino].surface[i]; // just to be sure I revert it all, I will likely delete this 
}
bool Tetris_Game::collision(int futureX, int futureY,bool futureTetrominoSurface[64], bool rotationCollision) // implement to dynamic object native properties later
{
    if(!rotationCollision) 
    {
        futureX = availableTetrominos[currentTetromino].position.x + futureX;
        futureY = availableTetrominos[currentTetromino].position.y + futureY;

        int surfaceIndex = 0;

        for(int checkerY = 0; checkerY < availableTetrominos[currentTetromino].objectHeight; checkerY++) //checking collisions on current dynamic object
            for(int checkerX = 0; checkerX < availableTetrominos[currentTetromino].objectWidth; checkerX++) 
            {
                int checkerFutureSumX = futureX + checkerX + 1;
                int checkerFutureSumY = futureY + checkerY + 1;

                    if(futureTetrominoSurface[surfaceIndex] && gameArea[checkerFutureSumY][checkerFutureSumX]) // this is where collision gets confirmed and immedietly ends check        
                        return true;                        
                                 
                surfaceIndex++;
            }
    }
    else //o-oh, special treatment :3, there is a rotation bug here when rotating next to walls, fix   
    {
        // Check if rotation is blocked by both sides
        if (collision(1, 0, futureTetrominoSurface) && collision(-1, 0, futureTetrominoSurface)) 
            return true;

            if(collision(0, 0, futureTetrominoSurface)) 
            {
                for (short i = 1; i <= 2; i++)                
                    if(!collision(i, 0, futureTetrominoSurface)) 
                    {
                        availableTetrominos[currentTetromino].moveX(i);
                        return false; 
                    }                

                for (short i = 1; i <= 2; i++)              
                    if(!collision(-i, 0, futureTetrominoSurface)) 
                    {
                        availableTetrominos[currentTetromino].moveX(-i);
                        return false; 
                    }
            }
        return false;
    }
    return false;
}
void Tetris_Game::inputHandling() 
{
    if(leftJoyStick.data.x > 0.9) // changes speed according to left joystick
        speed.x = 1;        
    else if(leftJoyStick.data.x < -0.9)     
        speed.x = -1;
    else
        speed.x = 0;

    holdTimeJoystick = (rightJoyStick.data.button) ? holdTimeJoystick + 1 : 0; // magic that I use to check 1 button activation, implement into native joystick functions
    holdTime = (rightJoyStick.data.x > 0.9 || rightJoyStick.data.x < -0.9) ? holdTime + 1 : 0;    
    
    if(holdTime == 1) 
        rotate(rotatedSurface, !(rightJoyStick.data.x < -0.9));
}
void Tetris_Game::tetrominoMovement() 
{
    if(moveTime.isReady() && !collision(speed.x, 0, rotatedSurface)) // X axis
        availableTetrominos[currentTetromino].moveX(speed.x);

    if((leftJoyStick.data.y < -0.9 && fasterDropTime.isReady() || holdTimeJoystick == 1 || droptime.isReady()) && !collision(0, -1, rotatedSurface)) // check if not on floor
    {
        if(coyoteMoveTimeSlow.isActive) // disabling if unused
            coyoteMoveTimeSlow.timerDeactivate();      
        if(coyoteMoveTimeFast.isActive) 
            coyoteMoveTimeFast.timerDeactivate();

        if(holdTimeJoystick == 1) //insta falling 
        {
            while (!collision(0, -1, rotatedSurface))
                availableTetrominos[currentTetromino].moveY(-1); 

            stackTetromino();
            regenerateTetromino();
        }                        
        else //faster falling
            availableTetrominos[currentTetromino].moveY(-1);      
    }        
    else if(collision(0, -1, rotatedSurface)) //on floor
    {      
        if(!coyoteMoveTimeSlow.isActive)
            coyoteMoveTimeSlow.timerActivate();
        if(!coyoteMoveTimeFast.isActive)
            coyoteMoveTimeFast.timerActivate();
        if(speed.x != 0)
            coyoteMoveTimeFast.timerReset();

        if(coyoteMoveTimeSlow.isReady() || coyoteMoveTimeFast.isReady()) // tetromino becomes static
        {
            stackTetromino();
            regenerateTetromino();
        }       
    }
}
void Tetris_Game::regenerateTetromino() 
{
    bool resetSack = true;
    for(short i = 0; i < 7; i++) 
    {
        if(!tetrominoSack[i]) 
        {
            resetSack = false;
            break;
        }      
    } 

    if(resetSack)
        for(short j = 0; j < 7; j++)        
            tetrominoSack[j] = false; 

    while (true) 
    {
        short chooser = random(0,7);

        if(!tetrominoSack[chooser]) 
        {
            currentTetromino = chooser;
            tetrominoSack[chooser] = true;
            break;
        }          
    }
        
    for(int i = 0; i < availableTetrominos[currentTetromino].objectHeight * availableTetrominos[currentTetromino].objectWidth; i++) 
        rotatedSurface[i] = availableTetrominos[currentTetromino].surface[i];

    availableTetrominos[currentTetromino].position.x = 2;
    availableTetrominos[currentTetromino].position.y = 12;   

    if(collision(0,0,availableTetrominos[currentTetromino].surface) && !rightJoyStick.data.button) //self destruct
    {
        delay(2000);
        ESP.restart();
    }

}
void Tetris_Game::stackTetromino() 
{
    int arrayIndex = 0;
        for (int i = 0; i < availableTetrominos[currentTetromino].objectHeight; i++)      
            for (int j = 0; j < availableTetrominos[currentTetromino].objectWidth; j++) 
            {
                if(availableTetrominos[currentTetromino].surface[arrayIndex])
                    gameArea[i + availableTetrominos[currentTetromino].position.y + 1][j + availableTetrominos[currentTetromino].position.x + 1] = availableTetrominos[currentTetromino].surface[arrayIndex];
                arrayIndex++;
            }
} 

void Tetris_Game::clearLanes() 
{
    for(int line = 16; line > 0; line--)  
    {
        bool lineIsFull = true;

        for (int i = 1;i < 9; i++) //checks if a line is full       
            if (!gameArea[line][i])  
            {
                lineIsFull = false;
                break;
            }           
                          
        if(lineIsFull) 
        {
            for (int i = 1; i < 9; i++) //clears a line   
                gameArea[line][i] = false; 
             
            for (int lineToStartFrom = line; lineToStartFrom < 16; lineToStartFrom++)  // moves pieces lower          
                for (int i = 1; i < 9; i++)               
                    gameArea[lineToStartFrom][i] = gameArea[lineToStartFrom + 1][i];
                        
            line--; 
        }                               
    }    
}
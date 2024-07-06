#ifndef TETRIS_H
#define TETRIS_H
#include "GameEngine/GameEngine.h"
#include "Main.h"
class Tetris_Game 
{   
    protected:
    struct coords 
    {
        int x;
        int y;
    };   
    
    coords speed;
    void rotate(bool surfaceToRotate[64], bool a);
    bool collision(int x = 0, int y = 0, bool currentTetrominoSurface[64] = {}, bool rotationCollision = false);
    void inputHandling();
    void tetrominoMovement();
    void regenerateTetromino();
    void stackTetromino();
    void clearLanes();
    int currentTetromino;
    bool rotatedSurface[64];
    bool gameArea[18][10];
    bool tetrominoSack[7];
    
    int holdTime = 0;
    int holdTimeJoystick = 0;
    bool rotateDirection;

    Point tetrisBoard[18][10];
    DynamicObject availableTetrominos[8];
    //DynamicObject gameBoard;
    bool tetrominoFace3[6][9] 
    {        
        {0,0,0,0,1,1,0,1,1}, //O
        {0,0,0,1,1,1,0,1,0}, //T
        {0,0,0,1,1,1,0,0,1}, //L
        {0,0,0,1,1,1,1,0,0}, //J
        {0,0,0,1,1,0,0,1,1}, //S
        {0,0,0,0,1,1,1,1,0}  //Z
    };
    bool tetrominoFaceI[16] {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0};
    
    public:
        Tetris_Game();
        void gameRun();
};
#endif
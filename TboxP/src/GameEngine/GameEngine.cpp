#include "GameEngine.h"
#include "Main.h"

/*
/////TODO AREA:


/////Finished:
    my sanity
    plan out function sequences (somewhat, picture in the folder)
    objects
    player input cause and effect
    frame dependancy
    timers
    movement not being bound to joystick, possibility of adding variables
    2D gameObject support
    Object Optimizations (Gameobject class now has Point and DynamicObject classes as children)
    GameObject parent class now handles X and Y coordinates for both children
    GameObject parent class handles movement methods for both children
    abandon Arduino IDE and use VScode
    Figure out how and sort each class into its distinct file
    2 buttons wired and separated in code with voltage measuring
    allow setPosition in Dynamic and Point classes to write in 16x8 and 8x16 onto the matrixArea
    implement 2nd joystick and joystick managing class instead of the buttons
    2 button game functions (interact button (joystick button potentially being one of the 2) and return button(maybe normal button, undecided))
    
    the 2 games::    
    figure out idea for 2nd game, potencial ideas: flappy bird, the one game where you shoot at bullets approaching you  
    
    Game 1) Snake
      fix snake inconsistencies caused by updating older code

    Game 2) Tetris
      test new axis conversion
      Tetromino faces
      rotation handling
      figure out object handling (collisions)
      make them stackable on the bottom
      figure out how I fucked up collisions
      allow some time of movemement while colliding with ground (coyote time, I think the name can be used here too)
      fix rotations when tetromino is sandwiched
      system for clearing out rows
      implement rng for pieces 
      bug fixing, (I piece needs special treatment when it comes to kicking off walls)
      bug fixing, (the pieces can't sometimes rotate when next to a wall, inproper implementation of a system)

    Console: 
     rewire the thing without breaking it
     a system I can easily program games with (not stacking it all in loop)
     cleanup
     implement button from right joystick
     put it into a box and don't break it
     Booting hub between 2 games, accesible mid game by holding both joystick buttons
     //plan out tetris
    fix bug in tetris

/////Scrapped:
  More Games
  //plan out tetris    
    gameplay difficulty curve
*/
hw_timer_t * timer = NULL;
volatile uint32_t startTime = 0;
volatile uint32_t endTime = 0;

bool canRun = true;
bool aspectRatio = true;
unsigned long timeCount = 0;

LedControl LEDMatrix[2] = { LedControl(DIN, CLK, CS, 2), LedControl(DIN, CLK, CS, 2)}; 

bool previousMatrixArea[8][16];
bool matrixArea[8][16] = {{false}};

JoyStick rightJoyStick(LpinX, LpinY, RpinJoyStickButtonRead);
JoyStick leftJoyStick(RpinX, RpinY);

void IRAM_ATTR onTimer() // I have no clue how this works
{
  endTime = micros();
}

void setup() 
{
  Serial.begin(115200);
  for (int i = 0; i < 2; i++) //display initialization, uncle google said it needed these
  {
    LEDMatrix[i].shutdown(i, false); 
    LEDMatrix[i].setIntensity(i, 3); 
    LEDMatrix[i].clearDisplay(i);    
  }



  // Set up the hardware timer, once again, no clue how this works
  timer = timerBegin(0, 80, true); // Use timer 0, prescaler 80, count up
  timerAttachInterrupt(timer, &onTimer, true); // Attach the interrupt
  timerAlarmWrite(timer, 10000, true); // Set the timer period to 10,000 microseconds
  timerAlarmEnable(timer); // Enable the timer

  startTime = micros();
}
void loop() 
{    
  if(millis() > timeCount + 20) //scuffed rendering scheme, who knows what will happen if the frametimes aren't precise ¯\_(ツ)_/¯
  {
    randomSeed(millis());
    
    rightJoyStick.JoyStickUpdateData(); //inputs
    leftJoyStick.JoyStickUpdateData();
    
    Main();
    
    renderScreen(); //final thing to occur in a frame    
    //nanoSecondCalculate(); // used only in debugging
  }    
}

void renderScreen() //renders to matrices from matrixArea 2d array dependant on previous matrix states, after rendering switches states, hopefully this process will keep up 50 times a second 
{    
    for (int x = 0; x < 16; x++) 
      for (int y = 0; y < 8; y++)
      {
        int i = (x < 8) ? 0 : 1; //display change
        if (previousMatrixArea[y][x] != matrixArea[y][x]) //checking if a pixel is already on 
          LEDMatrix[i].setLed(i, x % 8, y , matrixArea[y][x]); // replace the pixel
      }         
  
  for (int y = 0; y < 8; y++) // because previousMatrixArea = matrixArea doesn't work, oh well :3    
    for (int x = 0; x < 16; x++) 
    {
      previousMatrixArea[y][x] = matrixArea[y][x];
      matrixArea[y][x] = false;
    }  
  Timer::frameCount++;
  timeCount += 20; // my hope is that if like 2 frames skip, both will immediatly occur and there will be no desync (please)       
}  
void nanoSecondCalculate() 
{
  // Calculate elapsed time
  double elapsedTime = endTime - startTime;

  Serial.print("Elapsed Time: ");
  Serial.print(elapsedTime);
  Serial.print(" microseconds, "); 
  Serial.print((float)elapsedTime / 1000);
  Serial.print(" milliseconds (");
  Serial.print(1 / (float)(elapsedTime / 1000000));
  Serial.println(" FPS)");

  // Reset start time for next iteration
  startTime = micros();
}
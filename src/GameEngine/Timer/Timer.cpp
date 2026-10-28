#include "GameEngine/Timer/Timer.h"

    unsigned long Timer::frameCount = 0;
    
    Timer::Timer(int milliSecondsToConvertToFrames) 
    {
      holdForFrames = milliSecondsToConvertToFrames / 50;
    }
    void Timer::timerActivate() 
    {
      framesActive = frameCount;
      isActive = true;  
    }
    void Timer::timerDeactivate() 
    {
      isActive = false;
    }
    void Timer::timerReset() 
    {
      framesActive = frameCount;
    }

    bool Timer::isReady() 
    {
      if(!isActive) 
      {       
        return false;
      }

      if(frameCount > framesActive + holdForFrames) 
      {
        framesActive = frameCount + holdForFrames;
        return true;  
      }
      return false;        
    }   
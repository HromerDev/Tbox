#ifndef TIMER_H
#define TIMER_H

class Timer 
{       
    public:
        Timer(int milliSecondsToConvertToFrames);
        bool isReady();
        void timerActivate();
        void timerDeactivate();
        void timerReset();
        static unsigned long frameCount;
        bool isActive = true;
    protected:    
        int holdForFrames;
        unsigned long framesActive = 0;
}; 
#endif     
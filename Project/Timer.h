#ifndef Timer_h
#define Timer_h

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <thread>
#include <chrono>

class Timer {
    int interval;
    int delta;
    int initial;

    std::thread timerThread;
    //where enemy movement is done (poles)
    static void repeat(Timer*);


public:
    Timer();
    ~Timer();
    
    void start();
    void setRate(int);  
    //for pausing the game 
    void stop();
    virtual void action() = 0;
    bool running;
};


#endif

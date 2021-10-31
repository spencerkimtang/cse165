#include "Timer.h"


Timer::Timer() {
    interval = 1000;
    running = false;
    initial = glutGet(GLUT_ELAPSED_TIME);
    delta = initial;
}

Timer::~Timer(){
    if (running) timerThread.detach();
}

//where the  "enemy moves" (poles)
void Timer::repeat(Timer* self){
    while (self->running){
        int run = glutGet(GLUT_ELAPSED_TIME);
        self->delta = run - self->initial;
        int delay = self->interval;

        if (self->delta >= self->interval){
            self->action();
            glutPostRedisplay();
            
            self->initial = glutGet(GLUT_ELAPSED_TIME);
        }
        std::this_thread::sleep_for (std::chrono::milliseconds(self->interval/2));
    } 
}

//for pausing the game
void Timer::stop(){
    if (running) timerThread.detach();
    running = false;
}

void Timer::setRate(int mills){
    interval = mills;
}

void Timer::start(){
    running = true;
    timerThread = std::thread(repeat, this);
}

#ifndef App_h
#define App_h

#include "GlutApp.h"
#include "Rect.h"
#include <deque>

using namespace std;

class App: public GlutApp {

    Rect* ship;
    Rect* enemy;
    deque<Rect*> bullets;

public:
    //deque<SpaceShip*> bullets;
    
    App(int argc, char** argv, int width, int height, const char* title);

    
    void draw();
    
    void keyDown(unsigned char key, float x, float y);

    void idle();
    
    ~App();
    
};

#endif

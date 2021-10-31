#ifndef Game_h
#define Game_h

#include "AppComponent.h"
#include "TexRect.h"
#include "Timer.h"

class Game: public AppComponent, private Timer{
    TexRect* bird;
    TexRect* pole;
    TexRect* pole1;
    TexRect* pole2;
    TexRect* pole3;
    TexRect* pole4;
    TexRect* pole5;
    TexRect* pole6;
    TexRect* pole7;
    TexRect* pole8;
    TexRect* pole9;
    TexRect* backg;
    TexRect* backg1;
    TexRect* backg2;
    TexRect* menu;
    TexRect* gameoverScreen;
    
    bool hit;
    int hangTime;
    bool gamestart = false;
    bool gameover = false;
    bool birdHit = false;
    
    
    enum state{jump, falling, collision};
    state birdstate = falling;
    
public:
    Game();
    ~Game();
    
    void draw() const ;
    void handleKeyDown(unsigned char, float, float);
    void action();
};

#endif 

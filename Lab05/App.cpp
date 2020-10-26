#include <iostream>
#include "App.h"
#include "Rect.h"
#include <deque>

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

using namespace std;

void renderText(
    string text, 
    float x, 
    float y, 
    void* font = GLUT_BITMAP_TIMES_ROMAN_24, 
    float r = 0, 
    float g = 0, 
    float b = 0
){
    glColor3f(r, g, b);
    float offset = 0;
    for (int i = 0; i < text.length(); i++) {
        glRasterPos2f(x+offset, y);
        glutBitmapCharacter(font, text[i]);
        int w = glutBitmapWidth(font, text[i]);
        offset += ((float)w / 640)*2;
    }
}

bool hit = false;


App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
   
    //controlling ship
    ship = new Rect(0.0, -0.5, 0.2, 0.2, 0.0, 1.0, 0.0);
    //enemy ship
    enemy = new Rect(0.0, 0.6, 0.9, 0.5, 0.0, 0.0, 1.0);

}

void App::draw() {
    enemy -> draw();

    for (auto i = bullets.begin(); i < bullets.end(); i++){
        (*i) -> draw();
        if ((*i) -> hitted()){
            renderText("YOU WIN!", 0.0, 0.9, GLUT_BITMAP_TIMES_ROMAN_24, 0.0, 1.0, 1.0);
        }
    }

    if ((ship->getX() >= enemy->getX()) && (ship->getX() < enemy->getX() + enemy->getW()) && (ship->getY() < enemy->getY()) && (ship->getY() >= enemy->getY() - enemy->getH())){
        renderText("GAME OVER!", 0.0, 0.9, GLUT_BITMAP_TIMES_ROMAN_24, 0.0, 1.0, 1.0);
    }
    else {
        ship -> draw();
    }
}

void App::idle(){
    for (auto i = bullets.begin(); i < bullets.end(); i++){
        (*i) -> moveBullet();

        if (((*i)->getX() >= enemy->getX()) && ((*i)->getX() < enemy->getX() + enemy->getW()) && ((*i)->getY() < enemy->getY()) && ((*i)->getY() > enemy->getY() - enemy->getH())){
           (*i)->fire();
        }
    }
    redraw();
}

void App::keyDown(unsigned char key, float x, float y){
    if (key == 27){
        exit(0);
    }
    else if (key == 'w'){
        ship->moveUp();
        redraw();
    }
    else if (key == 's'){
        ship->moveDown();
        redraw();
    }
    else if (key == 'a'){
        ship->moveLeft();
        redraw();
    }
    else if (key == 'd'){
        ship->moveRight();
        redraw();
    }
    else if (key == ' '){
        float x = (ship->getX());
        float y = (ship->getY());
        bullets.push_front(new Rect(x, y, 0.05, 0.02, 1.0, 0.0, 0.0));
        redraw();
    }
}

App::~App(){
    std::cout << "Exiting..." << std::endl;
    delete ship;
    delete enemy;
    //delete bullets;
}

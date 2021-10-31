#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

#include "Game.h"

Game::Game(){
    bird = new TexRect("bird.png", -0.4, 0.25, 0.12, 0.16);
    
    pole = new TexRect("pole.png", 0.1, -0.3, 0.15, 1.25);
    pole1 = new TexRect("pole.png", 0.1, 1.5, 0.15, 1.25);
    pole2 = new TexRect("pole.png", 1.0, -0.5, 0.15, 1.25);
    pole3 = new TexRect("pole.png", 1.0, 1.3, 0.15, 1.2);
    pole4 = new TexRect("pole.png", 1.9, 0.1, 0.15, 1.25);
    pole5 = new TexRect("pole.png", 1.9, 1.9, 0.15, 1.25);
    pole6 = new TexRect("pole.png", 2.7, -0.6, 0.15, 1.25);
    pole7 = new TexRect("pole.png", 2.7, 1.2, 0.15, 1.25);
    pole8 = new TexRect("pole.png", 3.7, 0.1, 0.15, 1.25);
    pole9 = new TexRect("pole.png", 3.7, 1.9, 0.15, 1.25);

    backg = new TexRect("flappybirdBackground.png", -2, 1, 4, 2);
    backg1 = new TexRect("flappybirdBackground.png", 2, 1, 4, 2);
    backg2 = new TexRect("flappybirdBackground.png", 6, 1, 4, 2);
    
    menu = new TexRect("menu.png", -2, 1, 4, 2);
    gameoverScreen = new TexRect("gameover.png", -2, 1, 4, 2);

    setRate(1);
    //called in Timer.cpp
    start();
}

Game::~Game(){
    stop();
    delete bird;
    delete pole;
    delete pole1;
    delete pole2;
    delete pole3;
    delete pole4;
    delete pole5;
    delete pole6;
    delete pole7;
    delete pole8;
    delete pole9;
    delete backg;
    delete backg1;
    delete backg2;
    delete menu;
    delete gameoverScreen;
}

void Game::draw() const {
    if(gamestart == false){
        gameover == true;
        //draw in texrect
        menu->draw(1.0);
    }
    
    if(gameover == true){
        gamestart == false;
        gameoverScreen->draw(1.0);
    }
    
    if(gamestart == true && gameover == false){
        backg->draw(0.0);
        backg1->draw(0.0);
        backg2->draw(0.0);
        
        bird->draw(1.0);
        
        pole->draw(1.0);
        pole1->draw(1.0);
        pole2->draw(1.0);
        pole3->draw(1.0);
        pole4->draw(1.0);
        pole5->draw(1.0);
        pole6->draw(1.0);
        pole7->draw(1.0);
        pole8->draw(1.0);
        pole9->draw(1.0);
    }
}

void Game::handleKeyDown(unsigned char key, float x, float y){
    //to start game
    if(key == 's'){
        gamestart = true;
        gameover = false;
    }
    else if (key == ' '){
        hangTime = 200;
        birdstate = jump;
    }
    //for pausing
    else if (key == 'p'){
        stop();
    }
}

void Game::action(){
    if(gamestart == true && gameover == false){
        float fallingY = -0.0009;
        
        switch (birdstate) {
            //for pressing space bar
            case jump: {
                float ypos = bird->getY();
                if(hangTime > 0){
                    ypos += 0.001;
                    bird->setY(ypos);
                    hangTime = hangTime - 1;
                }
                else{
                    birdstate = falling;
                }
                break;
            }
            //when not pressing space bar or starting the game
            case falling: {
                bird->setY(fallingY + bird->getY());
                if(bird->contains(-0.4, -0.9)){
                    birdstate = collision;
                }
                break;
            }
            case collision: {
                bird->setY(bird->getY());
                backg->setX(-2);
                backg1->setX(-6);
                backg2->setX(-6);
                birdHit = true;
                gameover = true;
                //goes to timer
                stop();
                break;
            }
        }
        
        //for moving the poles
        if(birdstate != collision){
            if(pole->getX() <= -2.5){
                pole->setX(1.8);
            }
            if(pole1->getX() <= -2.5){
                pole1->setX(1.8);
            }
            if(pole2->getX() <= -2.5){
                pole2->setX(1.8);
            }
            if(pole3->getX() <= -2.5){
                pole3->setX(1.8);
            }
            if(pole4->getX() <= -2.5){
                pole4->setX(1.8);
            }
            if(pole5->getX() <= -2.5){
                pole5->setX(1.8);
            }
            if(pole6->getX() <= -2.5){
                pole6->setX(1.8);
            }
            if(pole7->getX() <= -2.5){
                pole7->setX(1.8);
            }
            if(pole8->getX() <= -2.5){
                pole8->setX(1.8);
            }
            if(pole9->getX() <= -2.5){
                pole9->setX(1.8);
            }
            
            pole->setX(-0.001 + pole->getX());
            pole1->setX(-0.001 + pole1->getX());
            pole2->setX(-0.001 + pole2->getX());
            pole3->setX(-0.001 + pole3->getX());
            pole4->setX(-0.001 + pole4->getX());
            pole5->setX(-0.001 + pole5->getX());
            pole6->setX(-0.001 + pole6->getX());
            pole7->setX(-0.001 + pole7->getX());
            pole8->setX(-0.001 + pole8->getX());
            pole9->setX(-0.001 + pole9->getX());
            
        }
        else{
            birdstate = collision;
        }
        
        if(backg->getX() <= -6){
            backg->setX(6);
        }
        if(backg1->getX() <= -6){
            backg1->setX(6);
        }
        if(backg2->getX() <= -6){
            backg2->setX(6);
        }
        
        backg->setX(backg->getX() - .001);
        backg1->setX(backg1->getX() - .001);
        backg2->setX(backg2->getX() - .001);
        
        //when bird hits pole
        if(pole->contains(bird->getX(), bird->getY())){
            birdstate = collision;
        }
        if(pole1->contains(bird->getX(), bird->getY())){
            birdstate = collision;
        }
        if(pole2->contains(bird->getX(), bird->getY())){
            birdstate = collision;
        }
        if(pole3->contains(bird->getX(), bird->getY())){
            birdstate = collision;
        }
        if(pole4->contains(bird->getX(), bird->getY())){
            birdstate = collision;
        }
        if(pole5->contains(bird->getX(), bird->getY())){
            birdstate = collision;
        }
        if(pole6->contains(bird->getX(), bird->getY())){
            birdstate = collision;
        }
        if(pole7->contains(bird->getX(), bird->getY())){
            birdstate = collision;
        }
        if(pole8->contains(bird->getX(), bird->getY())){
            birdstate = collision;
        }
        if(pole9->contains(bird->getX(), bird->getY())){
            birdstate = collision;
        }
    }
}

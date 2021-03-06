#include "Square.h"

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

//from lecture
//for making square 1
Square::Square(){
	x = 0;
	y = 0;
	red = 1;
	green = 0;
	blue = 0;
	w = 0.3;
	h = 0.3;

	selected = false;
}
//from lecture
Square::Square(float x, float y, float w, float h){
	this->x = x;
	this->y = y;

	red = 1;
	green = 0;
	blue = 0;

	this->w = w;
	this->h = h;

	selected = false;
}

//from lecture
//for making square 2 and 3
Square::Square(float x, float y, float w, float h, float red, float green, float blue){
	this->x = x;
	this->y = y;

	this->red = red;
	this->green = green;
	this->blue = blue;

	this->w = w;
	this->h = h;

	selected = false;
}

bool Square::contains(float x, float y){
	return (x > this->x) && (x < this->x + this->w) && (y < this->y) && (y > this->y - this->h);
}

	
float Square::dragX(float mx){
	return mx - this->w/2;
}

float Square::dragY(float my){
	return my + this->h/2;
}

bool Square::containsResize(float x, float y){
 	return (x > this->x) && (x < (this->x + this->w)/2) && (y < this->y) && (y > (this->y - this->h)/2);
}

float Square::sizeX(float mx){
	if (mx > this-> x){
		return mx + this->x;
	}
	else if (mx < this-> x){
		return mx - this->x;
	}
}

float Square::sizeY(float my){
	if (my > this-> y){
		return my + this->y;
	}
	else if (my < this-> y){
		return my - this-> y;
	}
}


void Square::select(){
	selected = true;
}

void Square::deselect(){
	selected = false;
}


void Square::draw(){
    if (selected){
        //white line border
        glColor3f(1,1,1);
		glBegin(GL_LINES);

            glVertex2f(x, y);
            glVertex2f(x+w, y);

            glVertex2f(x+w, y);
            glVertex2f(x+w, y-h);//
            
            glVertex2f(x+w, y-h);
            glVertex2f(x, y-h);//
            
            glVertex2f(x, y-h);
            glVertex2f(x, y);

		glEnd();

        glColor3f(red, green, blue);
        glBegin(GL_POLYGON);
            glVertex3f(x, y, 0.1);
            glVertex3f(x+w, y, 0.1);
            glVertex3f(x+w, y-h, 0.1);
            glVertex3f(x, y-h, 0.1);
        glEnd();

    }
    
    else {
        glColor3f(red, green, blue);
        glBegin(GL_POLYGON);
            glVertex3f(x, y, 0.1);
            glVertex3f(x+w, y, 0.1);
            glVertex3f(x+w, y-h, 0.1);
            glVertex3f(x, y-h, 0.1);
        glEnd();
    }
    
}

#include "Rect.h"
#include <iostream>
#include <string>

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

using namespace std;

Rect::Rect(){
	x = 0;
	y = 0;
	w = 0.0;
	h = 0.0;
	red = 0;
	green = 0;
	blue = 0;

	selected = false;
	selectedRed = false;
	selectedGreen = false;
	selectedBlue = false;
	selectedEraser = false;
}

Rect::Rect(float x, float y, float red, float green, float blue){
	this->x = x;
	this->y = y;

	this->red = red;
	this->green = green;
	this->blue = blue;

	selected = false;
	selectedRed = false;
	selectedGreen = false;
	selectedBlue = false;
	selectedEraser = false;
}

Rect::Rect(float x, float y, float w, float h, float red, float green, float blue){
	this->x = x;
	this->y = y;

	this->red = red;
	this->green = green;
	this->blue = blue;

	this->w = w;
	this->h = h;

	selected = false;
	selectedRed = false;
	selectedGreen = false;
	selectedBlue = false;
	selectedEraser = false;
}

// void Rect::renderText(string text, float x, float y, void* font, float red, float green, float blue){
// 	glColor3f(1, 1, 1);
//     float offset = 0;
//     for (int i = 0; i < text.length(); i++) {
// 		for (int i = 0; i < 30; i++) {
// 			glRasterPos2f(-0.9 +offset, 0.9);
// 			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, "Welcome");
// 			int w = glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, "Welcome");
// 			offset += ((float)w / 640)*2;
// 		}
// 	}
// }

void Rect::bootChoices(){
	if (selected){
		glColor3f(0,0,0);
		glBegin(GL_LINES);
			glLineWidth(10);
			glVertex2f(x, y);
			glVertex2f(x+w, y);

			glVertex2f(x+w, y);
			glVertex2f(x+w, y-h);
			
			glVertex2f(x+w, y-h);
			glVertex2f(x, y-h);
			
			glVertex2f(x, y-h);
			glVertex2f(x, y);
		glEnd();
		
		glColor3f(red, green, blue);
		glBegin(GL_POLYGON);
			glVertex2f(x, y);
			glVertex2f(x+w, y);
			glVertex2f(x+w, y-h);
			glVertex2f(x, y-h);

		glEnd();
	}
	else{
		glColor3f(red, green, blue);

		glBegin(GL_POLYGON);

		glVertex2f(x, y);
		glVertex2f(x+w, y);
		glVertex2f(x+w, y-h);
		glVertex2f(x, y-h);

		glEnd();
	}
}

void Rect::drawing(){
	glColor3f(this->red, this->green,this-> blue);
	glPointSize(10);

	glBegin(GL_POINTS);

		glVertex2f(x, y);

	glEnd();
}

bool Rect::contains(float mx, float my){
	return (mx > this->x) && (mx < this->x + this->w) && (my < this->y) && (my > this->y - this->h);
}	

bool Rect::selectRed(float mx, float my){
	if ((mx > -0.9) && (mx < -0.9 + 0.1) && (my < 0.8) && (my > 0.8 - 0.1)){
		this->selected = true;
		this->selectedRed = true;
		//cout << "red selected" << endl;
		return true;
	}
}

bool Rect::selectGreen(float mx, float my){
	if ((mx > -0.75) && (mx < -0.75 + 0.1) && (my < 0.8) && (my > 0.8 - 0.1)){
		selected = true;
		selectedGreen = true;
		//cout << "green selected" << endl;
		return true;
	}
}

bool Rect::selectBlue(float mx, float my){
	if ((mx > -0.6) && (mx < -0.6 + 0.1) && (my < 0.8) && (my > 0.8 - 0.1)){
		selected = true;
		selectedBlue = true;
		//cout << "blue selected" << endl;
		return true;
	}
}

bool Rect::selectEraser(float mx, float my){
	if ((mx > 0.3) && (mx < 0.3 + 0.1) && (my < 0.8) && (my > 0.8 - 0.1)){
		selected = true;
		selectedEraser = true;
		//cout << "eraser selected" << endl;
		return true;
	}
}

bool Rect::sRed(){
	if (this->selectedRed){
		//cout << "red true" << endl;
		return true;
	}
}

bool Rect::sGreen(){
	if (selectedGreen){
		//cout << "green true" << endl;
		return true;
	}
}

bool Rect::sBlue(){
	if (selectedBlue){
		//cout << "blue true" << endl;
		return true;
	}
}

bool Rect::sEraser(){
	if (selectedEraser){
		//cout << "eraser true" << endl;
		return true;
	}
}

void Rect::deselect(){
	selected = false;
	selectedEraser = false;
	selectedRed = false;
	selectedGreen = false;
	selectedBlue = false;
}
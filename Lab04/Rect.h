#ifndef RECT_H
#define RECT_H

#include <iostream>
#include <string>

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

struct Rect {
	float x;
	float y;
	float w;
	float h;

	float red;
	float green; 
	float blue;

	bool selected;
	bool selectedRed;
	bool selectedGreen;
	bool selectedBlue;
	bool selectedEraser;

	// This is a default constructor (takes no parameters)	
	Rect();
	Rect(float x, float y, float red, float green, float blue);
	Rect(float x, float y, float w, float h, float red, float green, float blue);
	//void renderText(std::string text, float x, float y, void* font, float red, float green, float blue);
	void bootChoices();
	bool contains(float mx, float my);
	void deselect();
	//for drawing with color selected
	void drawing();
	//for selecting color
	bool selectRed(float mx, float my);
	bool selectGreen(float mx, float my);
	bool selectBlue(float mx, float my);
	bool selectEraser(float mx, float my);
	//for mouse motion function
	bool sRed();
	bool sGreen();
	bool sBlue();
	bool sEraser();
	//float motion(float mx, float my);
};

#endif

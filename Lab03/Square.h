#ifndef Square_H
#define Square_H


struct Square {
	float x;
	float y;
	float red;
	float green; 
	float blue;
	float w;
	float h;

	bool selected;

	Square(); // This is a default constructor (takes no parameters)
	Square(float x, float y, float w, float h);
	Square(float x, float y, float w, float h, float red, float green, float blue);

	void draw();
	bool contains(float x, float y);
	float dragX(float mx);
	float dragY(float my);

	bool containsResize(float x, float y);
	float sizeX(float mx);
	float sizeY(float my);
	//bool containsDrag(float x, float y);

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void select();
	void deselect();


};




#endif

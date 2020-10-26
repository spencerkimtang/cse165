#ifndef RECT_H
#define RECT_H


class Rect {
	float x;
	float y;

	float red;
	float green; 
	float blue;

	float w;
	float h;

	bool hit;

public:
	Rect();

	Rect(float, float, float, float);

	Rect(float, float, float, float, float, float, float);

	Rect(const Rect&);

	bool operator== (const Rect&);

	~Rect();

	void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
	void moveBullet();
	bool hitted();
	void fire();

	void draw();

	bool contains(float, float) const;

	float getX() const ;

	float getY() const ;

	float getW() const ;

	float getH() const ;

	float getR() const ;

	float getG() const ;

	float getB() const ;

	void setX(float x);

	void setY(float y);

	void setW(float w);

	void setH(float h);


};




#endif

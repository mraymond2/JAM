#include <iostream>
#include "RightTriangle.h"

RightTriangle::RightTriangle(float x, float y, float w, float h) : Shape(), x(x), y(y), w(w), h(h) {}

void RightTriangle::draw() const{
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + w, y - h);
	glVertex2f(x, y - h);
	glEnd();
}

bool RightTriangle::contains(float px, float py) const {
	return px >= x && px <= x + w && py <= y && py >= y - h;
}

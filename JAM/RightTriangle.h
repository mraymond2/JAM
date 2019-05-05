#ifndef RightTriangle_h
#define RightTriangle_h

#include "Shape.h"

#if defined WIN32
#include <freeglut.h>
#include "../windows/SOIL.h"
#elif defined __APPLE__
#include <GLUT/glut.h>
#include <SOIL.h>
#else
#include <GL/freeglut.h>
#include <SOIL.h>
#endif

class RightTriangle : public Shape{
public:
	float x;
	float y;
	float w;
	float h;
	//float stair1L = (-1 * (tan((19.654 * PI) / 180) * (currX + 0.9))) + masterY - 0.1;
	//float stair2L = (-1 * (tan((19.654 * PI) / 180) * (currX + 0.9))) + masterY - 0.1;
	//float stair1R = masterY + 0.15 - ((tan((19.654 * PI) / 180) * (currX + 1.6)));

	RightTriangle(float = 0, float = 0, float = 0, float = 0);
	void draw() const;
	bool contains(float, float) const;
};

#endif

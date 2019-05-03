#pragma once
#ifndef Bullet_h
#define Bullet_h

#include "TexRect.h"

class Bullet : public TexRect {
public:
	bool fired;
	int damage;
	float bulletspeed;

	Bullet(const char*, float, float, float, float, bool, int, float);

	void draw(float z);

};
#endif // !bullet_h

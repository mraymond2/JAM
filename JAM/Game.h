#pragma once
#ifndef Game_h
#define Game_h

#include "AnimatedRect.h"

class Game: private Timer{
public:
	bool samuscanbedamaged = true;
	bool metroidalive = true;
	//remove this later - actually dont
	bool metroidattacking = false;
	bool up = true;
	bool left = true;
	float currX = 0;
	float currY = 0;
	float metroidX = 0.7;
	float metroidY = 0.5;
	int energy = 99;
	int state = 0;
	float masterX = -0.1;
	float masterY = -0.375;
	float idlemasterW = 0.2;
	float idlemasterH = 0.39;
	float runmasterW = 0.25;
	float runmasterLH = 0.415;
	float runmasterRH = 0.395;
	int jumpState = 0;
	int currentroom = 1;

	TexRect* bg1;
	TexRect* bg2;
	AnimatedRect* Samus;
	AnimatedRect* idleR;
	AnimatedRect* idleL;
	AnimatedRect* runR;
	AnimatedRect* runL;
	Rect* bg1Wall;
	Rect* bg2Wall;
	AnimatedRect* Metroidspawn;

 
	Game();
	void draw();
	void handleDown(unsigned char key);
	void handleUp(unsigned char key);
	void updateX(float currX);
	void updateY(float currY);
	float checkRoom(float currX);
	void action();
	~Game();
};




#endif

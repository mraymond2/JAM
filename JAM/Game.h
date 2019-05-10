#pragma once
#ifndef Game_h
#define Game_h

#include "RightTriangle.h"
#include "TextBox.h"
#include "AnimatedRect.h"
#include <vector>

class Game: private Timer{
	std::vector<TexRect*> rightbullets;
	std::vector<TexRect*> leftbullets;
	RightTriangle* triangle;
	RightTriangle* triangle2;
	TextBox* Energylevel;
	AnimatedRect* Angelo;
	AnimatedRect* Energytank1;
	AnimatedRect* Energytank2;
	AnimatedRect* Energytank3;
	AnimatedRect* Energytank4;
	AnimatedRect* Energytank5;
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
	//AnimatedRect* GameOver;

	float masterX = -0.1;
	float masterY = -0.375;
	float idlemasterW = 0.2;
	float idlemasterH = 0.39;
	float runmasterW = 0.25;
	float runmasterLH = 0.415;
	float runmasterRH = 0.395;

public:
	//samus
	float currX = 0;
	float currY = 0;
	int energy = 5;
	int state = 0;
	int jumpState = 0;
	bool jump = false;
	int currentroom = 1;
	bool samusAlive = true;
	bool Grounded = true;
	bool lookingLeft = false;
	//angelo
	int angelohealth = 200;
	bool change = false;
	bool angeloalive = true;
	bool angleft = true;
	bool angup = true;
	//music
	bool alreadyplayedbrinstar = false;
	bool alreadyplayedmega = false;
	//metroid
	bool samuscanbedamaged = true;
	bool metroidalive = true;
	bool metroidattacking = false;
	bool up = true;
	bool left = true;
	float metroidX = 0.7;
	float metroidY = 0.5;


	Game();
	void music();
	void draw();
	void handleDown(unsigned char key);
	void handleUp(unsigned char key);
	// to be implemented void updateHealth(int energy);
	void updateX(float currX);
	void updateY(float currY);
	float checkRoom(float currX);
	void samusMove(float curX, float currY);
	void metroid(float mx, float my);
	void angelo(float angX, float angY);
	void action();
	~Game();
};




#endif

#include <iostream>
#include "App.h"

App* singleton;
int state = 0;
float masterX = -0.1;
float masterY = -0.3;
float idlemasterW = 0.2;
float idlemasterH = 0.39;
float runmasterW = 0.25;
float runmasterLH = 0.415;
float runmasterRH = 0.395;
//float currX = singleton->

void timer(int id) {
	// This will get called every 16 milliseconds after
	// you call it once

	// If you want to manipulate the app in here
	// do it through the singleton pointer



	singleton->redraw();

	glutTimerFunc(16, timer, id);
}

App::App(int argc, char** argv, int width, int height, const char* title) : GlutApp(argc, argv, width, height, title) {
	//Samus = new TexRect
	bg1 = new TexRect("/Schoolwork/CSE165/FinalProject/JAM-master/JAM/fight_room_background.png", -2, 1, 4, 2);
	idleR = new AnimatedRect("/Schoolwork/CSE165/FinalProject/JAM-master/JAM/IdleR.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	idleL = new AnimatedRect("/Schoolwork/CSE165/FinalProject/JAM-master/JAM/IdleL.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	runL = new AnimatedRect("/Schoolwork/CSE165/FinalProject/JAM-master/JAM/RunGunL.png", 1, 10, 65, true, true, masterX, masterY, runmasterW, runmasterLH);
	runR = new AnimatedRect("/Schoolwork/CSE165/FinalProject/JAM-master/JAM/RunGunR.png", 1, 10, 65, true, true, masterX, masterY, runmasterW, runmasterRH);

	singleton = this;
	timer(1);
}

void App::draw() {
	bg1->draw(0);

	if (state == 0 || state == 4) {
		idleR->draw(1);
	}
	else if (state == 1 || state == 5) {
		idleL->draw(1);
	}
	else if (state == 2) {
		float currX = singleton->runR->getX();
		currX += 0.012;
		singleton->runR->setX(currX);
		singleton->idleR->setX(currX);
		singleton->idleL->setX(currX);
		singleton->runL->setX(currX);
		currX = masterX;
		runR->draw(1);
	}
	else if (state == 3) {
		float currX = singleton->runR->getX();
		currX -= 0.012;
		singleton->runR->setX(currX);
		singleton->idleR->setX(currX);
		singleton->idleL->setX(currX);
		singleton->runL->setX(currX);
		currX = masterX;
		runL->draw(1);
	}
}

void App::keyDown(unsigned char key, float x, float y) {
	if (key == 27) {
		exit(0);
	}
	if (key == 'd') {
		state = 2;
		//std::cout << "Move right" << std::endl;
	}
	if (key == 'a') {
		state = 3;
		//std::cout << "Move left" << std::endl;
	}
	if (key == ' ') {
		if (state % 2 == 0) {
			state = 4;
		}
		else {
			state = 5;
		}

		std::cout << "Jump" << std::endl;
	}
	if (key == 'w') {

	}
}

void App::keyUp(unsigned char key, float x, float y) {
	if (key == 'd') {
		state = 0;
	}
	if (key == 'a') {
		state = 1;
	}
}

App::~App() {
	delete bg1;
	delete idleR;
	delete idleL;
	delete runR;
	delete runL;
}

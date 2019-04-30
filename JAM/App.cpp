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
int jumpState = 0;

void timer(int id) {
	// This will get called every 8 milliseconds after
	// you call it once

	float currX = singleton->runR->getX();
	float currY = singleton->runR->getY();

	if (state == 2) {
		currX += 0.012;
		singleton->runR->setX(currX);
		singleton->idleR->setX(currX);
		singleton->idleL->setX(currX);
		singleton->runL->setX(currX);
		currX = masterX;
	}

	if (state == 3) {
		currX -= 0.012;
		singleton->runR->setX(currX);
		singleton->idleR->setX(currX);
		singleton->idleL->setX(currX);
		singleton->runL->setX(currX);
		currX = masterX;
	}

	if (state == 4) {
		if (currY < 0.3 && jumpState == 1) {
			currY += 0.012;
			singleton->runR->setY(currY);
			singleton->idleR->setY(currY);
			singleton->idleL->setY(currY);
			singleton->runL->setY(currY);
		}
		else if (currY > -0.3 && jumpState == 2) {
			currY -= 0.012;
			singleton->runR->setY(currY);
			singleton->idleR->setY(currY);
			singleton->idleL->setY(currY);
			singleton->runL->setY(currY);
		}
		singleton->idleR->setY(currY);
	}

	if (state == 5) {
		if (currY < 0.3 && jumpState == 1) {
			currY += 0.012;
			singleton->runR->setY(currY);
			singleton->idleR->setY(currY);
			singleton->idleL->setY(currY);
			singleton->runL->setY(currY);
		}
		if (currY > -0.3 && jumpState == 2) {
			currY -= 0.012;
			singleton->runR->setY(currY);
			singleton->idleR->setY(currY);
			singleton->idleL->setY(currY);
			singleton->runL->setY(currY);
		}
		singleton->idleL->setY(currY);
	}

	singleton->redraw();

	glutTimerFunc(8, timer, id);
}

App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
	//Samus = new TexRect
	bg1 = new TexRect("/Users/Aaron Abon/Desktop/School/CSE_165/JAM/JAM/fight_room_background.png", -2, 1, 4, 2);
	idleR = new AnimatedRect("/Users/Aaron Abon/Desktop/School/CSE_165/JAM/JAM/IdleR.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	idleL = new AnimatedRect("/Users/Aaron Abon/Desktop/School/CSE_165/JAM/JAM/IdleL.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	runL = new AnimatedRect("/Users/Aaron Abon/Desktop/School/CSE_165/JAM/JAM/RunGunL.png", 1, 10, 65, true, true, masterX, masterY, runmasterW, runmasterLH);
	runR = new AnimatedRect("/Users/Aaron Abon/Desktop/School/CSE_165/JAM/JAM/RunGunR.png", 1, 10, 65, true, true, masterX, masterY, runmasterW, runmasterRH);

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
		runR->draw(1);
	}
	else if (state == 3) {
		runL->draw(1);
	}
}

void App::keyDown(unsigned char key, float x, float y){
    if (key == 27){
        exit(0);
    }
	if (key == 'd') {
		//std::cout << "Move right" << std::endl;
		state = 2;
	}
	if (key == 'a') {
		//std::cout << "Move left" << std::endl;
		state = 3;
	} 
	if (key == ' ') {
		//std::cout << "Jump" << std::endl;
		if (state % 2 == 0) {
			state = 4;
			jumpState = 1;
		}
		else {
			state = 5;
			jumpState = 1;
		}
	} 
}

void App::keyUp(unsigned char key, float x, float y) {
	if (key == 'd') {
		state = 0;
	}
	if (key == 'a') {
		state = 1;
	}
	if (key == ' ') {
		if (state % 2 == 0) {
			state = 4;
			jumpState = 2;
		}
		else {
			state = 5;
			jumpState = 2;
		}
	}
}

App::~App(){
	delete bg1;
	delete idleR;
	delete idleL;
	delete runR;
	delete runL;
}

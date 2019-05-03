#include "Game.h"

Game::Game() {
	Samus = new AnimatedRect("/Users/Mason/Documents/CSE165/JAM/IdleR.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	bg1 = new TexRect("/Users/Mason/Documents/CSE165/JAM/fight_room_background.png", -2, 1, 4, 2);
	bg2 = new TexRect("/Users/Mason/Documents/CSE165/JAM/FusionMain3.png", -2, 1, 4, 2);
	idleR = new AnimatedRect("/Users/Mason/Documents/CSE165/JAM/IdleR.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	idleL = new AnimatedRect("/Users/Mason/Documents/CSE165/JAM/IdleL.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	runL = new AnimatedRect("/Users/Mason/Documents/CSE165/JAM/RunGunL.png", 1, 10, 65, true, true, masterX, masterY, runmasterW, runmasterLH);
	runR = new AnimatedRect("/Users/Mason/Documents/CSE165/JAM/RunGunR.png", 1, 10, 65, true, true, masterX, masterY, runmasterW, runmasterRH);
}

void Game::draw() {
	if (currentroom == 1) {
		masterX = -0.1;
		masterY = -0.3;
		bg1->draw(0);
	}
	if (currentroom == 2) {
		masterX = -0.5;
		masterY = -0.5;
		bg2->draw(0);
	}

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

void Game::handleDown(unsigned char key) {
	if (key == 'd') {
		//std::cout << "Move right" << std::endl;
		state = 2;
	}
	if (key == 'j') {
		state = 9;
	}
	if (key == 'a') {
		//std::cout << "Move left" << std::endl;
		state = 3;
	}
	if (key == ' ') {
		//std::cout << "Jump" << std::endl;
		if (state %2 == 0) {
			state = 4;
			jumpState = 1;
		}
		else {
			state = 5;
			jumpState = 1;
		}
	}
}
void Game::handleUp(unsigned char key) {
	if (key == 'd') {
		state = 0;
	}
	if (key == 'c') {
		currentroom = 2;
	}
	if (key == 'v') {
		currentroom = 1;
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

void Game::updateX(float currX) {
	runR->setX(currX);
	idleR->setX(currX);
	idleL->setX(currX);
	runL->setX(currX);
}

void Game::updateY(float currY) {
	runR->setY(currY);
	idleR->setY(currY);
	idleL->setY(currY);
	runL->setY(currY);
}

float Game::checkScreen(float currX) {
	if (currX > 0){
		if (currX > 2) {
			currentroom = 2;
			return (currX - 4);
		}
		else return currX;
	}
	else if (currX < 0) {
		if (currX < -2 - idleL->getW()) {
			currentroom = 1;
			return (currX + 4);
		}
		else return currX;
	}
	
}
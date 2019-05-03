#include "Game.h"

Game::Game() {
	Samus = new AnimatedRect("../IdleR.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	bg1 = new TexRect("../fight_room_background.png", -2, 1, 4, 2);
	bg2 = new TexRect("../FusionMain3.png", -2, 1, 4, 2);
	idleR = new AnimatedRect("../IdleR.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	idleL = new AnimatedRect("../IdleL.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	runL = new AnimatedRect("../RunGunL.png", 1, 10, 65, true, true, masterX, masterY, runmasterW, runmasterLH);
	runR = new AnimatedRect("../RunGunR.png", 1, 10, 65, true, true, masterX, masterY, runmasterW, runmasterRH);
	bg1Wall = new Rect(-2.1, 1, 0.4, 2);
	bg2Wall = new Rect(1.9, 1, 0.4, 2);
	setRate(16);
}

void Game::action() {
	float currX = runR->getX();
	float currY = runR->getY();
	


	if (state == 2) {
		if (currentroom == 1) {
			currX += 0.012;
		}
		if (currentroom == 2 && !bg2Wall->contains(currX + runR->getW(), currY)) {
			currX += 0.012;
		}
		currX = checkScreen(currX);
		updateX(currX);
		currX = masterX;
	}

	if (state == 3) {
		if (currentroom == 2) {
			currX -= 0.012;
		}
		if (currentroom == 1 && !bg1Wall->contains(currX, currY)) {
			currX -= 0.012;
		}
		currX = checkScreen(currX);
		updateX(currX);
		currX = masterX;
	}



	if (state == 4) {
		if (currY < 0.3 && jumpState == 1) {
			currY += 0.012;
			updateY(currY);
		}
		else if (currY > -0.3 && jumpState == 2) {
			currY -= 0.012;
			updateY(currY);
		}
		idleR->setY(currY);
	}

	if (state == 5) {
		if (currY < 0.3 && jumpState == 1) {
			currY += 0.012;
			updateY(currY);
		}
		if (currY > -0.3 && jumpState == 2) {
			currY -= 0.012;
			updateY(currY);
		}
		idleL->setY(currY);
	}
	glutPostRedisplay();
}

void Game::draw() {
	if (currentroom == 1) {
		masterX = -0.1;
		masterY = -0.3;
		bg1->draw(0);
		bg1Wall->draw();
	}
	if (currentroom == 2) {
		masterX = -0.5;
		masterY = -0.5;
		bg2->draw(0);
		bg2Wall->draw();
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
	if (currX > 2) {
		currentroom = 2;
		return (currX - 4);
	}

	if (currX < -2 - idleL->getW()) {
		currentroom = 1;
		return (currX + 4);
	}
		else return currX;
}

Game::~Game()
{
	delete  bg1;
	delete bg2;
	delete Samus;
	delete idleR;
	delete idleL;
	delete runR;
	delete runL;
	delete bg1Wall;
	delete bg2Wall;
}
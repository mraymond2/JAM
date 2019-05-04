#include "Game.h"
#include <mmsystem.h>
#include <mciapi.h>
#include <deque>
#include <string>

#pragma comment(lib, "Winmm.lib")

#include "Game.h"

#include <mmsystem.h>
#include <mciapi.h>

#pragma comment(lib, "Winmm.lib")


Game::Game() {
	Angelo = new AnimatedRect("../angelo.png", 1, 1, 65, true, true, 0.7, 0.5, 0.45, 0.45);
	Energytank = new AnimatedRect("../energytanksprite.png", 1, 3, 65, true, true, -1.975, .95, 0.2, 0.2);
	Samus = new AnimatedRect("../IdleR.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	bg1 = new TexRect("../fight_room_background.png", -2, 1, 4, 2);
	bg2 = new TexRect("../FusionMain3.png", -2, 1, 4, 2);
	idleR = new AnimatedRect("../IdleR.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	idleL = new AnimatedRect("../IdleL.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	runL = new AnimatedRect("../RunGunL.png", 1, 10, 65, true, true, masterX, masterY, runmasterW, runmasterLH);
	runR = new AnimatedRect("../RunGunR.png", 1, 10, 65, true, true, masterX, masterY, runmasterW, runmasterRH);
	Metroidspawn = new AnimatedRect("../ms1.png", 2, 5, 65, true, true, 0.7, 0.5, 0.3, 0.3);
	bg1Wall = new Rect(-2, 1, 0.4, 2);
	bg2Wall = new Rect(1.9, 1, 0.1, 2);
	setRate(8);
	start();
}

void Game::draw() {
	if (currentroom == 1) {
		masterX = -0.1;
		masterY = -0.3;
		bg1->draw(0);
		bg1Wall->draw();
		if (metroidalive) {
			Metroidspawn->draw(1);
		}
	}
	if (currentroom == 2) {
		masterX = -0.5;
		masterY = -0.5;
		bg2->draw(0);
		bg1Wall->draw();
		bg2Wall->draw();
		
		if (angeloalive) {
			Angelo->draw(1);
		}
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
	Energytank->draw(1);

	
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
		if (state % 2 == 0) {
			state = 4;
			jumpState = 1;
		}
		else {
			state = 5;
			jumpState = 1;
		}
	}
	if (key == 'f') {
		metroidalive = false;
	}

	if (key == 'o') {
		angelohealth = angelohealth - 50;
		if (angelohealth <= 50) {
			if (change == false) {
				Angelo->setMap("../sansgelo.png", 1, 1);
				change == true;
			}
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

float Game::checkRoom(float currX) {
	if (currX > 2) {
		currentroom = 2;
		return (currX - 3.5);
	}

	if (currX < -2 - idleL->getW()) {
		currentroom = 1;
		return (currX + 4);
	}
	else return currX;
}

void Game::music() {
	if (currentroom == 1) {
		if (alreadyplayedbrinstar == false) {
			mciSendString("close mp3", NULL, 0, NULL);
			mciSendString("open \"../brinstardepths.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
			mciSendString("play mp3", NULL, 0, NULL);
			alreadyplayedbrinstar = true;
		}
	}
	if (currentroom == 2) {
		if (alreadyplayedbrinstar == true && alreadyplayedmega == false) {
			mciSendString("close mp3", NULL, 0, NULL);
			mciSendString("open \"../megalovania.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
			mciSendString("play mp3", NULL, 0, NULL);
			alreadyplayedmega = true;
		}
	}
}



void Game::samusMove(float currX, float currY) {
	//run right
	if (state == 2) {
		if (currentroom == 1) {
			currX += 0.012;
		}
		if (currentroom == 2 && !bg2Wall->contains(currX + runR->getW(), currY)) {
			currX += 0.012;
		}
		currX = checkRoom(currX);
		updateX(currX);
		currX = masterX;
	}
	//run left
	if (state == 3) {
		if (currentroom == 2 && !bg1Wall->contains(currX, currY)) {
			currX -= 0.012;
		}
		if (currentroom == 1 && !bg1Wall->contains(currX, currY)) {
			currX -= 0.012;
		}
		currX = checkRoom(currX);
		updateX(currX);
		currX = masterX;
	}
	//jump facing right
	if (state == 4) {
		if (currY < 0.2 && jumpState == 1) {
			currY += 0.018;
			updateY(currY);
		}
		else {
			jumpState = 2;
		}
		if (currY > -0.375 && jumpState == 2) {
			currY -= 0.018;
			updateY(currY);
		}
		idleR->setY(currY);
	}
	//jump facing left
	if (state == 5) {
		if (currY < 0.2 && jumpState == 1) {
			currY += 0.018;
			updateY(currY);
		}
		else {
			jumpState = 2;
		}
		if (currY > -0.375 && jumpState == 2) {
			currY -= 0.018;
			updateY(currY);
		}
		idleL->setY(currY);
	}
}

void Game::metroid(float mx, float my) {
	if (metroidalive == 1) {
		//left-right movement
		if (left)
			mx -= 0.01;
		else
			mx += 0.01;
		if (mx < -1) {
			left = false;
		}
		if (mx > 1.5 - Metroidspawn->getW()) {
			left = true;
		}
		//up-down movement
		if (!up)
			my -= 0.005;
		else
			my += 0.005;
		if (my < -0.4) {
			up = true;
		}
		if (my > 0.5 - Metroidspawn->getH()) {
			up = false;
		}


		Metroidspawn->setX(mx);
		Metroidspawn->setY(my);

		if (samuscanbedamaged) {
			if (Metroidspawn->contains(idleR->getX() + (idlemasterW / 2), idleR->getY() - (idlemasterH / 3.7))) {
				energy -= 5;
				samuscanbedamaged = false;
				std::cout << "Samus got hit. Energy is: " << energy << std::endl;
			}
		}
		else {
			if (!Metroidspawn->contains(idleR->getX() + (idlemasterW / 2), idleR->getY() - (idlemasterH / 3.7))) {
				samuscanbedamaged = true;
			}
		}
	}
}

void Game::angelo(float mx, float my) {
	//left-right movement
	if (left)
		mx -= 0.01;
	else
		mx += 0.01;
	if (mx < -1) {
		left = false;
	}
	if (mx > 1.5 - Angelo->getW()) {
		left = true;
	}
	//up-down movement
	if (!up)
		my -= 0.005;
	else
		my += 0.005;
	if (my < -0.4) {
		up = true;
	}
	if (my > 0.5 - Angelo->getH()) {
		up = false;
	}

	Angelo->setX(mx);
	Angelo->setY(my);

}

void Game::action() {
	currX = runR->getX();
	currY = runR->getY();
	float mx = Metroidspawn->getX();
	float my = Metroidspawn->getY();
	float angX = Angelo->getX();
	float angY = Angelo->getY();

	
	music();
	samusMove(currX, currY);
	metroid(mx, my);
	angelo(angX, angY);
	glutPostRedisplay();
}

Game::~Game() {
	delete bg1;
	delete bg2;
	delete Samus;
	delete idleR;
	delete idleL;
	delete runR;
	delete runL;
	delete bg1Wall;
	delete bg2Wall;
	delete Metroidspawn;
	delete Angelo;
	delete Energytank;

}


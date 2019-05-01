#include "Game.h"

Game::Game() {
	Samus = new AnimatedRect("/Schoolwork/CSE165/MetroidProject/JAM/JAM/IdleR.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	bg1 = new TexRect("/Schoolwork/CSE165/MetroidProject/JAM/JAM/fight_room_background.png", -2, 1, 4, 2);
	bg2 = new TexRect("/Schoolwork/CSE165/MetroidProject/JAM/JAM/FusionMain3.png", -2, 1, 4, 2);
	idleR = new AnimatedRect("/Schoolwork/CSE165/MetroidProject/JAM/JAM/IdleR.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	idleL = new AnimatedRect("/Schoolwork/CSE165/MetroidProject/JAM/JAM/IdleL.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	runL = new AnimatedRect("/Schoolwork/CSE165/MetroidProject/JAM/JAM/RunGunL.png", 1, 10, 65, true, true, masterX, masterY, runmasterW, runmasterLH);
	runR = new AnimatedRect("/Schoolwork/CSE165/MetroidProject/JAM/JAM/RunGunR.png", 1, 10, 65, true, true, masterX, masterY, runmasterW, runmasterRH);
}

void Game::draw() {

	if (currentroom == 1) {
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

void Game::handledown(unsigned char key) {
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
void Game::handleup(unsigned char key) {
	if (key == 'd') {
		state = 0;
	}
	if (key == 'c') {
		currentroom = 2;
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
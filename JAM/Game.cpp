#include "Game.h"

Game::Game() {
	bg1 = new TexRect("/Users/Aaron Abon/Desktop/School/CSE_165/JAM/JAM/fight_room_background.png", -2, 1, 4, 2);
	idleR = new AnimatedRect("/Users/Aaron Abon/Desktop/School/CSE_165/JAM/JAM/IdleR.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	idleL = new AnimatedRect("/Users/Aaron Abon/Desktop/School/CSE_165/JAM/JAM/IdleL.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	runL = new AnimatedRect("/Users/Aaron Abon/Desktop/School/CSE_165/JAM/JAM/RunGunL.png", 1, 10, 65, true, true, masterX, masterY, runmasterW, runmasterLH);
	runR = new AnimatedRect("/Users/Aaron Abon/Desktop/School/CSE_165/JAM/JAM/RunGunR.png", 1, 10, 65, true, true, masterX, masterY, runmasterW, runmasterRH);
}

Game::draw() {
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

Game::handledown(unsigned char key) {
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
Game::handleup(unsigned char key) {
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
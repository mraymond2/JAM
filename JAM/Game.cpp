#include "Game.h"
#include <mmsystem.h>
#include <mciapi.h>
#include <deque>
#include <string>
#include <cmath>
#include <vector>

#define PI 3.1415926

#pragma comment(lib, "Winmm.lib")

#include "Game.h"
#include <mmsystem.h>
#include <mciapi.h>

#pragma comment(lib, "Winmm.lib")


Game::Game() {
	//energy tanks + text
	Energylevel = new TextBox("Energy:", -1.97, .87, GLUT_BITMAP_HELVETICA_18, 1, 1, 1, 500);
	Energytank1 = new AnimatedRect("../energytanksprite.png", 1, 3, 65, true, true, -1.7, .94, 0.1, 0.1);
	Energytank2 = new AnimatedRect("../energytanksprite.png", 1, 3, 65, true, true, -1.59, .94, 0.1, 0.1);
	Energytank3 = new AnimatedRect("../energytanksprite.png", 1, 3, 65, true, true, -1.48, .94, 0.1, 0.1);
	Energytank4 = new AnimatedRect("../energytanksprite.png", 1, 3, 65, true, true, -1.37, .94, 0.1, 0.1);
	Energytank5 = new AnimatedRect("../energytanksprite.png", 1, 3, 65, true, true, -1.26, .94, 0.1, 0.1);
	//game over
	gameOverText = new TextBox("GAME OVER", -0.25, 0, GLUT_BITMAP_HELVETICA_18, 1, 1, 1, 500);
	//angelo
	Angelo = new AnimatedRect("../angelo.png", 1, 1, 65, true, true, 0.7, 0.5, 0.45, 0.45);
	//samus
	Samus = new AnimatedRect("../IdleR.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	//backgrounds
	bg1 = new TexRect("../fight_room_background.png", -2, 1, 4, 2);
	bg2 = new TexRect("../FusionMain3.png", -2, 1, 4, 2);
	//samusrun
	idleR = new AnimatedRect("../IdleR.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	idleL = new AnimatedRect("../IdleL.png", 1, 1, 65, true, true, masterX, masterY, idlemasterW, idlemasterH);
	runL = new AnimatedRect("../RunGunL.png", 1, 10, 65, true, true, masterX, masterY, runmasterW, runmasterLH);
	runR = new AnimatedRect("../RunGunR.png", 1, 10, 65, true, true, masterX, masterY, runmasterW, runmasterRH);
	//metroid
	Metroidspawn = new AnimatedRect("../ms1.png", 2, 5, 65, true, true, 0.7, 0.5, 0.3, 0.3);
	//grounds
	bg1Wall = new Rect(-2, 1, 0.4, 2);
	bg2Wall = new Rect(1.9, 1, 0.1, 2);
	ground1 = new Rect(-2, -0.75, 4, 0.250);
	ground2 = new Rect(-2, -0.75, 0.90, 0.250);
	ground3 = new Rect(-1.25, -0.95, 4, 0.1);
	triangle = new RightTriangle(-1.6, -0.5, 0.7, 0.25);
	triangle2 = new RightTriangle(-1.11, -0.745, 0.53, 0.21);
	//GameOver = new AnimatedRect("../gameoversheet.png", 10, 8, 100, true , true, -2, 1, 4, 2);
	//GameOver->playOnce();
	setRate(8);
	start();
}


void Game::draw() {
	if (energy > 0) {
		Energylevel->draw();
		if (currentroom == 1) {
			//triangle->draw();
			masterX = -0.1;
			masterY = -0.3;
			bg1->draw(0);
			bg1Wall->draw();
			ground1->draw();

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
			ground2->draw();
			ground3->draw();

			if (angeloalive) {
				Angelo->draw(1);
			}
		}

		if (state == 0) {
			idleR->draw(0.75);
		}
		else if (state == 1) {
			idleL->draw(0.75);
		}
		else if (state == 2) {
			runR->draw(0.75);
		}
		else if (state == 3) {
			runL->draw(0.75);
		}

		Energytank1->draw(1);
		if (energy > 1) {
			Energytank2->draw(1);
			if (energy > 2) {
				Energytank3->draw(1);
				if (energy > 3) {
					Energytank4->draw(1);
					if (energy > 4) {
						Energytank5->draw(1);
					}
				}
			}
		}
	}
	if (energy < 0) {
		//GameOver->draw(1);
		gameOverText->draw();
	}
	for (std::vector<TexRect*>::iterator i = rightbullets.begin(); i != rightbullets.end(); ++i) {
		(*i)->draw(1);
	}
	for (std::vector<TexRect*>::iterator i = leftbullets.begin(); i != leftbullets.end(); ++i) {
		(*i)->draw(1);
	}

}


void Game::handleDown(unsigned char key) {
	if (key == 'd') {
		//std::cout << "Move right" << std::endl;
		lookingLeft = false;
		state = 2;
	}
	if (key == 'a') {
		//std::cout << "Move left" << std::endl;
		lookingLeft = true;
		state = 3;
	}
	if (key == 'w' && jump == false) {
		//std::cout << "Jump" << std::endl;
		jump = true;
		jumpState = 1;
	}
	if (key == ' ') {
		if (state == 2 || state == 0) {
			rightbullets.push_back(new TexRect("../bulletcircle.png", currX, (currY - 0.1), 0.1, 0.1));
		}
		if (state == 3 || state == 1) {
			leftbullets.push_back(new TexRect("../bulletcircle.png", currX, (currY - 0.1), 0.1, 0.1));
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
		if (angelohealth <= 500) {
			if (change == false) {
				Angelo->setMap("../sansgelo.png", 1, 1);
				change = true;
			}
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
			if (triangle->contains(currX, currY - idleL->getH())/*currX < -0.95 && currX > -1.6*/) {
				currY = masterY + 0.15 - ((tan((19.654 * PI) / 180) * (currX + 1.6)));
				updateY(currY);
			}
		}
		if (currentroom == 2 && !bg2Wall->contains(currX + runR->getW(), currY)) {
			currX += 0.012;
			if (triangle2->contains(currX, currY - idleL->getH()/*currX < -0.65 && currX > -1.11*/)) {
				currY = masterY + 0.1 - ((tan((21.615 * PI) / 180) * (currX + 1.11)));
				updateY(currY);
			}
		}
		currX = checkRoom(currX);
		updateX(currX);
		currX = masterX;
	}
	//run left
	if (state == 3) {
		if (currentroom == 1 && !bg1Wall->contains(currX, currY)) {
			currX -= 0.012;
			if (currX < -0.95 && currX > -1.65) {
				currY = (-1 * (tan((19.654 * PI) / 180) * (currX + 0.9))) + masterY - 0.1;
				updateY(currY);
			}
		}
		if (currentroom == 2 && !bg1Wall->contains(currX, currY)) {
			currX -= 0.012;
			if (currX < -0.65 && currX > -1.2) {
				currY = (-1 * (tan((21.615 * PI) / 180) * (currX + 0.58))) + masterY - 0.12;
				updateY(currY);
			}
		}
		currX = checkRoom(currX);
		updateX(currX);
		currX = masterX;
	}
	//jump
	if (jump == true) {
		if (currentroom == 1) {
			if (currY < 0.2 && jumpState == 1) {
				currY += 0.018;
				updateY(currY);
			}
			else if (!ground1->contains(currX, idleR->getY() - 0.4) && jumpState == 2) {
				currY -= 0.018;
				updateY(currY);
			}
			else if (currY <= ground1->contains(currX, idleR->getY() - 0.4) && jumpState == 2) {
				jump = false;
			}
			else {
				jumpState = 2;
			}
		}
		if (currentroom == 2) {
			if (currX < -0.65) {
				if (currY < 0.2 && jumpState == 1) {
					currY += 0.018;
					updateY(currY);
				}
				else if (!ground2->contains(currX, idleR->getY() - 0.4) && jumpState == 2) {
					currY -= 0.018;
					updateY(currY);
				}
				else if (currY <= ground2->contains(currX, idleR->getY() - 0.4) && jumpState == 2) {
					jump = false;
				}
				else {
					jumpState = 2;
				}
			}
			else {
				if (currY < 0 && jumpState == 1) {
					currY += 0.018;
					updateY(currY);
				}
				else if (!ground3->contains(currX, idleR->getY() - 0.4) && jumpState == 2) {
					currY -= 0.018;
					updateY(currY);
				}
				else if (currY <= ground3->contains(currX, idleR->getY() - 0.4) && jumpState == 2) {
					jump = false;
				}
				else {
					jumpState = 2;
				}
			}
		}
		idleR->setY(currY);
	}
}


void Game::angelo(float mx, float my) {
	if (angelohealth < 0) {
		angelocanbedamaged = false;
		angeloalive = false;
	}
	if (angeloalive == true) {
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

		if (currentroom == 2) {
			if (samuscanbedamaged) {
				if (Angelo->contains(idleR->getX() + (idlemasterW / 2), idleR->getY() - (idlemasterH / 3.7))) {
					energy -= 1;
					samuscanbedamaged = false;
					std::cout << "Samus got hit. Energy is: " << energy << std::endl;
				}
			}
			else {
				if (!Angelo->contains(idleR->getX() + (idlemasterW / 2), idleR->getY() - (idlemasterH / 3.7))) {
					samuscanbedamaged = true;
				}
			}
		}
	}
}


void Game::metroid(float mx, float my) {
	if (metroidhealth < 0) {
		metroidcanbedamaged = false;
		metroidalive = false;
	}
	if (metroidalive == true) {
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
				energy -= 1;
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

void Game::action() {
	currX = runR->getX();
	currY = runR->getY();
	float mx = Metroidspawn->getX();
	float my = Metroidspawn->getY();
	float angX = Angelo->getX();
	float angY = Angelo->getY();

	for (std::vector<TexRect*>::iterator i = leftbullets.begin(); i != leftbullets.end(); ++i) {

		(*i)->setX((*i)->getX() - .075);

		if (currentroom == 2) {

			if (angeloalive == true) {
				if (angelocanbedamaged == true) {
					if (Angelo->contains((*i)->getX(), (*i)->getY())) {
						angelohealth -= bulletdamage;
						std::cout << "angelo got hit and health is " << angelohealth << std::endl;
						angelocanbedamaged = false;

					}
				}
				else {
					if (!Angelo->contains((*i)->getX(), (*i)->getY())) {
						angelocanbedamaged = true;
					}
				}
			}
		}

		if (metroidalive) {
			if (metroidcanbedamaged == true) {
				if (Metroidspawn->contains((*i)->getX(), (*i)->getY())) {
					metroidhealth -= bulletdamage;
					std::cout << "Metroid got hit and health is " << metroidhealth << std::endl;
					metroidcanbedamaged = false;

				}
			}
			else {
				if (!Metroidspawn->contains((*i)->getX(), (*i)->getY())) {
					metroidcanbedamaged = true;
				}
			}
		}


	}
	for (std::vector<TexRect*>::iterator i = rightbullets.begin(); i != rightbullets.end(); ++i) {

		(*i)->setX((*i)->getX() + .075);

		if (currentroom == 2) {
			if (angeloalive == true) {
				if (angelocanbedamaged == true) {
					if (Angelo->contains((*i)->getX(), (*i)->getY())) {
						angelohealth -= bulletdamage;
						std::cout << "angelo got hit and health is " << angelohealth << std::endl;
						angelocanbedamaged = false;

					}
				}
				else {
					if (!Angelo->contains((*i)->getX(), (*i)->getY())) {
						angelocanbedamaged = true;
					}
				}
			}
		}

		if (metroidalive) {
			if (metroidcanbedamaged == true) {
				if (Metroidspawn->contains((*i)->getX(), (*i)->getY())) {
					metroidhealth -= bulletdamage;
					std::cout << "Metroid got hit and health is " << metroidhealth << std::endl;
					metroidcanbedamaged = false;

				}

			}

			else {
				if (!Metroidspawn->contains((*i)->getX(), (*i)->getY())) {
					metroidcanbedamaged = true;
				}
			}
		}
	}

	music();
	samusMove(currX, currY);
	metroid(mx, my);
	angelo(angX, angY);
	glutPostRedisplay();
}
Game::~Game() {
	delete triangle;
	delete triangle2;
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
	delete Energytank1;
	delete Energytank2;
	delete Energytank3;
	delete Energytank4;
	delete Energytank5;

	//delete GameOver;

}


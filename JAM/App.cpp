#include <iostream>
#include "App.h"

App* singleton;

void timer(int id) {
	// This will get called every 8 milliseconds after
	// you call it once

	float currX = singleton->game->runR->getX();
	float currY = singleton->game->runR->getY();
	


	if (singleton->game->state == 2) {
		currX += 0.012;
		currX = singleton->game->checkScreen(currX);
		singleton->game->updateX(currX);
		currX = singleton->game->masterX;
	}

	if (singleton->game->state == 3) {
		currX -= 0.012;
		currX = singleton->game->checkScreen(currX);
		singleton->game->updateX(currX);
		currX = singleton->game->masterX;
	}



	if (singleton->game->state == 4) {
		if (currY < 0.3 && singleton->game->jumpState == 1) {
			currY += 0.012;
			singleton->game->updateY(currY);
		}
		else if (currY > -0.3 && singleton->game->jumpState == 2) {
			currY -= 0.012;
			singleton->game->updateY(currY);
		}
		singleton->game->idleR->setY(currY);
	}
	if (singleton->game->state == 5) {
		if (currY < 0.3 && singleton->game->jumpState == 1) {
			currY += 0.012;
			singleton->game->updateY(currY);
		}
		if (currY > -0.3 && singleton->game->jumpState == 2) {
			currY -= 0.012;
			singleton->game->updateY(currY);
		}
		singleton->game->idleL->setY(currY);
	}



	singleton->redraw();

	glutTimerFunc(8, timer, id);
}

App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
	game = new Game;
	
	singleton = this;
	timer(1);
}

void App::draw() {
	game->draw();
}

void App::keyDown(unsigned char key, float x, float y){
	if (key == 27) {
		exit(0);
	}
	else
		game->handleDown(key);
}

void App::keyUp(unsigned char key, float x, float y) {
	game->handleUp(key);
}

App::~App(){
	delete game;
}

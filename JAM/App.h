#ifndef App_h
#define App_h

#include "GlutApp.h"
#include "AnimatedRect.h"

class App: public GlutApp {
	TexRect* bg1;
	AnimatedRect* idleR;
	AnimatedRect* idleL;
	AnimatedRect* runR;
	AnimatedRect* runL;

public:
    App(int argc, char** argv, int width, int height, const char* title);
    
    void draw();
    
    void keyDown(unsigned char key, float x, float y);

	void keyUp(unsigned char key, float x, float y);
	
	friend void timer(int);

    ~App();
};

#endif

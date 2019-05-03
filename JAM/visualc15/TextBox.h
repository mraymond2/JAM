#ifndef TextBox_h
#define TextBox_h

#include <string>
#include "Shape.h"

class TextBox : public Shape {
public:
	std::string text;
	float x;
	float y;

	void* font;
	float r;
	float g;
	float b;
	int width;

	TextBox(

		const char* = "My TextBox",
		float = 0,
		float = 0,
		void* = GLUT_BITMAP_HELVETICA_18,
		float = 1,
		float = 1,
		float = 1,
		int = 800
	);

	void draw() const;
};

#endif /* TextBox_hpp */

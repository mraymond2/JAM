#include "TextBox.h"
#include <iostream>

TextBox::TextBox(
	const char* text,
	float x,
	float y,
	void* font,
	float r,
	float g,
	float b,
	int width
) :

	Shape(),
	text(text),
	x(x),
	y(y),
	font(font),
	r(r),
	g(g),
	b(b),
	width(width)
{}

void TextBox::draw() const {
	glColor3f(r, g, b);
	float offset = 0;
	for (int i = 0; i < text.length(); i++) {
		glRasterPos2f(x + offset, y);
		glutBitmapCharacter(font, text[i]);
		int w = glutBitmapWidth(font, text[i]);
		offset += ((float)w / width) * 2;
	}
}

#include "Button.h"

Button::Button(int xStart, int yStart, int width, int height) {
	_xStart = xStart;
	_width = width;
	_yStart = yStart;
	_height = height;
}

Button::~Button() {}

int	Button::getHeight() const {
	return (_height);
}
int	Button::getWidth() const {
	return (_width);
}

int	Button::getxStart() const {
	return (_xStart);
}
int	Button::getyStart() const {
	return (_yStart);
}
#pragma once

class Button
{
public:
	Button(int, int, int, int);
	~Button();
	int getxStart() const;
	int	getyStart() const;
	int	getHeight() const;
	int	getWidth() const;

private:
	int _xStart;
	int	_yStart;

	int	_height;
	int	_width;
};
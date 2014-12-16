#pragma once

# include "World.h"
# include "Button.h"

class GuiPause
{
public:
	GuiPause(World &, const sf::Texture * const texture);
	~GuiPause();

	enum GuiPauseButton
	{
		CONTINUE,
		EXIT,
		MAX
	};

	struct GuiClick
	{
		int posX;
		int posY;
	};

	bool				getIsActive() const;
	bool				doAction(const GuiPauseButton &);
	GuiPauseButton		isPressed(const GuiClick &) const;

private:
	//sf::Texture *				_texture;
	bool						_isActive;
	std::vector<Button>			_button;
};

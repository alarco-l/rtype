#pragma once

# include "World.h"
# include "Button.h"

enum GuiMenuButton
{
	CONNECT,
	EXIT,
	MAX
};

struct GuiClick
{
	int posX;
	int posY;
};

class GuiMenu
{
public:
	GuiMenu(World &, const sf::Texture * const texture);
	~GuiMenu();
	bool				getIsActive() const;
	bool				doAction(const GuiMenuButton &);
	GuiMenuButton		isPressed(const GuiClick &) const;

private:
	bool				_isActive;
	std::vector<Button> _button;
};

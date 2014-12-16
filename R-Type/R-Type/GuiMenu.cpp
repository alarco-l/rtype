#include "GuiMenu.h"
#include <iostream>

GuiMenu::GuiMenu(World &world, const sf::Texture * const texture)
{
	world.createStaticEntity(texture, sf::Vector2f(0.0f, 0.0f));
	_button.push_back(Button(720, 510, 513, 90));
	_button.push_back(Button(802, 656, 513, 90));
	_isActive = true;
}

GuiMenu::~GuiMenu()
{
}

bool	GuiMenu::getIsActive() const {
	return (_isActive);
}

GuiMenu::GuiMenuButton	GuiMenu::isPressed(const GuiClick &cl) const {
	unsigned int rank = -1;
	while (++rank < MAX) {
		if (cl.posX >= _button[rank].getxStart() && cl.posX <= (_button[rank].getxStart() + _button[rank].getWidth()) &&
			cl.posY >= _button[rank].getyStart() && cl.posY <= (_button[rank].getyStart() + _button[rank].getHeight())) {
			return ((GuiMenuButton)rank);
		}
	}
	return (MAX);
}

bool		GuiMenu::doAction(const GuiMenuButton &bt) {
	_isActive = false;
	if (bt == EXIT)
		return (false);
	else
		return (true);
}
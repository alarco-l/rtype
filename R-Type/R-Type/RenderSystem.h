#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "World.h"

class								RenderSystem
{
public:
	static void						update(sf::RenderWindow *window, World &world);
private:
	RenderSystem();
	RenderSystem(const RenderSystem &rhs);
	RenderSystem &operator=(const RenderSystem &rhs);
};
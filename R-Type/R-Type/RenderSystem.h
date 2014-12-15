#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "World.h"

class								RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();
	void							update(sf::RenderWindow &window, World &world) const;
private:
	RenderSystem(const RenderSystem &rhs);
	RenderSystem &operator=(const RenderSystem &rhs);
};
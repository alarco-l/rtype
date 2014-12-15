#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "ISystem.h"

class								RenderSystem : public ISystem
{
public:
	RenderSystem();
	~RenderSystem();
	void							update(sf::RenderWindow &window, World &world) const;
	void							update(World &world, const sf::Time &elapsed) const;
private:
	RenderSystem(const RenderSystem &rhs);
	RenderSystem &operator=(const RenderSystem &rhs);
};
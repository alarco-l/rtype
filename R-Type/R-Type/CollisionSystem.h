#pragma once

#include "World.h"

class										CollisionSystem
{
public:
	CollisionSystem(const sf::Vector2u &precision, const sf::Vector2u &displaySize);
	~CollisionSystem();
	void									update(World &world) const;
private:
	CollisionSystem(const CollisionSystem &rhs);
	CollisionSystem &operator=(const CollisionSystem &rhs);

	sf::Vector2f							_cellSize;
	std::vector<std::vector<unsigned int> >	_collisionGrid;
};
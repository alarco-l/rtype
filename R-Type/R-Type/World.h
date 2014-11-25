#pragma once

#include "RenderComponent.hpp"
#include "MovementComponent.hpp"
#include "PositionComponent.hpp"

class									World
{
public:
	World();
	~World();
	void								createEntity();
	void								destroyEntity(const unsigned int id);
private:
	World(const World &rhs);
	const World &operator=(const World &rhs);
};
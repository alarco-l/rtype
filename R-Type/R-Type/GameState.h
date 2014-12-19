#pragma once

#include "AState.h"

class							GameState : public AState
{
public:
	GameState(Game *game);
	~GameState();

	bool						initialize(ResourceManager &resourceManager);
	bool						handleEvents(const sf::Event &event);
};
#pragma once

#include "AState.h"

class							GUIState : public AState
{
public:
	GUIState(Game *game);
	~GUIState();

	bool						initialize(ResourceManager &resourceManager);
	bool						handleEvents(const sf::Event &event);
};
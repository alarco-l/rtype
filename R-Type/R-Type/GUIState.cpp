#include "GUIState.h"

GUIState::GUIState(Game *game) : AState(game)
{
	_isBlocking = true;
}

GUIState::~GUIState()
{
}

bool						GUIState::initialize(ResourceManager &resourceManager)
{
	return (true);
}

bool						GUIState::handleEvents(const sf::Event &event)
{
	return (true);
}
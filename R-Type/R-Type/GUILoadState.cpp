#include "GUILoadState.h"
#include "GameState.h"

GUILoadState::GUILoadState(Game *game) : AState(game)
{
	_isBlocking = true;
}

GUILoadState::~GUILoadState()
{
}

void						GUILoadState::initialize()
{
	_game->factory.createLoadMenu(_id, _world, _game->getScreenSize());
}

bool						GUILoadState::handleKeyState()
{
	return (true);
}

bool						GUILoadState::handleKeyEvent(const sf::Event &event)
{
	return (true);
}
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
	std::vector<const sf::Texture * const> textures;

	// TODO : verifs
	resourceManager.loadTexture("textures/bg.png");
	
	_world.createStaticEntity(resourceManager.getTexture("textures/bg.png"), sf::Vector2f());
	return (true);
}

bool						GUIState::handleEvents(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		_game->popState();
		return(false);
	}
	return (true);
}
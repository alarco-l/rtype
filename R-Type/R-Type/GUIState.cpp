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
	std::vector<const sf::Texture * const>	textures;
	unsigned int							idTitle;
	unsigned int							idConnect;
	unsigned int							idQuit;
	sf::Vector2u							screenSize = _game->getScreenSize();
	// TODO : verifs
	resourceManager.loadTexture("textures/bg.png");
	resourceManager.loadFont("textures/SPACEBAR.ttf");


	idTitle = _world.createEmptyEntity();
	idConnect = _world.createEmptyEntity();
	idQuit = _world.createEmptyEntity();


	_world.addTextComponent(idTitle, ComponentFactory::createTextComponent("R-TYPE", resourceManager.getFont("textures/SPACEBAR.ttf"), 120, sf::Color(13, 205, 248, 255)));
	_world.addTextComponent(idConnect, ComponentFactory::createTextComponent("Connect", resourceManager.getFont("textures/SPACEBAR.ttf"), 80));
	_world.addTextComponent(idQuit, ComponentFactory::createTextComponent("Quit", resourceManager.getFont("textures/SPACEBAR.ttf"), 80));
	
	
	_world.addTransformComponent(idTitle, ComponentFactory::createTransformComponent(sf::Vector2f(screenSize.x/2 - 250, 0)));
	_world.addTransformComponent(idConnect, ComponentFactory::createTransformComponent(sf::Vector2f(sf::Vector2f(screenSize.x / 2 - 200, screenSize.y / 3))));
	_world.addTransformComponent(idQuit, ComponentFactory::createTransformComponent(sf::Vector2f(sf::Vector2f(screenSize.x / 2 - 100, screenSize.y/2))));
	
	
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
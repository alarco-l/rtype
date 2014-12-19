#include "GUIState.h"

GUIState::GUIState(Game *game) : AState(game)
{
	_isBlocking = true;
	_state = Button::CONNECT;
}

GUIState::~GUIState()
{
}

bool						GUIState::initialize(ResourceManager &resourceManager)
{
	std::vector<const sf::Texture * const>	textures;
	sf::Vector2u							screenSize = _game->getScreenSize();

	resourceManager.loadTexture("textures/bg.png");
	resourceManager.loadFont("textures/SPACEBAR.ttf");


	_id[0] = _world.createEmptyEntity();
	_id[GUIState::Button::CONNECT] = _world.createEmptyEntity();
	_id[GUIState::Button::EXIT] = _world.createEmptyEntity();


	_world.addTextComponent(_id[0], ComponentFactory::createTextComponent("R-TYPE", resourceManager.getFont("textures/SPACEBAR.ttf"), true, 120, sf::Color(13, 205, 248, 255)));
	_world.addTextComponent(_id[GUIState::Button::CONNECT], ComponentFactory::createTextComponent("Connect", resourceManager.getFont("textures/SPACEBAR.ttf"), true, 80));
	_world.addTextComponent(_id[GUIState::Button::EXIT], ComponentFactory::createTextComponent("Quit", resourceManager.getFont("textures/SPACEBAR.ttf"), true, 80));
	
	_world.addTransformComponent(_id[0], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 10.0f)));
	_world.addTransformComponent(_id[GUIState::Button::CONNECT], ComponentFactory::createTransformComponent(sf::Vector2f(sf::Vector2f(0.0f, screenSize.y / 3.0f))));
	_world.addTransformComponent(_id[GUIState::Button::EXIT], ComponentFactory::createTransformComponent(sf::Vector2f(sf::Vector2f(0.0f, screenSize.y / 2.0f))));
	
	_world.createStaticEntity(resourceManager.getTexture("textures/bg.png"), sf::Vector2f());
	return (true);
}

# include <iostream>

bool						GUIState::handleEvents(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		_game->popState();
		return(false);
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
		if ((--_state) <= 0)
			_state = Button::EXIT;
		return(true);
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
		if ((++_state) >= Button::MAX)
			_state = Button::CONNECT;
		return(true);
	}
	std::cout << _state << std::endl;
	return (true);
}
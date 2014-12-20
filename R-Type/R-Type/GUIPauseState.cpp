#include "GUIPauseState.h"
#include "GameState.h"

GUIPauseState::GUIPauseState(Game *game) : AState(game)
{
	_isBlocking = false;
	_state = Button::CONTINUE;
}

GUIPauseState::~GUIPauseState()
{
}

bool						GUIPauseState::initialize(ResourceManager &resourceManager)
{
	unsigned int			background;
	unsigned int			title;
	sf::Vector2u			screenSize = _game->getScreenSize();

	if (!resourceManager.loadTexture("textures/bg.png"))
		return (false);
	if (!resourceManager.loadFont("fonts/SPACEBAR.ttf"))
		return (false);

	background = _world.createEmptyEntity();
	_world.addRenderComponent(background, ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/bg.png")));
	_world.addTransformComponent(background, ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1.0f, 1.0f), 0.0f, sf::Vector2f(screenSize)));

	title = _world.createEmptyEntity();
	_world.addTextComponent(title, ComponentFactory::createTextComponent("R-TYPE", resourceManager.getFont("fonts/SPACEBAR.ttf"), true, false, 120, sf::Color(13, 205, 248, 255)));
	_world.addTransformComponent(title, ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 10.0f)));

	_id[CONTINUE] = _world.createEmptyEntity();
	_world.addTextComponent(_id[CONTINUE], ComponentFactory::createTextComponent("Continue", resourceManager.getFont("fonts/SPACEBAR.ttf"), true, true, 80, sf::Color(255, 255, 255, 150)));
	_world.addTransformComponent(_id[CONTINUE], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, screenSize.y / 3.0f)));

	_id[EXIT] = _world.createEmptyEntity();
	_world.addTextComponent(_id[EXIT], ComponentFactory::createTextComponent("Quit", resourceManager.getFont("fonts/SPACEBAR.ttf"), true, false, 80, sf::Color(255, 255, 255, 150)));
	_world.addTransformComponent(_id[EXIT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, screenSize.y / 3.0f + 150.0f)));

	return (true);
}

#include <iostream>

bool						GUIPauseState::handleEvents(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		unsigned int			prev = _state;

		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			if ((_state--) == 0)
				_state = Button::EXIT;
			_world.textComponents[_id[_state]]->highlighted = true;
			_world.textComponents[_id[prev]]->highlighted = false;
			return(true);

		case sf::Keyboard::Down:
			if ((++_state) == Button::MAX)
				_state = Button::CONTINUE;
			_world.textComponents[_id[_state]]->highlighted = true;
			_world.textComponents[_id[prev]]->highlighted = false;
			return(true);

		case sf::Keyboard::Return:
			if (_state == Button::CONTINUE)
			{
				_game->popState();
				return (false);
			}
			else
			{
				_game->popState();
				std::cout << "POPSTATE2" << std::endl;
				_game->popState();
				return (false);
			}

		default:
			return (true);
		}
	}

	return (true);
}
#include "GUIEndState.h"
#include "GameState.h"

GUIEndState::GUIEndState(Game *game) : AState(game)
{
	_isBlocking = false;
	_state = Button::EXIT;
}

GUIEndState::~GUIEndState()
{
}

void						GUIEndState::initialize(ResourceManager &resourceManager)
{
	sf::Vector2u			screenSize = _game->getScreenSize();

	_id[TITLE] = _world.createEmptyEntity();
	_world.addTextComponent(_id[TITLE], ComponentFactory::createTextComponent("R-TYPE", resourceManager.getFont("fonts/SPACEBAR.ttf"), true, false, 120, sf::Color(13, 205, 248, 255)));
	_world.addTransformComponent(_id[TITLE], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 10.0f)));


	_id[TEXT] = _world.createEmptyEntity();
	_world.addTextComponent(_id[TEXT], ComponentFactory::createTextComponent("You Win", resourceManager.getFont("fonts/BMSPA.ttf"), true, false, 120, sf::Color(13, 205, 248, 255)));
	_world.addTransformComponent(_id[TEXT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 10.0f)));


	_id[TEXT2] = _world.createEmptyEntity();
	_world.addTextComponent(_id[TEXT2], ComponentFactory::createTextComponent("You Loose", resourceManager.getFont("fonts/BMSPA.ttf"), true, false, 120, sf::Color(13, 205, 248, 255)));
	_world.addTransformComponent(_id[TEXT2], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 10.0f)));

	_id[SCORE] = _world.createEmptyEntity();
	_world.addTextComponent(_id[SCORE], ComponentFactory::createTextComponent("Score :", resourceManager.getFont("fonts/BMSPA.ttf"), true, false, 120, sf::Color(13, 205, 248, 255)));
	_world.addTransformComponent(_id[SCORE], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 10.0f)));

	_id[EXIT] = _world.createEmptyEntity();
	_world.addTextComponent(_id[EXIT], ComponentFactory::createTextComponent("Return", resourceManager.getFont("fonts/BMSPA.ttf"), true, false, 80, sf::Color(255, 255, 255, 150)));
	_world.addTransformComponent(_id[EXIT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, screenSize.y / 3.0f + 150.0f)));
}

bool						GUIEndState::handleEvents(const sf::Event &event)
{
	_state = Button::EXIT;
	_world.textComponents[_id[_state]]->highlighted = true;
	if (event.type == sf::Event::KeyPressed)
	{
		unsigned int		prev = _state;

		switch (event.key.code)
		{
		case sf::Keyboard::Return:
			if (_state == Button::EXIT)
			{
				_game->popState();
				_game->popState();
				return (false);
			}
		default:
			return (true);
		}
	}

	return (true);
}
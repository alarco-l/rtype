#include "GUIEndState.h"
#include "GameState.h"

GUIEndState::GUIEndState(Game *game, const Result &result) : AState(game)
{
	(result == WIN) ? _result = "You Win" : _result = "You Lose";
	_isBlocking = false;
	_state = Element::EXIT;
}

GUIEndState::~GUIEndState()
{
}

void						GUIEndState::initialize(ResourceManager &resourceManager)
{
	sf::Vector2u			screenSize = _game->getScreenSize();

	_id[FILTER] = _world.createEmptyEntity();
	_world.addRenderComponent(_id[FILTER], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/unicolor.png"), sf::Color(0, 0, 0, 150)));
	_world.addTransformComponent(_id[FILTER], ComponentFactory::createTransformComponent(sf::Vector2f(screenSize), sf::Vector2f(0.0f, 0.0f)));

	_id[TEXT] = _world.createEmptyEntity();
	_world.addTextComponent(_id[TEXT], ComponentFactory::createTextComponent(_result, resourceManager.getFont("fonts/BMSPA.ttf"), true, false, 80, sf::Color::White));
	_world.addTransformComponent(_id[TEXT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 100.0f)));

	_id[SCORE] = _world.createEmptyEntity();
	_world.addTextComponent(_id[SCORE], ComponentFactory::createTextComponent("Score :", resourceManager.getFont("fonts/BMSPA.ttf"), true, false, 38, sf::Color::White));
	_world.addTransformComponent(_id[SCORE], ComponentFactory::createTransformComponent(sf::Vector2f(), sf::Vector2f(0.0f, screenSize.y - screenSize.y / 2.0f)));

	_id[EXIT] = _world.createEmptyEntity();
	_world.addTextComponent(_id[EXIT], ComponentFactory::createTextComponent("Press Enter To Quit", resourceManager.getFont("fonts/BMSPA.ttf"), true, true, 18, sf::Color::White));
	_world.addTransformComponent(_id[EXIT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, screenSize.y - screenSize.y / 3.0f)));
}

bool						GUIEndState::handleEvents(const sf::Event &event)
{
	_state = Element::EXIT;
	_world.textComponents[_id[_state]]->highlighted = true;
	if (event.type == sf::Event::KeyPressed)
	{
		unsigned int		prev = _state;

		switch (event.key.code)
		{
		case sf::Keyboard::Return:
			if (_state == Element::EXIT)
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
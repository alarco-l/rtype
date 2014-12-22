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

void						GUIPauseState::initialize(ResourceManager &resourceManager)
{
	unsigned int			filter;
	sf::Vector2u			screenSize = _game->getScreenSize();

	filter = _world.createEmptyEntity();
	_world.addRenderComponent(filter, ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/unicolor.png"), sf::Color(0, 0, 0, 150)));
	_world.addTransformComponent(filter, ComponentFactory::createTransformComponent(sf::Vector2f(screenSize), sf::Vector2f(0.0f, 0.0f)));

	_id[CONTINUE] = _world.createEmptyEntity();
	_world.addTextComponent(_id[CONTINUE], ComponentFactory::createTextComponent("Continue", resourceManager.getFont("fonts/SPACEBAR.ttf"), true, true, 80, sf::Color(255, 255, 255, 150)));
	_world.addTransformComponent(_id[CONTINUE], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, screenSize.y / 3.0f)));

	_id[EXIT] = _world.createEmptyEntity();
	_world.addTextComponent(_id[EXIT], ComponentFactory::createTextComponent("Quit", resourceManager.getFont("fonts/SPACEBAR.ttf"), true, false, 80, sf::Color(255, 255, 255, 150)));
	_world.addTransformComponent(_id[EXIT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, screenSize.y / 3.0f + 150.0f)));
}

bool						GUIPauseState::handleEvents(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		unsigned int		prev = _state;

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

		case sf::Keyboard::Escape:
			_game->popState();
			return (false);

		case sf::Keyboard::Return:
			if (_state == Button::CONTINUE)
			{
				_game->popState();
				return (false);
			}
			else
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
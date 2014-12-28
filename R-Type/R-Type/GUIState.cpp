#include "GUIState.h"
#include "GameState.h"
#include "GUIEndState.h"

GUIState::GUIState(Game *game) : AState(game)
{
	_isBlocking = true;
	_state = RType::MainMenu::CONNECT;
}

GUIState::~GUIState()
{
}

void						GUIState::initialize()
{
	_game->factory.createMainMenu(_id, _world, _game->getScreenSize());
}

void						GUIState::stop(void) {}

bool						GUIState::handleKeyState()
{
	return (true);
}

bool						GUIState::handleKeyEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		unsigned int			prev = _state;

		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			if ((_state--) == 0)
				_state = RType::MainMenu::EXIT;
			_world.textComponents[_id[_state]]->highlighted = true;
			_world.textComponents[_id[prev]]->highlighted = false;
			return(true);

		case sf::Keyboard::Down:
			if ((++_state) == RType::MainMenu::MAX)
				_state = RType::MainMenu::CONNECT;
			_world.textComponents[_id[_state]]->highlighted = true;
			_world.textComponents[_id[prev]]->highlighted = false;
			return(true);

		case sf::Keyboard::Return:
			if (_state == RType::MainMenu::CONNECT)
			{
				_game->pushState(new GameState(_game));
				return (true);
			}
			else
			{
				_game->popState();
				return (false);
			}

		default:
			return (true);
		}
	}

	return (true);
}
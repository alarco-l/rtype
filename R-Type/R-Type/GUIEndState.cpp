#include "GUIEndState.h"
#include "GameState.h"

GUIEndState::GUIEndState(Game *game, const Result &result) : AState(game)
{
	(result == WIN) ? _result = "You Win" : _result = "You Lose";
	_isBlocking = false;
	_state = RType::EndMenu::EXIT;
}

GUIEndState::~GUIEndState()
{
}

void						GUIEndState::initialize()
{
	_game->factory.createEndMenu(_id, _world, _game->getScreenSize(), _result);
}

void						GUIEndState::stop(void) {}

bool						GUIEndState::handleKeyState()
{
	return (true);
}

bool						GUIEndState::handleKeyEvent(const sf::Event &event)
{
	_state = RType::EndMenu::EXIT;
	_world.textComponents[_id[_state]]->highlighted = true;

	if (event.type == sf::Event::KeyPressed)
	{
		unsigned int		prev = _state;

		switch (event.key.code)
		{
		case sf::Keyboard::Return:
			if (_state == RType::EndMenu::EXIT)
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
#include "Game.h"
#include "GameState.h"

Game::Game() : _window(NULL)
{
}

Game::~Game()
{
}

bool										Game::initialize(const sf::Vector2u &size, const std::string &title)
{
	AState									*gameState;

	_window = new sf::RenderWindow(sf::VideoMode(size.x, size.y), title);

	if (!_window->isOpen())
		return (false);

	gameState = new GameState(this);
	if (!gameState->initialize(_resourceManager))
		return (false);
	this->pushState(gameState);
	return (true);
}

void										Game::run()
{
	sf::Event								event;
	sf::Time								elapsed;
	std::vector<AState *>::reverse_iterator	rit;
	AState									*state;

	while (_window->isOpen())
	{
		if (_states.empty())
			break;

		while (_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				return;
		}

		elapsed = _clock.restart();
		_window->clear();

		state = _states.back();
		if (!state->handleEvents(event))
			continue;
		for (rit = _states.rbegin(); rit != _states.rend(); ++rit)
		{
			state = *rit;
			state->update(elapsed);
			state->draw(_window);
			if (state->isBlocking())
				break;
		}

		_window->display();
	}
}

void										Game::exit()
{
	if (_window != NULL)
	{
		_window->close();
		delete (_window);
	}
}

void										Game::pushState(AState *state)
{
	_states.push_back(state);
}

void										Game::popState()
{
	delete (_states.back());
	_states.pop_back();
}
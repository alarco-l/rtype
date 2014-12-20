#include <stack>

#include "Game.h"
#include "GameState.h"
#include "GUIState.h"
#include "GUIPauseState.h"

Game::Game() : _window(NULL)
{
}

Game::~Game()
{
}

bool										Game::initialize(const sf::Vector2u &size, const std::string &title)
{
	_window = new sf::RenderWindow(sf::VideoMode(size.x, size.y), title, sf::Style::Fullscreen);

	if (!_window->isOpen())
		return (false);

	this->pushState(new GUIState(this));
	return (true);
}

void										Game::run()
{
	sf::Event								event;
	sf::Time								elapsed;
	std::vector<AState *>::reverse_iterator	rit;
	AState									*state;
	std::stack<AState *>					drawStack;

	while (_window->isOpen())
	{
		if (_states.empty())
			return;

		state = _states.back();
		while (_window->pollEvent(event))
		{
			if (!state->handleEvents(event))
				break;
		}

		elapsed = _clock.restart();
		_window->clear();

		for (rit = _states.rbegin(); rit != _states.rend(); ++rit)
		{
			state = *rit;
			state->update(elapsed);
			drawStack.push(state);
			if (state->isBlocking())
				break;
		}

		while (!drawStack.empty())
		{
			drawStack.top()->draw(_window);
			drawStack.pop();
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
	if (state->initialize(_resourceManager))
		_states.push_back(state);
	else
		delete (state);
}

void										Game::popState()
{
	_states.pop_back();
}

sf::Vector2u								Game::getScreenSize() const
{
	return (_window->getSize());
}

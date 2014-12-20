#include "Game.h"
#include "GameState.h"
#include "GUIState.h"

Game::Game() : _window(NULL)
{
}

Game::~Game()
{
}

bool										Game::initialize(const sf::Vector2u &size, const std::string &title)
{
	_window = new sf::RenderWindow(sf::VideoMode(size.x, size.y), title, sf::Style::None);

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

		// reverse order for draw
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
	if (state->initialize(_resourceManager))
		_states.push_back(state);
	else
		delete (state);
}

void										Game::popState()
{
	delete (_states.back());
	_states.pop_back();
}

sf::Vector2u				Game::getScreenSize() const
{
	return (_window->getSize());
}

/*GameState		*Game::createGameState() {
	GameState	*gameState = new GameState(this);
	if (!gameState->initialize(_resourceManager))
		return (NULL);
	return (gameState);
}*/
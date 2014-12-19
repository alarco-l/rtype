#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "ResourceManager.h"

class							AState;

class							Game
{
public:
	Game();
	~Game();

	bool						initialize(const sf::Vector2u &size, const std::string &title);
	void						run();
	void						exit();
	void						pushState(AState *state);
	void						popState();
private:
	Game(const Game &rhs);
	Game &operator=(const Game &rhs);

	ResourceManager				_resourceManager;
	sf::RenderWindow			*_window;
	sf::Clock					_clock;
	std::vector<AState *>		_states;
};
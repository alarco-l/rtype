#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "World.h"
#include "Systems.h"
#include "Game.h"

class							AState
{
public:
	AState(Game *game);
	~AState();

	virtual void				initialize(ResourceManager &resourceManager) = 0;
	virtual void				stop(void) = 0;
	virtual void				update(const sf::Time &elapsed);
	virtual void				draw(sf::RenderWindow *window);
	virtual bool				handleKeyEvent(const sf::Event &event) = 0;
	virtual bool				handleKeyState() = 0;
	virtual bool				isBlocking() const;
protected:
	bool						_isBlocking;
	World						_world;
	Game						*_game;
	Network::Client				*_client;
};
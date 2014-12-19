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

	virtual bool				initialize(ResourceManager &resourceManager) = 0;
	virtual void				update(const sf::Time &elapsed);
	virtual void				draw(sf::RenderWindow *window);
	virtual bool				handleEvents(const sf::Event &event) = 0;
	virtual bool				isBlocking() const;
protected:
	bool						_isBlocking;
	Game						*_game;
	World						_world;
};
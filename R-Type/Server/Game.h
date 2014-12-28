#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>

#include "BasicTypes.h"

#include "World.h"
#include "Systems.h"
#include "ComponentFactory.h"
#include "ResourceManager.h"

#include "DlLoader.hpp"
#include "IMonster.h"
#include "hpl.h"
#include "clock.h"
#include "RFCManager.h"

class							Game
{
public:
	Game();
	~Game();

	void						init();
	void						run(::hpl::Clock &);
	void						update(::hpl::Clock &);
	void						spawnMonster(std::string const &);
	void						deleteMonster(int id);
	void						fire(int id);

	World						&getWorld();
private:
	std::vector<IMonster *>		_monster;
	std::vector<uint>			_idMonster;
	DlLoader					*_dlLoader;
	World						_world;
	ResourceManager				_ressource;
	sf::Clock					_time;
	sf::Clock					_fireTime;
	bool						_spawn1;
	bool						_spawn2;
	RFCManager					_rfcManager;
};
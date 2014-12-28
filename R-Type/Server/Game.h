#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>
#include <ctime>

#include "BasicTypes.h"

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

private:
	std::vector<IMonster *>		_monster;
	std::vector<uint>			_idMonster;
	std::vector<IMonster::Dir>	_monsterDir;
	DlLoader					*_dlLoader;
	::hpl::Clock				_frameRate;
	::hpl::Clock				_fireTime;
	bool						_spawn1;
	bool						_spawn2;
	RFCManager					_rfcManager;
};
#pragma once

#include "AState.h"

class							GameState : public AState
{
public:
	GameState(Game *game);
	~GameState();

	void						initialize(ResourceManager &resourceManager);
	bool						handleEvents(const sf::Event &event);
	void						update(const sf::Time &elapsed);
	void						updateHUD();
private:
	enum HUD
	{
		LIFETEXT,
		SHIELDTEXT,
		LIFEBAR,
		SHIELDBAR,
		BOSSLIFEBAR,
		SCORE,
		WEAPON1,
		WEAPON2,
		WEAPON3,
		MAX
	};

	void						initializeHUD(ResourceManager &resourceManager);

	void						updateLife();
	void						updateLifeBoss();
	void						updateShield();
	void						updateAmo();
	void						updateScore();

	int							_idBoss;
	int							_idPlayer;
	unsigned int				_id[MAX];
};
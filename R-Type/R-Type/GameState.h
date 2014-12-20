#pragma once

#include "AState.h"

class							GameState : public AState
{
public:
	GameState(Game *game);
	~GameState();

	bool						initialize(ResourceManager &resourceManager);
	bool						handleEvents(const sf::Event &event);
	void						update(const sf::Time &elapsed);
	void						updateHUD();
private:
	void						updateLife();
	void						updateLifeBoss();
	void						updateShield();
	void						updateAmo();
	void						updateScore();

	enum HUD
	{
		LIFE,
		SHIELD,
		LIFEBAR,
		SHIELDBAR,
		LIFEBOSSBAR,
		SCORE,
		AMO1,
		AMO2,
		AMO3,
		MAX
	};
	int							_idBoss;
	int							_idPlayer;
	unsigned int				_id[MAX];
};
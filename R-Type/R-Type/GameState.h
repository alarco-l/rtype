#pragma once

#include "AState.h"

#include "Network/Client.h"

class							GameState : public AState
{
public:
	GameState(Game *game);
	~GameState();

	void						initialize();
	void						stop(void);
	bool						handleKeyEvent(const sf::Event &event);
	bool						handleKeyState();
	void						update(const sf::Time &elapsed);
	
private:

	void						onConnectEvent(Network::Client &client);
	void						onRecive(Network::Socket &socket);
	void						onEnd(Network::Socket const &socket);

	void						updateBackground();
	void						updateHUD();

	int							_idBoss;
	unsigned int				_idPlayer[RType::Player::MAX];
	unsigned int				_idHud[RType::HUD::MAX];
	unsigned int				_idBackground[RType::GameBackground::MAX];
};
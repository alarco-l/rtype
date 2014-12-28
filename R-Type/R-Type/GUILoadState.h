#pragma once

#include "AState.h"

class							GUILoadState : public AState
{
public:
	GUILoadState(Game *game);
	~GUILoadState();

	void						initialize();
	bool						handleKeyEvent(const sf::Event &event);
	bool						handleKeyState();

private:

	unsigned int				_id[RType::LobbyMenu::MAX];
};
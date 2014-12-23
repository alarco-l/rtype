#pragma once

#include "AState.h"

class							GUIState : public AState
{
public:
	GUIState(Game *game);
	~GUIState();

	void						initialize(ResourceManager &resourceManager);
	bool						handleKeyEvent(const sf::Event &event);
	bool						handleKeyState();

private:
	enum Element
	{
		CONNECT,
		EXIT,
		MAX
	};

	unsigned int				_state;
	unsigned int				_id[2];
};
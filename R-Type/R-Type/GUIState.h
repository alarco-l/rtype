#pragma once

#include "AState.h"

class							GUIState : public AState
{
public:
	GUIState(Game *game);
	~GUIState();

	bool						initialize(ResourceManager &resourceManager);
	bool						handleEvents(const sf::Event &event);
private:
	enum Button
	{
		BEGIN,
		CONNECT,
		EXIT,
		MAX
	};
	unsigned int				_state;
	unsigned int				_id[3];
};
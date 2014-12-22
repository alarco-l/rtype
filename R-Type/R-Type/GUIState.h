#pragma once

#include "AState.h"

class							GUIState : public AState
{
public:
	GUIState(Game *game);
	~GUIState();

	void						initialize(ResourceManager &resourceManager);
	bool						handleEvents(const sf::Event &event);
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
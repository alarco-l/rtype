#pragma once

#include "AState.h"

class							GUIPauseState : public AState
{
public:
	GUIPauseState(Game *game);
	~GUIPauseState();

	bool						initialize(ResourceManager &resourceManager);
	bool						handleEvents(const sf::Event &event);
private:
	enum Button
	{
		CONTINUE,
		EXIT,
		MAX
	};
	unsigned int				_state;
	unsigned int				_id[2];
};
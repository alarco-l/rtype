#pragma once

#include "AState.h"

class							GUIPauseState : public AState
{
public:
	GUIPauseState(Game *game);
	~GUIPauseState();

	void						initialize(ResourceManager &resourceManager);
	bool						handleEvents(const sf::Event &event);
private:
	enum Element
	{
		CONTINUE,
		EXIT,
		MAX
	};

	unsigned int				_state;
	unsigned int				_id[2];
};
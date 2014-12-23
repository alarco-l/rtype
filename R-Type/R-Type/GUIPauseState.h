#pragma once

#include "AState.h"

class							GUIPauseState : public AState
{
public:
	GUIPauseState(Game *game);
	~GUIPauseState();

	void						initialize(ResourceManager &resourceManager);
	bool						handleKeyEvent(const sf::Event &event);
	bool						handleKeyState();

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
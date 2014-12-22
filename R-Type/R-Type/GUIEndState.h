#pragma once

#include "AState.h"

class							GUIEndState : public AState
{
public:
	GUIEndState(Game *game);
	~GUIEndState();

	void						initialize(ResourceManager &resourceManager);
	bool						handleEvents(const sf::Event &event);
private:
	enum Button
	{
		TITLE,
		TEXT,
		TEXT2,
		SCORE,
		EXIT,
		MAX
	};

	unsigned int				_state;
	unsigned int				_id[MAX];
};
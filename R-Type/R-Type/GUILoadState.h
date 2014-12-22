#pragma once

#include "AState.h"

class							GUILoadState : public AState
{
public:
	GUILoadState(Game *game);
	~GUILoadState();

	void						initialize(ResourceManager &resourceManager);
	bool						handleEvents(const sf::Event &event);
private:
	enum Button
	{
		BACKGROUND,
		TITLE,
		TEXT,
		IMG,
		MAX
	};

	unsigned int				_state;
	unsigned int				_id[MAX];
};
#pragma once

#include "AState.h"

class							GUILoad : public AState
{
public:
	GUILoad(Game *game);
	~GUILoad();

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
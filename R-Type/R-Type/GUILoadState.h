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
	enum Element
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
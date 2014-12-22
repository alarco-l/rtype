#pragma once

#include "AState.h"

class							GUIEndState : public AState
{
public:

	enum Result
	{
		WIN,
		LOSE
	};

	GUIEndState(Game *game, const Result &result);
	~GUIEndState();

	void						initialize(ResourceManager &resourceManager);
	bool						handleEvents(const sf::Event &event);

private:
	enum Element
	{
		TEXT,
		FILTER,
		SCORE,
		EXIT,
		MAX
	};
	std::string					_result;
	unsigned int				_state;
	unsigned int				_id[MAX];
};
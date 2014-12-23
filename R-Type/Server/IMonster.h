#pragma once

#include "BasicTypes.h"

class						IMonster
{
public:
	virtual					~IMonster() {}

	virtual	void			update() = 0;

	virtual sint			getType() = 0;
private:
	sint					type;
};
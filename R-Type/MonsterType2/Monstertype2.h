#pragma once

#include "IMonster.h"

class							MonsterType1 : public IMonster
{
public:
	MonsterType1();
	~MonsterType1();

	Dir							update();

	const char					*getTexture() const;

	void						setSpawn(float x, float y);
};

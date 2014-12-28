#pragma once

#include "IMonster.h"

class							MonsterType1 : public IMonster
{
public:
	MonsterType1();
	~MonsterType1();

	Dir							update();
	Dir							fire();

	const char					*getTexture() const;
	const char					*getFire() const;

	void						setSpawn(float x, float y);
private:
	IMonster::Dir				_dir;
};

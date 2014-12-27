#include "MonsterType2.h"

MonsterType1::MonsterType1()
{
	_texture = "../R-Type/textures/intercepter.png";
	_time = 0.f;
}

MonsterType1::~MonsterType1() {}

IMonster::Dir			MonsterType1::update()
{
	IMonster::Dir		dir;
	int					R = 85;
	int					d = 85;

	_time += 0.003f;
	dir.x = 1200 - (1200 - _spawn.x) - ((R * _time) - (d * sin((_time))));
	dir.y = ((R - d * cos(_time))) + _spawn.y;
	return (dir);
}

const char				*MonsterType1::getTexture() const { return (_texture.c_str()); }

void					MonsterType1::setSpawn(float x, float y)
{
	_spawn.x = x;
	_spawn.y = y;
}

EXPORT IMonster			*newInstance()
{
	return (new MonsterType1());
}
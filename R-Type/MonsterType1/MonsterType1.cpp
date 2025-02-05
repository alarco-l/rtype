#include "MonsterType1.h"

MonsterType1::MonsterType1()
{
	_texture = "../R-Type/textures/hero.png";
	_fire = "../R-Type/textures/greenLaserRay.png";
	_time = 0.f;
	_life = 50;
}

MonsterType1::~MonsterType1() {}

IMonster::Dir			MonsterType1::update()
{
	IMonster::Dir		dir;
	int					R = 75;
	int					d = 75;

	_time += 0.02f * 0.02f * 80;
	dir.x = 1200 - (1200 - _spawn.x) - ((R * _time) - (d * sin((_time))));
	dir.y = ((R - d * cos(_time))) + _spawn.y;
	_dir = dir;
	return (dir);
}

IMonster::Dir			MonsterType1::fire()
{
	return (_dir);
}

const char				*MonsterType1::getTexture() const { return (_texture.c_str()); }

const char				*MonsterType1::getFire() const { return (_fire.c_str()); }

int						MonsterType1::getLife() const { return (_life); }

void					MonsterType1::setSpawn(float x, float y)
{
	_spawn.x = x;
	_spawn.y = y;
}

void					MonsterType1::setLife(int life) { _life = life; }

EXPORT IMonster			*newInstance()
{
	return (new MonsterType1());
}
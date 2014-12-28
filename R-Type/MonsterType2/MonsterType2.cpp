#include "MonsterType2.h"

MonsterType2::MonsterType2()
{
	_texture = "../R-Type/textures/intercepter.png";
	_fire = "../R-Type/textures/greenLaserRay.png";
	_time = 0.f;
}

MonsterType2::~MonsterType2() {}

IMonster::Dir			MonsterType2::update()
{
	IMonster::Dir		dir;
	int					R = 30;
	int					d = 85;

	_time += 0.03f * 0.02f * 80;
	dir.x = 1200 - (1200 - _spawn.x) - ((R * _time) - (d * sin((_time))));
	dir.y = ((R - d * cos(_time))) + _spawn.y;
	_dir = dir;
	return (dir);
}

IMonster::Dir			MonsterType2::fire()
{
	return (_dir);
}

const char				*MonsterType2::getTexture() const { return (_texture.c_str()); }

const char				*MonsterType2::getFire() const { return (_fire.c_str()); }

int						MonsterType2::getLife() const { return (_life); }

void					MonsterType2::setSpawn(float x, float y)
{
	_spawn.x = x;
	_spawn.y = y;
}

void					MonsterType2::setLife(int life) { _life = life; }

EXPORT IMonster			*newInstance()
{
	return (new MonsterType2());
}
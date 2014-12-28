#pragma once

#include <string>

#define							EXPORT extern "C" 
#define							DLL __declspec(dllexport) 

class							IMonster
{
public:
	struct						Dir
	{
		float					x;
		float					y;
	};

	virtual						~IMonster() {}

	virtual Dir					update() = 0;
	virtual Dir					fire() = 0;

	virtual const char			*getTexture() const = 0;
	virtual const char			*getFire() const = 0;
	virtual int					getLife() const = 0;

	virtual void				setSpawn(float x, float y) = 0;
	virtual void				setLife(int life) = 0;
protected:
	std::string					_texture;
	std::string					_fire;
	float						_time;
	Dir							_spawn;
	int							_life;
};

EXPORT DLL IMonster				*newInstance();
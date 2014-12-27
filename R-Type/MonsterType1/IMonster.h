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

	virtual const char			*getTexture() const = 0;
	virtual void				setSpawn(float x, float y) = 0;
protected:
	std::string					_texture;
	float						_time;
	Dir							_spawn;
};

EXPORT DLL IMonster				*newInstance();
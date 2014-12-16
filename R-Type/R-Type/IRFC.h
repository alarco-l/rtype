#pragma once

#include "BasicType.h"

class					IRFC
{
public:

	struct					Coord
	{
		sint				posX;
		sint				posY;
	};

	struct					Dir
	{
		sint				dirX;
		sint				dirY;
	};

	virtual				~IRFC() {}

	virtual void		setSocket(Socket &socket) = 0;
	virtual void		getData(Socket &socket) = 0;
};
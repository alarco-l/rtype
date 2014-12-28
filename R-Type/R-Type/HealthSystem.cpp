#include "HealthSystem.h"

void										HealthSystem::update(World &world, const sf::Time &elapsed, GameSpecificFactory &factory)
{
	for (unsigned int i = 0; i < world.entityCount; ++i)
	{
		InfoComponent						*info = world.infoComponents[i];

		if (info)
		{
			if (info->damageReceived > info->shield)
			{
				info->damageReceived -= info->shield;
				info->shield = 0;
				info->life -= info->damageReceived;
			}
			else
				info->shield -= info->damageReceived;

			info->damageReceived = 0;

			if (info->life <= 0)
				info->dead = true;

		}
	}
}
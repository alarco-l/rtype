#include "WeaponSystem.h"

void								WeaponSystem::update(World &world, const sf::Time &elapsed, GameSpecificFactory &factory, const sf::Vector2u &screenSize)
{
	for (unsigned int i = 0; i < world.entityCount; ++i)
	{
		WeaponComponent				*weapon = world.weaponComponents[i];
		ProjectileComponent			*proj = world.projectileComponents[i];

		if (weapon)
		{
			weapon->cooldown -= elapsed;
			if (weapon->cooldown < sf::Time::Zero)
				weapon->cooldown = sf::Time::Zero;

			if (weapon->fire && weapon->cooldown == sf::Time::Zero && world.infoComponents.size() > world.weaponComponents[i]->owner && weapon->projectileType < 2)
			{
				unsigned int		id[1]; // pas toujours 1 :(

				//if (weapon->projectileType < 2)
				//{
				(factory.*(factory.createProjectile[weapon->projectileType]))(id, i, world, screenSize);
					world.transformComponents[id[0]]->position = world.transformComponents[i]->position;
					world.projectileComponents[id[0]]->owner = world.weaponComponents[i]->owner;
					weapon->cooldown = weapon->maxCooldown;
				//}
			}

			weapon->fire = false;
		}
	}
}
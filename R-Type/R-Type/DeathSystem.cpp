#include "DeathSystem.h"

void									DeathSystem::update(World &world)
{
	for (unsigned int i = 0; i < world.entityCount; ++i)
	{
		InfoComponent					*info = world.infoComponents[i];

		if (info && info->dead)
		{
			AnimationComponent			*anim = world.animationComponents[i];

			if (anim)
			{
				if (anim->restart)
				{
					anim->animations = info->deathAnimation;
					anim->restart = false;
					anim->currentAnimation = anim->animations.begin();
					anim->maxLifetime = info->maxLifetime;
					anim->lifetime = sf::Time::Zero;
					world.removeCollisionComponent(i);
					world.removeMovementComponent(i);
				}
				else if (anim->currentAnimation == anim->animations.end())
					world.destroyEntity(i);
			}
			else
				world.destroyEntity(i);
		}
	}
}
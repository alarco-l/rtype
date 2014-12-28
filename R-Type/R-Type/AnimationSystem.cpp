#include "AnimationSystem.h"

void						AnimationSystem::update(World &world, const sf::Time &elapsed)
{
	for (unsigned int i = 0; i < world.entityCount; ++i)
	{
		AnimationComponent	*anim = world.animationComponents[i];
		RenderComponent		*render = world.renderComponents[i];

		if (anim && render && anim->animations.size() != 0)
		{
			anim->lifetime -= elapsed;
			if (anim->lifetime <= sf::Time::Zero)
			{
				anim->lifetime = anim->maxLifetime;

				++anim->currentAnimation;

				if (anim->restart && anim->currentAnimation == anim->animations.end())
					anim->currentAnimation = anim->animations.begin();

				if (anim->currentAnimation != anim->animations.end())
					render->texture = *anim->currentAnimation;
			}
		}
	}
}
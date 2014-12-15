#include "AnimationSystem.h"

AnimationSystem::AnimationSystem()
{
}

AnimationSystem::~AnimationSystem()
{
}

void						AnimationSystem::update(World &world, const sf::Time &elapsed) const
{
	for (unsigned int i = 0; i != world.entityCount; ++i)
	{
		AnimationComponent	*anim = world.animationComponents[i];
		RenderComponent		*render = world.renderComponents[i];

		if (anim && render)
		{
			anim->lifetime -= elapsed;
			if (anim->lifetime <= sf::Time::Zero)
			{
				anim->lifetime = anim->maxLifetime;
				++anim->currentAnimation;
				if (anim->currentAnimation == anim->animations.end())
					anim->currentAnimation = anim->animations.begin();
				render->texture = *anim->currentAnimation;
			}
		}
	}
}
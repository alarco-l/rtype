#include "RenderSystem.h"

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

void							RenderSystem::update(World &world, const sf::Time &elapsed) const {}

void							RenderSystem::update(sf::RenderWindow &window, World &world) const
{
	for (unsigned int i = 0; i != world.entityCount; ++i)
	{
		RenderComponent			*render = world.renderComponents[i];
		TransformComponent		*xform = world.transformComponents[i];

		if (render && xform)
		{
			// peut-etre juste faire gaffe et pas de if
			sf::Vector2f	textureSize(render->texture->getSize());

			if (render->vertices[2].texCoords != textureSize)
			{
				render->vertices[0].texCoords = sf::Vector2f(0.0f, 0.0f);
				render->vertices[1].texCoords = sf::Vector2f(textureSize.x, 0.0f);
				render->vertices[2].texCoords = sf::Vector2f(textureSize.x, textureSize.y);
				render->vertices[3].texCoords = sf::Vector2f(0.0f, textureSize.y);

				render->vertices[0].position = render->vertices[0].texCoords;
				render->vertices[1].position = render->vertices[1].texCoords;
				render->vertices[2].position = render->vertices[2].texCoords;
				render->vertices[3].position = render->vertices[3].texCoords;
			}

			sf::RenderStates	states;

			states.texture = render->texture;
			states.transform = xform->transform;
			window.draw(render->vertices, states);
		}
	}
}
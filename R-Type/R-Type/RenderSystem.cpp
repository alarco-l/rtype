#include "RenderSystem.h"

void							RenderSystem::update(sf::RenderWindow *window, World &world)
{
	for (unsigned int i = 0; i != world.entityCount; ++i)
	{
		RenderComponent			*render = world.renderComponents[i];
		TransformComponent		*xform = world.transformComponents[i];

		if (render && xform)
		{
			sf::Vector2f		textureSize(render->texture->getSize());

			render->vertices[0].texCoords = sf::Vector2f(0.0f, 0.0f);
			render->vertices[1].texCoords = sf::Vector2f(textureSize.x, 0.0f);
			render->vertices[2].texCoords = sf::Vector2f(textureSize.x, textureSize.y);
			render->vertices[3].texCoords = sf::Vector2f(0.0f, textureSize.y);

			render->vertices[0].position = render->vertices[0].texCoords;
			render->vertices[1].position = sf::Vector2f(xform->size.x, 0.0f);
			render->vertices[2].position = sf::Vector2f(xform->size.x, xform->size.y);
			render->vertices[3].position = sf::Vector2f(0.0f, xform->size.y);

			render->vertices[0].color = render->color;
			render->vertices[1].color = render->color;
			render->vertices[2].color = render->color;
			render->vertices[3].color = render->color;

			sf::RenderStates	states;

			states.texture = render->texture;
			states.transform = xform->transform;
			window->draw(render->vertices, states);
		}
	}
}
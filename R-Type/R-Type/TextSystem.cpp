#include "TextSystem.h"

void							TextSystem::update(sf::RenderWindow *window, World &world)
{
	for (unsigned int i = 0; i != world.entityCount; ++i)
	{
		TextComponent			*txt = world.textComponents[i];
		TransformComponent		*xform = world.transformComponents[i];

		if (txt && xform)
		{
			sf::Text			text;

			text.setFont(*txt->font);
			text.setColor(txt->color);
			text.setString(txt->string);
			text.setCharacterSize(txt->size);

			sf::RenderStates	states;

			states.transform = xform->transform;
			window->draw(text, states);
		}
	}
}
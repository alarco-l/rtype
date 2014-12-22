#include "GUILoad.h"
#include "GameState.h"

GUILoad::GUILoad(Game *game) : AState(game)
{
	_isBlocking = true;
	_state = Button::MAX;
}

GUILoad::~GUILoad()
{
}

void						GUILoad::initialize(ResourceManager &resourceManager)
{
	sf::Vector2u			screenSize = _game->getScreenSize();

	_id[TITLE] = _world.createEmptyEntity();
	_world.addTextComponent(_id[TITLE], ComponentFactory::createTextComponent("R-TYPE", resourceManager.getFont("fonts/SPACEBAR.ttf"), true, false, 120, sf::Color(13, 205, 248, 255)));
	_world.addTransformComponent(_id[TITLE], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 10.0f)));

	_id[BACKGROUND] = _world.createEmptyEntity();
	_world.addRenderComponent(_id[BACKGROUND], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/menu_background.png")));
	_world.addTransformComponent(_id[BACKGROUND], ComponentFactory::createTransformComponent(sf::Vector2f(screenSize), sf::Vector2f(0.0f, 0.0f)));

	_id[TEXT] = _world.createEmptyEntity();
	_world.addTextComponent(_id[TEXT], ComponentFactory::createTextComponent("Waiting Gamers ...", resourceManager.getFont("fonts/BMSPA.ttf"), true, true, 72, sf::Color(255, 255, 255, 150)));
	_world.addTransformComponent(_id[TEXT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, screenSize.y / 3.0f)));

	_id[IMG] = _world.createEmptyEntity();
	_world.addRenderComponent(_id[IMG], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/load_icon.png")));
	_world.addTransformComponent(_id[IMG], ComponentFactory::createTransformComponent(sf::Vector2f(375, 375), sf::Vector2f(screenSize.x - screenSize.x / 2.0f, screenSize.y/2 + 70.0f)));
}

bool						GUILoad::handleEvents(const sf::Event &event)
{
	return (true);
}
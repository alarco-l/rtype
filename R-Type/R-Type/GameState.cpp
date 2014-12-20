#include "GameState.h"
#include "GUIPauseState.h"

GameState::GameState(Game *game) : AState(game)
{
	_isBlocking = true;
}

GameState::~GameState()
{
}

bool						GameState::initialize(ResourceManager &resourceManager)
{
	std::vector<const sf::Texture * const> textures;

	// TODO : verifs
	resourceManager.loadTexture("textures/hero.png");
	resourceManager.loadTexture("textures/fireball.png");
	resourceManager.loadTexture("textures/explosion0.png");
	resourceManager.loadTexture("textures/explosion1.png");
	resourceManager.loadTexture("textures/explosion2.png");
	resourceManager.loadTexture("textures/explosion3.png");
	resourceManager.loadTexture("textures/explosion4.png");
	resourceManager.loadTexture("textures/explosion5.png");

	textures.push_back(resourceManager.getTexture("textures/explosion0.png"));
	textures.push_back(resourceManager.getTexture("textures/explosion1.png"));
	textures.push_back(resourceManager.getTexture("textures/explosion2.png"));
	textures.push_back(resourceManager.getTexture("textures/explosion3.png"));
	textures.push_back(resourceManager.getTexture("textures/explosion4.png"));
	textures.push_back(resourceManager.getTexture("textures/explosion5.png"));

	_world.createMovingEntity(resourceManager.getTexture("textures/hero.png"), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.5f, 0.5f));
	_world.createParticleEffect(20, true, resourceManager.getTexture("textures/fireball.png"), sf::Vector2f(800.0f, 450.0f));
	_world.createAnimatedEntity(textures, sf::seconds(0.10f), sf::Vector2f(0.0f, 450.0f));
	return (true);
}

bool						GameState::handleEvents(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		_game->pushState(new GUIPauseState(_game));
		return (true);
	}

	return (true);
}
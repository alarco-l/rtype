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
	// TODO : verifs
	//resourceManager.loadTexture("textures/hero.png");
	//resourceManager.loadTexture("textures/fireball.png");
	//resourceManager.loadTexture("textures/explosion0.png");
	//resourceManager.loadTexture("textures/explosion1.png");
	//resourceManager.loadTexture("textures/explosion2.png");
	//resourceManager.loadTexture("textures/explosion3.png");
	//resourceManager.loadTexture("textures/explosion4.png");
	//resourceManager.loadTexture("textures/explosion5.png");

	//_world.createMovingEntity(resourceManager.getTexture("textures/hero.png"), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.5f, 0.5f));
	//_world.createParticleEffect(20, true, resourceManager.getTexture("textures/fireball.png"), sf::Vector2f(800.0f, 450.0f));
	//_world.createAnimatedEntity(textures, sf::seconds(0.10f), sf::Vector2f(0.0f, 450.0f));

	resourceManager.loadTexture("textures/bar.png");
	resourceManager.loadTexture("textures/loadLaser.png");
	resourceManager.loadTexture("textures/mine_ico.png");
	resourceManager.loadTexture("textures/missile_ico.png");

	sf::Vector2u			screenSize = _game->getScreenSize();

	if (!resourceManager.loadFont("fonts/BMSPA.ttf"))
		return (false);

	_id[SHIELD] = _world.createEmptyEntity();
	_world.addTextComponent(_id[SHIELD], ComponentFactory::createTextComponent("Shield", resourceManager.getFont("fonts/BMSPA.ttf"), false, false, 18, sf::Color(255, 255, 255, 255)));
	_world.addTransformComponent(_id[SHIELD], ComponentFactory::createTransformComponent(sf::Vector2f(25.0f, screenSize.y - 38.0f)));

	_id[SHIELDBAR] = _world.createEmptyEntity();
	_world.addRenderComponent(_id[SHIELDBAR], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/bar.png"), sf::Color(13, 205, 248)));
	_world.addTransformComponent(_id[SHIELDBAR], ComponentFactory::createTransformComponent(sf::Vector2f(120.0f, screenSize.y - 30.0f), sf::Vector2f(1, 1), 0, sf::Vector2f(200, 10)));

	_id[LIFE] = _world.createEmptyEntity();
	_world.addTextComponent(_id[LIFE], ComponentFactory::createTextComponent("Life", resourceManager.getFont("fonts/BMSPA.ttf"), false, false, 18, sf::Color(255, 255, 255, 255)));
	_world.addTransformComponent(_id[LIFE], ComponentFactory::createTransformComponent(sf::Vector2f(25.0f, screenSize.y - 58.0f)));

	_id[LIFEBAR] = _world.createEmptyEntity();
	_world.addRenderComponent(_id[LIFEBAR], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/bar.png"), sf::Color::Green));
	_world.addTransformComponent(_id[LIFEBAR], ComponentFactory::createTransformComponent(sf::Vector2f(120.0f, screenSize.y - 50.0f), sf::Vector2f(1, 1), 0, sf::Vector2f(200, 10)));

	_id[LIFEBOSSBAR] = _world.createEmptyEntity();
	_world.addRenderComponent(_id[LIFEBOSSBAR], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/bar.png"), sf::Color::Red));
	_world.addTransformComponent(_id[LIFEBOSSBAR], ComponentFactory::createTransformComponent(sf::Vector2f(screenSize.x / 2 - 250.0f, 50.0f), sf::Vector2f(1, 1), 0, sf::Vector2f(500, 10)));
	
	_id[AMO1] = _world.createEmptyEntity();
	_world.addRenderComponent(_id[AMO1], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/loadLaser.png")));
	_world.addTransformComponent(_id[AMO1], ComponentFactory::createTransformComponent(sf::Vector2f(screenSize.x - screenSize.x / 7.0f, screenSize.y - 70.0f), sf::Vector2f(1, 1), 0, sf::Vector2f(50, 50)));

	_id[AMO2] = _world.createEmptyEntity();
	_world.addRenderComponent(_id[AMO2], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/mine_ico.png")));
	_world.addTransformComponent(_id[AMO2], ComponentFactory::createTransformComponent(sf::Vector2f(screenSize.x - screenSize.x / 7.0f + 70, screenSize.y - 70.0f), sf::Vector2f(1, 1), 0, sf::Vector2f(50, 50)));

	_id[AMO3] = _world.createEmptyEntity();
	_world.addRenderComponent(_id[AMO3], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/missile_ico.png"), sf::Color::Green));
	_world.addTransformComponent(_id[AMO3], ComponentFactory::createTransformComponent(sf::Vector2f(screenSize.x - screenSize.x / 7.0f - 70, screenSize.y - 70.0f), sf::Vector2f(1, 1), 0, sf::Vector2f(50, 50)));

	_id[SCORE] = _world.createEmptyEntity();
	_world.addTextComponent(_id[SCORE], ComponentFactory::createTextComponent("Score : 1000000", resourceManager.getFont("fonts/BMSPA.ttf"), true, false, 18, sf::Color(255, 255, 255, 255)));
	_world.addTransformComponent(_id[SCORE], ComponentFactory::createTransformComponent(sf::Vector2f(0, 15.0f)));


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



void				GameState::update(const sf::Time &elapsed) {
	ParticleSystem::update(_world, elapsed);
	TransformSystem::update(_world, elapsed);
	AnimationSystem::update(_world, elapsed);
	updateHUD();
}

void				GameState::updateHUD() {
	updateLife();
	updateLifeBoss();
	updateShield();
	updateAmo();
}


void						GameState::updateLife() {
	//_world.renderComponents[_id[LIFEBAR]]
}

void						GameState::updateLifeBoss() {
	//_world.renderComponents[_id[LIFEBOSSBAR]]
}

void						GameState::updateShield() {
	//_world.renderComponents[_id[SHIELDBAR]]
}

void						GameState::updateScore() {
	//_world.renderComponents[_id[SCORE]]
}

void						GameState::updateAmo() {
	//_world.renderComponents[_id[AMO1]]
	//_world.renderComponents[_id[AMO2]]
	//_world.renderComponents[_id[AMO3]]
}
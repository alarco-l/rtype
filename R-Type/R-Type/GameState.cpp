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
	resourceManager.loadTexture("textures/bar.png");
	resourceManager.loadTexture("textures/loadLaser.png");
	resourceManager.loadTexture("textures/mine_ico.png");
	resourceManager.loadTexture("textures/missile_ico.png");

	sf::Vector2u			screenSize = _game->getScreenSize();

	if (!resourceManager.loadFont("fonts/BMSPA.ttf"))
		return (false);

	_id[SHIELDTEXT] = _world.createEmptyEntity();
	_world.addTextComponent(_id[SHIELDTEXT], ComponentFactory::createTextComponent("Shield", resourceManager.getFont("fonts/BMSPA.ttf"), false, false, 18, sf::Color(255, 255, 255, 255)));
	_world.addTransformComponent(_id[SHIELDTEXT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(25.0f, screenSize.y - 38.0f)));

	_id[SHIELDBAR] = _world.createEmptyEntity();
	_world.addRenderComponent(_id[SHIELDBAR], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/bar.png"), sf::Color(13, 205, 248)));
	_world.addTransformComponent(_id[SHIELDBAR], ComponentFactory::createTransformComponent(sf::Vector2f(200, 10), sf::Vector2f(120.0f, screenSize.y - 30.0f)));

	_id[LIFETEXT] = _world.createEmptyEntity();
	_world.addTextComponent(_id[LIFETEXT], ComponentFactory::createTextComponent("Life", resourceManager.getFont("fonts/BMSPA.ttf"), false, false, 18, sf::Color(255, 255, 255, 255)));
	_world.addTransformComponent(_id[LIFETEXT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(25.0f, screenSize.y - 58.0f)));

	_id[LIFEBAR] = _world.createEmptyEntity();
	_world.addRenderComponent(_id[LIFEBAR], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/bar.png"), sf::Color::Green));
	_world.addTransformComponent(_id[LIFEBAR], ComponentFactory::createTransformComponent(sf::Vector2f(200, 10), sf::Vector2f(120.0f, screenSize.y - 50.0f)));

	_id[BOSSLIFEBAR] = _world.createEmptyEntity();
	_world.addRenderComponent(_id[BOSSLIFEBAR], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/bar.png"), sf::Color::Red));
	_world.addTransformComponent(_id[BOSSLIFEBAR], ComponentFactory::createTransformComponent(sf::Vector2f(500, 10), sf::Vector2f(screenSize.x / 2 - 250.0f, 50.0f)));
	
	_id[WEAPON1] = _world.createEmptyEntity();
	_world.addRenderComponent(_id[WEAPON1], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/loadLaser.png")));
	_world.addTransformComponent(_id[WEAPON1], ComponentFactory::createTransformComponent(sf::Vector2f(50, 50), sf::Vector2f(screenSize.x - screenSize.x / 7.0f, screenSize.y - 70.0f)));

	_id[WEAPON2] = _world.createEmptyEntity();
	_world.addRenderComponent(_id[WEAPON2], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/mine_ico.png")));
	_world.addTransformComponent(_id[WEAPON2], ComponentFactory::createTransformComponent(sf::Vector2f(50, 50), sf::Vector2f(screenSize.x - screenSize.x / 7.0f + 70, screenSize.y - 70.0f)));

	_id[WEAPON3] = _world.createEmptyEntity();
	_world.addRenderComponent(_id[WEAPON3], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/missile_ico.png"), sf::Color::Green));
	_world.addTransformComponent(_id[WEAPON3], ComponentFactory::createTransformComponent(sf::Vector2f(50, 50), sf::Vector2f(screenSize.x - screenSize.x / 7.0f - 70, screenSize.y - 70.0f)));

	_id[SCORE] = _world.createEmptyEntity();
	_world.addTextComponent(_id[SCORE], ComponentFactory::createTextComponent("Score : 1000000", resourceManager.getFont("fonts/BMSPA.ttf"), true, false, 18, sf::Color(255, 255, 255, 255)));
	_world.addTransformComponent(_id[SCORE], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0, 15.0f)));

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



void						GameState::update(const sf::Time &elapsed)
{
	ParticleSystem::update(_world, elapsed);
	TransformSystem::update(_world, elapsed);
	AnimationSystem::update(_world, elapsed);
	this->updateHUD();
}

void						GameState::updateHUD()
{
	this->updateLife();
	this->updateLifeBoss();
	this->updateShield();
	this->updateAmo();
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
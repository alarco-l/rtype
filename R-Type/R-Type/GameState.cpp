#include "GameState.h"
#include "GUIPauseState.h"
#include "GUIEndState.h"

GameState::GameState(Game *game) : AState(game)
{
	_isBlocking = true;
}

GameState::~GameState()
{
}

void						GameState::initializePlayer(ResourceManager &resourceManager) {
	 //create player
	_idPlayer = _world.createEmptyEntity();
	_world.addRenderComponent(_idPlayer, ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/hero.png"), 1));
	_world.addTransformComponent(_idPlayer, ComponentFactory::createTransformComponent(sf::Vector2f(1021, 748), sf::Vector2f(0, 0), sf::Vector2f(0.15f, 0.15f)));
	_world.addMovementComponent(_idPlayer, ComponentFactory::createMovementComponent(200, sf::Vector2f()));
}

void						GameState::initialize(ResourceManager &resourceManager)
{
	this->initializeBackground(resourceManager);
	this->initializeHUD(resourceManager);
	this->initializePlayer(resourceManager);
}


bool						GameState::handleKeyState() {
	_world.movementComponents[_idPlayer]->direction = sf::Vector2f();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		_world.movementComponents[_idPlayer]->direction += sf::Vector2f(0, -1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		_world.movementComponents[_idPlayer]->direction += sf::Vector2f(0, 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		_world.movementComponents[_idPlayer]->direction += sf::Vector2f(-1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		_world.movementComponents[_idPlayer]->direction += sf::Vector2f(1, 0);
	}
	return (true);
}

bool						GameState::handleKeyEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		_game->pushState(new GUIPauseState(_game));
		return (true);
	}

	// simuler une fin de partie
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
		_game->pushState(new GUIEndState(_game, GUIEndState::LOSE));
		return (true);
	}
	return (true);
}

void						GameState::update(const sf::Time &elapsed)
{
	ParticleSystem::update(_world, elapsed);
	TransformSystem::update(_world, elapsed);
	CollisionSystem::update(_world, sf::Vector2u(10, 10), _game->getScreenSize());
	AnimationSystem::update(_world, elapsed);
	this->updateBackground();
	this->updateHUD();
	this->updatePlayer();
}

void						GameState::initializeHUD(ResourceManager &resourceManager)
{
	sf::Vector2u			screenSize = _game->getScreenSize();

	_idHud[SHIELDTEXT] = _world.createEmptyEntity();
	_world.addTextComponent(_idHud[SHIELDTEXT], ComponentFactory::createTextComponent("Shield", resourceManager.getFont("fonts/BMSPA.ttf"), false, false, 18, sf::Color(255, 255, 255, 255)));
	_world.addTransformComponent(_idHud[SHIELDTEXT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(25.0f, screenSize.y - 38.0f)));

	_idHud[SHIELDBAR] = _world.createEmptyEntity();
	_world.addRenderComponent(_idHud[SHIELDBAR], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/unicolor.png"), 0, sf::Color(13, 205, 248)));
	_world.addTransformComponent(_idHud[SHIELDBAR], ComponentFactory::createTransformComponent(sf::Vector2f(200, 10), sf::Vector2f(120.0f, screenSize.y - 30.0f)));

	_idHud[LIFETEXT] = _world.createEmptyEntity();
	_world.addTextComponent(_idHud[LIFETEXT], ComponentFactory::createTextComponent("Life", resourceManager.getFont("fonts/BMSPA.ttf"), false, false, 18, sf::Color(255, 255, 255, 255)));
	_world.addTransformComponent(_idHud[LIFETEXT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(25.0f, screenSize.y - 58.0f)));

	_idHud[LIFEBAR] = _world.createEmptyEntity();
	_world.addRenderComponent(_idHud[LIFEBAR], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/unicolor.png"), 0, sf::Color::Green));
	_world.addTransformComponent(_idHud[LIFEBAR], ComponentFactory::createTransformComponent(sf::Vector2f(200, 10), sf::Vector2f(120.0f, screenSize.y - 50.0f)));

	_idHud[BOSSLIFEBAR] = _world.createEmptyEntity();
	_world.addRenderComponent(_idHud[BOSSLIFEBAR], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/unicolor.png"), 0, sf::Color::Red));
	_world.addTransformComponent(_idHud[BOSSLIFEBAR], ComponentFactory::createTransformComponent(sf::Vector2f(500, 10), sf::Vector2f(screenSize.x / 2 - 250.0f, 50.0f)));

	_idHud[WEAPON1] = _world.createEmptyEntity();
	_world.addRenderComponent(_idHud[WEAPON1], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/laser_icon.png")));
	_world.addTransformComponent(_idHud[WEAPON1], ComponentFactory::createTransformComponent(sf::Vector2f(50, 50), sf::Vector2f(screenSize.x - screenSize.x / 7.0f, screenSize.y - 70.0f)));

	_idHud[WEAPON2] = _world.createEmptyEntity();
	_world.addRenderComponent(_idHud[WEAPON2], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/mine_icon.png")));
	_world.addTransformComponent(_idHud[WEAPON2], ComponentFactory::createTransformComponent(sf::Vector2f(50, 50), sf::Vector2f(screenSize.x - screenSize.x / 7.0f + 70, screenSize.y - 70.0f)));

	_idHud[WEAPON3] = _world.createEmptyEntity();
	_world.addRenderComponent(_idHud[WEAPON3], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/missile_icon.png"), 0, sf::Color::Green));
	_world.addTransformComponent(_idHud[WEAPON3], ComponentFactory::createTransformComponent(sf::Vector2f(50, 50), sf::Vector2f(screenSize.x - screenSize.x / 7.0f - 70, screenSize.y - 70.0f)));

	_idHud[SCORE] = _world.createEmptyEntity();
	_world.addTextComponent(_idHud[SCORE], ComponentFactory::createTextComponent("Score : 1000000", resourceManager.getFont("fonts/BMSPA.ttf"), true, false, 18, sf::Color(255, 255, 255, 255)));
	_world.addTransformComponent(_idHud[SCORE], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0, 15.0f)));
}

void						GameState::initializeBackground(ResourceManager &resourceManager)
{
	_idBackground[0] = _world.createEmptyEntity();
	_world.addRenderComponent(_idBackground[0], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/background.png"), 30));
	_world.addTransformComponent(_idBackground[0], ComponentFactory::createTransformComponent(sf::Vector2f(_game->getScreenSize()), sf::Vector2f(0.0f, 0.0f)));
	_world.addScrollComponent(_idBackground[0], ComponentFactory::createScrollComponent(20.0f));

	_idBackground[1] = _world.createEmptyEntity();
	_world.addRenderComponent(_idBackground[1], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/background_reversed.png"), 25));
	_world.addTransformComponent(_idBackground[1], ComponentFactory::createTransformComponent(sf::Vector2f(_game->getScreenSize()), sf::Vector2f(static_cast<float>(_game->getScreenSize().x), 0.0f)));
	_world.addScrollComponent(_idBackground[1], ComponentFactory::createScrollComponent(20.0f));
}

void						GameState::updateHUD()
{
	this->updateLife();
	this->updateLifeBoss();
	this->updateShield();
	this->updateAmo();
}

void						GameState::updateBackground()
{
	if (_world.transformComponents[_idBackground[0]]->position.x + _world.transformComponents[_idBackground[0]]->size.x <= 0.0f)
		_world.transformComponents[_idBackground[0]]->position.x = _world.transformComponents[_idBackground[0]]->size.x;

	if (_world.transformComponents[_idBackground[1]]->position.x + _world.transformComponents[_idBackground[1]]->size.x <= 0.0f)
		_world.transformComponents[_idBackground[1]]->position.x = _world.transformComponents[_idBackground[1]]->size.x;
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
void						GameState::updatePlayer() {
	_world.movementComponents[_idPlayer]->direction = sf::Vector2f(0, 0);
}
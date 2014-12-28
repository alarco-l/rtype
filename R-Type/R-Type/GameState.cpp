#include "GameState.h"
#include "GUIPauseState.h"
#include "GUIEndState.h"
#include "RFCClient.h"

GameState::GameState(Game *game) : AState(game)
{
	_isBlocking = true;
}

GameState::~GameState() {}

void	GameState::onConnectEvent(Network::Client &client)
{
	_rfc = new RFCClient(client.socket);
	//client.socket.onRecive(::hpl::bind(&GameState::onRecive, this, ::hpl::Placeholder::_1));
	client.socket.onEnd(::hpl::bind(&GameState::onEnd, this, ::hpl::Placeholder::_1));
}

void	GameState::onRecive(Network::Socket &socket) {}
void	GameState::onEnd(Network::Socket const &socket) {}

void						GameState::initialize(ResourceManager &resourceManager)
{
	_client = Network::Client::connect<Network::udp::ip4>(Network::Client::Config("127.0.0.1", 2222), ::hpl::bind(&GameState::onConnectEvent, this, ::hpl::Placeholder::_1));
	this->initializeBackground(resourceManager);
	this->initializeHUD(resourceManager);
	this->initializePlayer(resourceManager);
}

void						GameState::stop(void)
{
	_client->socket.close();
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

bool						GameState::handleKeyState()
{
	sf::Vector2f			direction = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f			size = _world.transformComponents[_idPlayer[SHIP]]->size;
	sf::Vector2f			scale = _world.transformComponents[_idPlayer[SHIP]]->scale;
	sf::Vector2f			pos = _world.transformComponents[_idPlayer[SHIP]]->position;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pos.y > 0)
		direction += sf::Vector2f(0, -1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pos.y < _game->getScreenSize().y - (size.y * scale.y))
		direction += sf::Vector2f(0, 1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pos.x > 0)
		direction += sf::Vector2f(-1, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pos.x < _game->getScreenSize().x - (size.x * scale.x))
		direction += sf::Vector2f(1, 0);

	_world.movementComponents[_idPlayer[SHIP]]->direction = direction;
	_world.movementComponents[_idPlayer[MOTORUP]]->direction = direction;
	_world.movementComponents[_idPlayer[MOTORDOWN]]->direction = direction;

	return (true);
}

void						GameState::update(const sf::Time &elapsed)
{
	ParticleSystem::update(_world, elapsed);
	TransformSystem::update(_world, elapsed, _rfc);
	CollisionSystem::update(_world, sf::Vector2u(10, 10), _game->getScreenSize(), _rfc);
	AnimationSystem::update(_world, elapsed);
	this->updateBackground();
	this->updateHUD();
}

void						GameState::initializeHUD(ResourceManager &resourceManager)
{
	sf::Vector2u			screenSize = _game->getScreenSize();

	_idHud[SHIELDTEXT] = _world.createEmptyEntity();
	_world.addTextComponent(_idHud[SHIELDTEXT], ComponentFactory::createTextComponent("Shield", resourceManager.getFont("fonts/BMSPA.ttf"), false, false, 18, sf::Color(255, 255, 255, 255)));
	_world.addTransformComponent(_idHud[SHIELDTEXT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(25.0f, screenSize.y - 38.0f)));

	_idHud[SHIELDBAR] = _world.createEmptyEntity();
	_world.addRenderComponent(_idHud[SHIELDBAR], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/unicolor.png"), RenderComponent::Plane::HUD, sf::Color(13, 205, 248)));
	_world.addTransformComponent(_idHud[SHIELDBAR], ComponentFactory::createTransformComponent(sf::Vector2f(200, 10), sf::Vector2f(120.0f, screenSize.y - 30.0f)));

	_idHud[LIFETEXT] = _world.createEmptyEntity();
	_world.addTextComponent(_idHud[LIFETEXT], ComponentFactory::createTextComponent("Life", resourceManager.getFont("fonts/BMSPA.ttf"), false, false, 18, sf::Color(255, 255, 255, 255)));
	_world.addTransformComponent(_idHud[LIFETEXT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(25.0f, screenSize.y - 58.0f)));

	_idHud[LIFEBAR] = _world.createEmptyEntity();
	_world.addRenderComponent(_idHud[LIFEBAR], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/unicolor.png"), RenderComponent::Plane::HUD, sf::Color::Green));
	_world.addTransformComponent(_idHud[LIFEBAR], ComponentFactory::createTransformComponent(sf::Vector2f(200, 10), sf::Vector2f(120.0f, screenSize.y - 50.0f)));

	_idHud[BOSSLIFEBAR] = _world.createEmptyEntity();
	_world.addRenderComponent(_idHud[BOSSLIFEBAR], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/unicolor.png"), RenderComponent::Plane::HUD, sf::Color::Red));
	_world.addTransformComponent(_idHud[BOSSLIFEBAR], ComponentFactory::createTransformComponent(sf::Vector2f(500, 10), sf::Vector2f(screenSize.x / 2 - 250.0f, 50.0f)));

	_idHud[WEAPON1] = _world.createEmptyEntity();
	_world.addRenderComponent(_idHud[WEAPON1], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/laser_icon.png"), RenderComponent::Plane::HUD));
	_world.addTransformComponent(_idHud[WEAPON1], ComponentFactory::createTransformComponent(sf::Vector2f(50, 50), sf::Vector2f(screenSize.x - screenSize.x / 7.0f, screenSize.y - 70.0f)));

	_idHud[WEAPON2] = _world.createEmptyEntity();
	_world.addRenderComponent(_idHud[WEAPON2], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/mine_icon.png"), RenderComponent::Plane::HUD));
	_world.addTransformComponent(_idHud[WEAPON2], ComponentFactory::createTransformComponent(sf::Vector2f(50, 50), sf::Vector2f(screenSize.x - screenSize.x / 7.0f + 70, screenSize.y - 70.0f)));

	_idHud[WEAPON3] = _world.createEmptyEntity();
	_world.addRenderComponent(_idHud[WEAPON3], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/missile_icon.png"), RenderComponent::Plane::HUD, sf::Color::Green));
	_world.addTransformComponent(_idHud[WEAPON3], ComponentFactory::createTransformComponent(sf::Vector2f(50, 50), sf::Vector2f(screenSize.x - screenSize.x / 7.0f - 70, screenSize.y - 70.0f)));

	_idHud[SCORE] = _world.createEmptyEntity();
	_world.addTextComponent(_idHud[SCORE], ComponentFactory::createTextComponent("Score : 1000000", resourceManager.getFont("fonts/BMSPA.ttf"), true, false, 18, sf::Color(255, 255, 255, 255)));
	_world.addTransformComponent(_idHud[SCORE], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0, 15.0f)));
}

void						GameState::initializeBackground(ResourceManager &resourceManager)
{
	_idBackground[0] = _world.createEmptyEntity();
	_world.addRenderComponent(_idBackground[0], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/background.png"), RenderComponent::Plane::BACKGROUND));
	_world.addTransformComponent(_idBackground[0], ComponentFactory::createTransformComponent(sf::Vector2f(_game->getScreenSize()), sf::Vector2f(0.0f, 0.0f)));
	_world.addScrollComponent(_idBackground[0], ComponentFactory::createScrollComponent(20.0f));

	_idBackground[1] = _world.createEmptyEntity();
	_world.addRenderComponent(_idBackground[1], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/background_reversed.png"), RenderComponent::Plane::BACKGROUND));
	_world.addTransformComponent(_idBackground[1], ComponentFactory::createTransformComponent(sf::Vector2f(_game->getScreenSize()), sf::Vector2f(static_cast<float>(_game->getScreenSize().x), 0.0f)));
	_world.addScrollComponent(_idBackground[1], ComponentFactory::createScrollComponent(20.0f));
}

void						GameState::initializePlayer(ResourceManager &resourceManager)
{
	_idPlayer[SHIP] = _world.createEmptyEntity();
	_world.addRenderComponent(_idPlayer[SHIP], ComponentFactory::createRenderComponent(resourceManager.getTexture("textures/hero.png"), RenderComponent::Plane::DEFAULT));
	_world.addTransformComponent(_idPlayer[SHIP], ComponentFactory::createTransformComponent(sf::Vector2f(1021, 748), sf::Vector2f(0, 0), sf::Vector2f(0.15f, 0.15f)));
	_world.addMovementComponent(_idPlayer[SHIP], ComponentFactory::createMovementComponent(500, sf::Vector2f()));

	_idPlayer[MOTORUP] = _world.createParticleEffect(25, true, resourceManager.getTexture("textures/fireMotor.png"), sf::Vector2f(-18, 0), sf::Vector2f(0.3f, 0.3f));
	_world.addMovementComponent(_idPlayer[MOTORUP], ComponentFactory::createMovementComponent(500, sf::Vector2f()));
	_world.emitterComponents[_idPlayer[MOTORUP]]->lifetimeInterval = sf::Vector2f(0.1f, 0.2f);
	_world.emitterComponents[_idPlayer[MOTORUP]]->propagationInterval = sf::Vector2f(170.0f, 190.0f);
	_world.emitterComponents[_idPlayer[MOTORUP]]->velocityInterval = sf::Vector2f(100.0f, 200.0f);

	_idPlayer[MOTORDOWN] = _world.createParticleEffect(25, true, resourceManager.getTexture("textures/fireMotor.png"), sf::Vector2f(-18, 81), sf::Vector2f(0.3f, 0.3f));
	_world.addMovementComponent(_idPlayer[MOTORDOWN], ComponentFactory::createMovementComponent(500, sf::Vector2f()));
	_world.emitterComponents[_idPlayer[MOTORDOWN]]->lifetimeInterval = sf::Vector2f(0.1f, 0.2f);
	_world.emitterComponents[_idPlayer[MOTORDOWN]]->propagationInterval = sf::Vector2f(170.0f, 190.0f);
	_world.emitterComponents[_idPlayer[MOTORDOWN]]->velocityInterval = sf::Vector2f(100.0f, 200.0f);
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

#include <SFML/Graphics.hpp>

#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "R-Type");
	sf::Clock clock;
	sf::Texture texture;
	sf::Sprite sprite;
	float R = 100.f;
	float d = 50.f;
	float x, y = 0.f;

	if (!texture.loadFromFile("../R-Type/textures/hero.png"))
		return 1;
	sprite.setTexture(texture);
	sprite.scale(sf::Vector2f(0.05, 0.20));
	sprite.setPosition(sf::Vector2f(0, 0));
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		x = (R * clock.getElapsedTime().asSeconds()) - (d * sin((clock.getElapsedTime().asSeconds())));
		y = (R - d * cos((clock.getElapsedTime().asSeconds())));
		sprite.setPosition(sf::Vector2f(x, y));
		window.clear();
		window.draw(sprite);
		window.display();
	}
	return(0);
}
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class cEntity
{
public:
	sf::Vector2f position = { 0, 0 };
	sf::Vector2f direction = { 1, 0};
	void draw(sf::RenderWindow& window);
private:
	//sf::Shape shape;
	
};


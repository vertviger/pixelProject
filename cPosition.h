#pragma once
#include <SFML/Graphics.hpp>
class cPosition
{
public: 
	int x;
	int y;
	int cursorX = sf::Mouse::getPosition().x;
	int cursorY = sf::Mouse::getPosition().y;
	sf::Vector2f position = {x, y};
	sf::Vector2f direction = {cursorX, cursorY};
private:

};


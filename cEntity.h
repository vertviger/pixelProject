#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "cPosition.h"
class cEntity
{
public:
	cPosition position;
	void drawEntity(int x, int y);
private:
	sf::RectangleShape shape = sf::RectangleShape(position.position);
	cPosition setPosition(int x, int y)
	{
		return pu
	}
};


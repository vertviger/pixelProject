#pragma once
#include <SFML/Graphics.hpp>
class cEventHandler
{
public:
	void reactToEvent(std::optional<sf::Event> event);
};



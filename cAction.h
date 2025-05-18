#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#pragma once

class cEntity;

class cAction
{
public:
	cAction(const std::string& name, cEntity* _owner);
	bool Do(cEntity* _target); // return true if finished action
	bool Can(cEntity* _target);
private:
	sf::Vector2f randOffset;
	struct cConfig;
	const cConfig* config = NULL;
	cEntity* owner = NULL;
	sf::Clock clockForAction;
	bool Teleport(sf::Vector2f newPos);
};

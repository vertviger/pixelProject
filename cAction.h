#include <SFML/Graphics.hpp>

#pragma once

enum cActionType { A_NONE, A_MOVE_LEFT, A_MOVE_RIGHT, A_MOVE_STOP_X, A_MOVE_STOP_Y, A_MOVE_UP, A_MOVE_DOWN, A_TELEPORT, A_FIREBALL };

class cEntity;

class cTarget
{
	sf::Vector2f position;
	const cEntity* entity = NULL;
};

/*
class cAction
{
public:
	static const cAction* Get(cActionType);
	virtual bool Can(const cEntity* _who, const cTarget& _target) = 0;
	virtual void Do(const cEntity* _who, const cTarget& _target) = 0;
};
*/
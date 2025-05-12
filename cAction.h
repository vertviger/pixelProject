#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#pragma once

enum cActionType { A_NONE, A_TELEPORT, A_FIREBALL, A_SPEED, A_TRANSFORM, A_ATTACK_MELEE};

class cEntity;

class cTarget
{
	sf::Vector2f position;
	cEntity* entity = NULL;
};


class cAction
{
public:
	cAction(const std::string& name, cEntity* _owner);
	//virtual bool Can(const cEntity* _who, const cTarget& _target) = 0;
	bool Do(cEntity* _target); // return false if finished action
private:
	void Move(cEntity* target);
	struct cConfig;
	const cConfig* config = NULL;
	cEntity* owner = NULL;
	sf::Clock clockForAction;
};

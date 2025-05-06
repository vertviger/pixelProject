#pragma once
#include <SFML/Graphics.hpp>
#include "cAction.h"
#include <optional>
#include <map>


class cGameControl
{
public:
	cGameControl();
	~cGameControl();
	static cGameControl* Get();
	void Draw(sf::RenderWindow& window);
	void EventHandle(std::optional<sf::Event> event);
	void ControledEntity(cEntity* _e) { controlledEntity = _e; }

private:
	cActionType selectedAction = A_NONE;
	sf::Sprite* slotsSprite;
	std::map<cActionType, sf::Sprite*> actionSprites;
	cEntity* controlledEntity = NULL;
};


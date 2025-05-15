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
	void Quant();
	void Draw(sf::RenderWindow& window);
	void EventHandle(std::optional<sf::Event> event);
	void ControledEntity(cEntity* _e) { controlledEntity = _e; }
	cEntity* ControledEntity() const { return controlledEntity; }
private:
	cEntity* target = NULL;
	cAction* action = NULL;
	std::string selectedActionName;
	sf::Sprite* slotsSprite;
	std::vector<sf::Sprite*> actionSprites;
	cEntity* controlledEntity = NULL;
};


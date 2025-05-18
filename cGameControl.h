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
	static cGameControl& Get();
	void Quant();
	void Draw(sf::RenderWindow& window);
	void EventHandle(std::optional<sf::Event> event);
	void ControledEntity(cEntity* _e);
	cEntity* ControledEntity() const { return controlledEntity; }
	void SelectAction(int number);
private:
	cEntity* GetTarget(const sf::Vector2i& mousePos) const;
	cEntity* target = NULL;
	cAction* actionSelected = NULL;
	cAction* action = NULL;
	int selectedActionIdx = 0;
	sf::Sprite slotsSprite;
	sf::Sprite hpBar;
	std::vector<sf::Sprite> actionSprites;
	cEntity* controlledEntity = NULL;
	const sf::Cursor cursorCant = sf::Cursor::createFromSystem(sf::Cursor::Type::NotAllowed).value();
	const sf::Cursor cursorCan = sf::Cursor::createFromSystem(sf::Cursor::Type::Cross).value();
};


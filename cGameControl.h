#pragma once
#include <SFML/Window/Event.hpp>
#include "cAction.h"
#include <optional>

class cGameControl
{
public:
	static cGameControl* Get();
	void EventHandle(std::optional<sf::Event> event);
private:
	cActionType selectedAction = A_NONE;
};


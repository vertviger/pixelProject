#pragma once
#include <vector>
#include "cEntity.h"
class cScene
{
public: 
	cEntity* controlledEntity();
	void draw(sf::RenderWindow& window);
	void onKeyReleased(sf::Event::KeyReleased key);
	//void spawn();
private:
	std::vector<cEntity> entities;
};


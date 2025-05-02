#pragma once
#include <vector>
#include "cEntity.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class cScene
{
public: 
	cScene();
	~cScene();
	cEntity* AddEnity();
	cEntity* ControlledEntity();
	static cScene* Get();
	void Draw(RenderWindow& window);
	void EventHandle(optional<Event> event);
	//void spawn();
private:
	vector<cEntity> entities;
};


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
	Vector2f GetSize() { return size; }
	//void spawn();
private:
	vector<cEntity*> entities;
	Vector2f size = {16.0f, 9.0f};
};


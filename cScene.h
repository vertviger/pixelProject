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
	static cScene* Get();

	cEntity*	Spawn(const string& _name);
	void		Draw(RenderWindow& window);
	cEntity*	FindEntity(Vector2f pos);
	Vector2f	GetSize() { return size; }
	const vector<cEntity*>& Entities() const { return entities; }
	void		Quant(float deltaTimeSec);
private:
	vector<cEntity*> entities;
	Vector2f size = {16.0f, 9.0f};
};


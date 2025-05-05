#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "cAction.h"

using namespace std;
using namespace sf;

class cEntity
{
public:
	cEntity();
	~cEntity();
	void ChangePosition(const Vector2f& newPosition)
	{
		position = newPosition;
	}
	void ChangeDirection(const Vector2f& newDirection)
	{
		lookAt = newDirection;
	}
	const Vector2f& GetPosition() const
	{
		return position;
	}
	const Vector2f& GetDirection() const
	{
		return lookAt;
	}

	void StartAction(cActionType _at, const cTarget& _t);
	void Quant(float _deltaTimeSec);
	void Draw(RenderWindow& window);

	sf::Sprite* sprite = NULL;
private:

	bool Can(cActionType);

	Vector2f position = { 8.0 , 4.5 };
	Vector2f lookAt;
	Vector2f move_direction = { 0, 0 }; // x < 0 - left, x > 0 - right, y > 0 - up, y < 0 - down
	Vector2f size = { 0.8, 1 };
	float mana = 100.0f;
	const float maxMovementSpeed = 1.0f; // m/s
	cActionType currentAction = A_NONE;
};


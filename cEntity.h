#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

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
		direction = newDirection;
	}
	const Vector2f& GetPosition() const
	{
		return position;
	}
	const Vector2f& GetDirection() const
	{
		return direction;
	}
	void Jump();
	void Sneak();
	void GoRight();
	void GoLeft();
	void Draw(RenderWindow& window);
	sf::Sprite* sprite = NULL;
private:
	Vector2f position = { 8.0 , 4.5 };
	Vector2f direction = { 1, 0 };
	Vector2f size = { 1, 1 };
};


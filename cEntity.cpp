#include "cEntity.h"

void cEntity::Draw(sf::RenderWindow& window)
{
	auto shape = CircleShape(20, 6);
	shape.setFillColor(Color::Cyan);
	shape.setPosition(position);
	window.draw(shape);
}
void cEntity::Jump()
{
	Vector2f currentPos = GetPosition();
	Vector2f newPos = { currentPos.x ,(currentPos.y - 1) };
	ChangePosition(newPos);
}
void cEntity::Sneak()
{
	Vector2f currentPos = GetPosition();
	Vector2f newPos = { currentPos.x ,(currentPos.y + 1) };
	ChangePosition(newPos);
}
void cEntity::GoRight()
{
	Vector2f currentPos = GetPosition();
	Vector2f newPos = { (currentPos.x - 1) ,currentPos.y };
	ChangePosition(newPos);
}
void cEntity::GoLeft()
{
	Vector2f currentPos = GetPosition();
	Vector2f newPos = { (currentPos.x + 1) ,currentPos.y };
	ChangePosition(newPos);
}

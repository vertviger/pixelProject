#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "cAction.h"

using namespace std;
using namespace sf;

class cBrain;

class cEntity
{
public:
	cEntity(const string& _name);
	~cEntity();
	void ChangePosition(const Vector2f& newPosition)
	{
		position = newPosition;
	}
	const Vector2f& GetPosition() const
	{
		return position;
	}
	FloatRect Bound() const { return FloatRect(position - Vector2f(size.x/2, size.y/2), size);}
	float Health(){ return health;}
	float HealthPercentage();
	void SetMoveDirection(const Vector2f& newDirection) { moveDirection = newDirection; }
	void Quant(float _deltaTimeSec);
	void Draw(RenderWindow& window);
	void TakeDamage(float damage);
	const string& Name() const { return name; }
	
protected:
	struct cConfig;
private:
	Vector2f position = { 8.0 , 4.5 };
	Vector2f moveDirection = { 0, 0 }; // x < 0 - left, x > 0 - right, y > 0 - up, y < 0 - down
	Vector2f size = { 1, 1 };
	const cConfig* config;
	float mana = 100.0f;
	float health = 100.0f;
	float maxMovementSpeed = 1.0f; // m/s
	cActionType currentAction = A_NONE;
	cBrain* brain = NULL;
	std::string name;
	Clock damageClock;
	sf::Sprite* sprite = NULL;
	sf::Sprite* sprite100 = NULL;
	sf::Sprite* sprite75 = NULL;
	sf::Sprite* sprite50 = NULL;
	sf::Sprite* sprite25 = NULL;
};


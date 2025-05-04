#include "cEntity.h"
#include "cScene.h"
#include "cGraphics.h"

Vector2f CameraScale(Vector2f scenePos)
{
	return { scenePos.x * 120, scenePos.y * 120 };
}
void cEntity::Draw(sf::RenderWindow& window)
{
	if (!sprite) return;
	auto scene = cScene::Get();
	float kx = window.getSize().x / scene->GetSize().x;
	float ky = window.getSize().y / scene->GetSize().y;
	sprite->setPosition({ position.x * kx, position.y * ky });
	window.draw(*sprite);
}
cEntity::cEntity()
{
	const Texture& texture = GetTexture("../Visuals/Sprites/player.png");
	sprite = new Sprite(texture);
	sprite->setPosition(position);
}
cEntity::~cEntity()
{
	if (sprite) delete sprite;
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

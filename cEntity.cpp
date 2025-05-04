#include "cEntity.h"
#include "cScene.h"
#include "cGraphics.h"

void cEntity::Draw(sf::RenderWindow& window)
{
	if (!sprite) return;
	auto scene = cScene::Get();
	float kx = window.getSize().x / scene->GetSize().x;
	float ky = window.getSize().y / scene->GetSize().y;
	Vector2f origin = { position.x * kx, position.y * ky };
	origin.x -= (size.x / 2) * kx; // shifting position cords to the middle of the sprite X axis
	origin.y -= size.y * ky; // shifting position cords to the middle of the sprite Y axis
	sprite->setPosition(origin);
	Vector2u textureSize = sprite->getTexture().getSize();
	Vector2f textureSizeF = { (float)textureSize.x, (float)textureSize.y };
	Vector2f scale = { (size.x * kx)/textureSizeF.x, (size.y * ky) / textureSizeF.y};
	sprite->setScale(scale);
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

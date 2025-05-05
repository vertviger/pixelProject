#include "cEntity.h"
#include "cScene.h"
#include "cGraphics.h"

void cEntity::Draw(sf::RenderWindow& window)
{
	if (!sprite) return;
	auto scene = cScene::Get();
	Vector2f screen_size = window.getView().getSize();
	float kx = screen_size.x / scene->GetSize().x;
	float ky = screen_size.y / scene->GetSize().y;
	Vector2f pos = { position.x * kx, position.y * ky };
	sprite->setPosition(pos);
	Vector2u textureSize = sprite->getTexture().getSize();
	Vector2f textureSizeF = { (float)textureSize.x, (float)textureSize.y };
	Vector2f origin = textureSizeF;
	origin.x *= 0.5f; // shifting position cords to the middle of the sprite X axis
	sprite->setOrigin(origin);
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

void cEntity::StartAction(cActionType _at, const cTarget& _t)
{
	if(!Can(_at)) return;
	switch(_at)
	{
	case A_NONE:
		break;
	case A_MOVE_LEFT:
		move_direction = { -1.0f , 0.0f };
		break;
	case A_MOVE_RIGHT:
		break;
	case A_MOVE_STOP:
		move_direction = { 1.0f , 0.0f };
		break;
	case A_JUMP:
		move_direction.y = 1.0f;
		break;
	case A_TELEPORT:
		break;
	case A_FIREBALL:
		break;
	default:
		break;
	}
}

bool cEntity::Can(cActionType _a)
{
	switch(_a)
	{
	case A_NONE:
		break;
	case A_MOVE_LEFT:
		break;
	case A_MOVE_RIGHT:
		break;
	case A_MOVE_STOP:
		break;
	case A_JUMP:
		break;
	case A_TELEPORT:
		break;
	case A_FIREBALL:
		break;
	default:
		break;
	}
	return true;
}

void cEntity::Quant(float _deltaTimeSec)
{
	// process movement and jump and spells
}

/*
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
*/
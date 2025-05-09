#include "cEntity.h"
#include "cScene.h"
#include "cGraphics.h"
#include "cBrain.h"

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
	origin.y *= 0.5f; // shifting position cords to the middle of the sprite Y axis
	sprite->setOrigin(origin);
	Vector2f scale = { (size.x * kx)/textureSizeF.x, (size.y * ky) / textureSizeF.y};
	sprite->setScale(scale);
	window.draw(*sprite);
}

cEntity::cEntity(const string& _name) : name(_name)
{
	//to do load config by name
	if (!config.brainName.empty())
	{
		brain = new cBrain(this, config.brainName);
	}
	const Texture& texture = GetTexture("../resources/Visuals/Sprites/" +_name+ ".png");
	sprite = new Sprite(texture);
	sprite->setPosition(position);
	if (_name == "tree")
	{
		size = { 3.0, 3.0 };
	}
	else if(_name == "player")
	{
		size = { 0.8, 1.0 };
	}
}
cEntity::~cEntity()
{
	if (sprite) delete sprite;
	delete brain;
}

void cEntity::StartAction(cActionType _at, const cTarget& _t)
{
	if(!Can(_at)) return;
	switch(_at)
	{
	case A_NONE:
		break;
	case A_MOVE_LEFT:
		moveDirection.x = -1.0f;
		break;
	case A_MOVE_RIGHT:
		moveDirection.x = 1.0f;
		break;
	case A_MOVE_STOP_X:
		moveDirection.x = 0.0f;
		break;
	case A_MOVE_STOP_Y:
		moveDirection.y = 0.0f;
		break;
	case A_MOVE_UP:
		moveDirection.y = -1.0f;
		break;
	case A_MOVE_DOWN:
		moveDirection.y = +1.0f;
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
	case A_TELEPORT:
		//return mana > 25.0f;  
		break;
	case A_FIREBALL:
		//return mana > 10.0f;  
		break;
	default:
		break;
	}
	return true;
}

void cEntity::Quant(float _deltaTimeSec)
{
	if (brain)
	{
		brain->Think();
	}
	//if (moveDirection.x != 0 && moveDirection.y != 0) moveDirection = moveDirection.normalized();
	position += (moveDirection * maxMovementSpeed) * _deltaTimeSec;
	// process movement and jump and spells
}

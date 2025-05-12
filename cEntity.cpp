#include "cEntity.h"
#include "cScene.h"
#include "cGraphics.h"
#include "cBrain.h"
#include <map>
#include <fstream>
#include <iostream>

struct cEntity::cConfig
{
	static const cConfig* Get(const std::string& name);
	bool loaded = false;
	float maxMana = 100.0f;
	float maxHealth = 100.0f;
	float maxMovementSpeed = 1.0f;
	string brainName;
};
const cEntity::cConfig* cEntity::cConfig::Get(const std::string& _name)
{
	static map<std::string, cEntity::cConfig> configStorage;
	cEntity::cConfig& config = configStorage[_name];
	if (config.loaded) return &config;

	config.loaded = true;
	std::string path = "../assets/entities/" + _name + ".txt";
	auto file = std::fstream(path);
	if (file.is_open())
	{
		auto words = std::string();
		while (getline(file, words))
		{
			stringstream s(words);
			string str;
			s >> str;
			if (str == "health")
			{
				while (s >> str)
				{
					config.maxHealth = std::stof(str);
				}
			}
			else if (str == "mana")
			{
				while (s >> str)
				{
					config.maxMana = std::stof(str);
				}
			}
			else if (str == "movementSpeed")
			{
				while (s >> str)
				{
					config.maxMovementSpeed = std::stof(str);
				}
			}
			else if (str == "brainName")
			{
				while (s >> str)
				{
					config.brainName = str;
				}
			}
		}
	}
	else
	{
		std::cout << "File not found: " << path << std::endl;
	}
	return &config;
}

void cEntity::Draw(sf::RenderWindow& window)
{
	if (!sprite) return;
	if (health <= 0) return;
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

void cEntity::TakeDamage(float damage)
{
	std::srand(std::time({}));
	string damageStr = to_string((int)damage);
	int damageTextSize = int(damage / 5);
	float randPosX = std::rand() / RAND_MAX * 0.1f - 0.05f;
	float randPosY = std::rand() / RAND_MAX * 0.1f - 0.05f;
	ShowText(damageStr, sf::Vector2f(position.x, position.y - size.y * 0.5f), Color::Red, 3.0f);

	health -= damage;
	if (health <= 0) return;
	if (health >= 75);
	else if (health >= 50) sprite = sprite75;
	else if (health >= 25) sprite = sprite50;
	else if (health >= 0) sprite = sprite25;
}

cEntity::cEntity(const string& _name) : name(_name)
{
	config = cConfig::Get(_name);
	if (!config->brainName.empty())
	{
		brain = new cBrain(this, config->brainName);
	}
	mana = config->maxMana;
	health = config->maxHealth;
	maxMovementSpeed = config->maxMovementSpeed;
	const Texture& texture = GetTexture("../assets/Visuals/Sprites/" +_name+ "100.png");
	sprite100 = new Sprite(texture);
	sprite100->setPosition(position);
	sprite = sprite25 = sprite50 = sprite75 = sprite100; //to do make correct sprites setup
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
	if (sprite100) delete sprite100;
	/*if (sprite75) delete sprite75;
	if (sprite50) delete sprite50;
	if (sprite25) delete sprite25;*/
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
	if (health <= 0) return;
	if (brain) brain->Think();
	//if (moveDirection.x != 0 && moveDirection.y != 0) moveDirection = moveDirection.normalized();
	position += (moveDirection * maxMovementSpeed) * _deltaTimeSec;
	// process movement and jump and spells
}

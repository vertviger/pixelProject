#include "cEntity.h"
#include "cScene.h"
#include "cGraphics.h"
#include "cBrain.h"
#include <map>
#include <fstream>
#include <filesystem>
#include <iostream>

struct cEntity::cConfig
{
	static const cConfig* Get(const std::string& name);
	bool loaded = false;
	float maxMana = 100.0f;
	float maxHealth = 100.0f;
	float maxMovementSpeed = 1.0f;
	float sizeX = 1.0f;
	float sizeY = 1.0f;
	string brainName;
};
const cEntity::cConfig* cEntity::cConfig::Get(const std::string& _name)
{
	static map<std::string, cEntity::cConfig> configStorage;
	cEntity::cConfig& config = configStorage[_name];
	if (config.loaded) return &config;

	config.loaded = true;
	std::string path = AssetsPath() + "entities/" + _name + ".txt";
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
			else if (str == "sizeX")
			{
				while (s >> str)
				{
					config.sizeX = std::stof(str);
				}
			}
			else if (str == "sizeY")
			{
				while (s >> str)
				{
					config.sizeY = std::stof(str);
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
	Vector2f scale = { (size.x * kx)/textureSizeF.x, (size.y * ky) / textureSizeF.y};
	sprite->setScale(scale);
	window.draw(*sprite);
}
float RandValue()
{
	//std::srand(std::time({}));
	return (float)std::rand() / (RAND_MAX + 2);
}
void cEntity::TakeDamage(float damage)
{
	string damageStr = to_string(std::abs((int)damage));
	int damageTextSize = int(damage / 5);
	float randPosX = RandValue() * 0.6f - 0.3f;
	float randPosY = RandValue() * 0.3f - 0.15f;
	ShowText(damageStr, sf::Vector2f(position.x + randPosX, position.y - size.y * 0.5f + randPosY), damage > 0 ? Color::Red : Color::Green, 3.0f);
	health -= damage;
	float healthPercentage = HealthPercentage()*100;
	if (health <= 0) return;
	if (healthPercentage >= 75) sprite = sprite100;
	else if (healthPercentage >= 50 && sprite75) sprite = sprite75;
	else if (healthPercentage >= 25 && sprite50) sprite = sprite50;
	else if (healthPercentage >= 0 && sprite25) sprite = sprite25;
}

bool ExistsFile(const std::string& fileName)
{
	return std::filesystem::exists(fileName);
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
	const Texture& texture100 = GetTexture(AssetsPath() + "Visuals/Sprites/" +_name+ "100.png");
	sprite100 = new Sprite(texture100);
	sprite100->setPosition(position);
	sprite = sprite100;
	Vector2u textureSize = sprite->getTexture().getSize();
	Vector2f textureSizeF = { (float)textureSize.x, (float)textureSize.y };
	Vector2f origin = textureSizeF;
	origin.x *= 0.5f; // shifting position cords to the middle of the sprite X axis
	origin.y *= 0.5f; // shifting position cords to the middle of the sprite Y axis
	std::string path75 = AssetsPath() + "Visuals/Sprites/" + _name + "75.png";
	if (std::filesystem::exists(path75))
	{
		const Texture& texture75 = GetTexture(path75);
		sprite75 = new Sprite(texture75);
		sprite75->setOrigin(origin);
	}
	std::string path50 = AssetsPath() + "Visuals/Sprites/" + _name + "50.png";
	if (std::filesystem::exists(path50))
	{
		const Texture& texture50 = GetTexture(path50);
		sprite50 = new Sprite(texture50);
		sprite50->setOrigin(origin);
	}
	std::string path25 = AssetsPath() + "Visuals/Sprites/" + _name + "25.png";
	if (std::filesystem::exists(path25))
	{
		const Texture& texture25 = GetTexture(path25);
		sprite25 = new Sprite(texture25);
		sprite25->setOrigin(origin);
	}
	sprite->setOrigin(origin);
	size = { config->sizeX, config->sizeY };
}
cEntity::~cEntity()
{
	if (sprite100) delete sprite100;
	if (sprite75) delete sprite75;
	if (sprite50) delete sprite50;
	if (sprite25) delete sprite25;
	delete brain;
}

float cEntity::HealthPercentage()
{
	return health / config->maxHealth;
}

void cEntity::Quant(float _deltaTimeSec)
{
	if (health <= 0) return;
	if (brain) brain->Think();
	//if (moveDirection.x != 0 && moveDirection.y != 0) moveDirection = moveDirection.normalized();
	position += (moveDirection * maxMovementSpeed) * _deltaTimeSec;
	// process movement and jump and spells
}

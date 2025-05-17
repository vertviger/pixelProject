#include "cAction.h"
#include <map>
#include <fstream>
#include <iostream>
#include "cEntity.h"


using namespace std;
const string& AssetsPath();
float RandValue();


struct cAction::cConfig
{
	static const cConfig* Get(const std::string& name);
	bool loaded = false;
	float distance = 0.5;
	float manaRequired = 10.0;
	float damage = 10.0;
	float timeForAction = 3.0; //seconds
	string actionSprite = "";
	bool teleport = false;
};
const cAction::cConfig* cAction::cConfig::Get(const std::string& _name)
{
	static map<std::string, cAction::cConfig> configStorage;
	cAction::cConfig& config = configStorage[_name];
	if (config.loaded) return &config;
	config.loaded = true;
	std::string path = AssetsPath() + "actions/" + _name + ".txt";
	auto file = std::fstream(path);
	if (file.is_open())
	{
		auto words = std::string();
		while (getline(file, words))
		{
			stringstream s(words);
			string str;
			s >> str;
			if (str == "distance")
			{
				while (s >> str)
				{
					config.distance = std::stof(str);
				}
			}
			else if (str == "damage")
			{
				while (s >> str)
				{
					config.damage = std::stof(str);
				}
			}
			else if (str == "manaRequired")
			{
				while (s >> str)
				{
					config.manaRequired = std::stof(str);
				}
			}
			else if (str == "timeForAction")
			{
				while (s >> str)
				{
					config.timeForAction = std::stof(str);
				}
			}
			else if (str == "actionSprite")
			{
				while (s >> str)
				{
					config.actionSprite = str;
				}
			}
			else if (str == "teleport")
			{
				config.teleport = true;
			}
		}
	}
	else
	{
		std::cout << "File not found: " << path << std::endl;
	}
	return &config;
}
cAction::cAction(const string& name, cEntity* _owner) : owner(_owner)
{
	config = cConfig::Get(name);
	clockForAction.stop();
	randOffset.x = RandValue() * 2 - 1;
	randOffset.y = RandValue() * 2 - 1;
}

float Distance(const Vector2f& p1, const Vector2f& p2);
void ShowSprite(const std::string& _name, const sf::Vector2f& _pos, sf::Color _color, float _duration);

bool cAction::Teleport(Vector2f newPos)
{
	if (clockForAction.getElapsedTime().asSeconds() >= config->timeForAction)
	{
		owner->ChangePosition(newPos);
		clockForAction.restart();
		return true;
	}
	return false;
}

bool cAction::Do(cEntity* _target)
{
	if (!clockForAction.isRunning()) clockForAction.start();
	if (config->teleport)
	{
		return Teleport(_target->GetPosition());
	}
	if (_target->Health() <= 0) return true;
	Vector2f dest = _target->GetPosition() + randOffset;
	//check distance to target, if greater than distance, start Move();
	//if distance less than distance from config, change sprite to doing action,do damage to target
	float dist = Distance(owner->GetPosition(), dest);
	if (dist > config->distance)
	{
		Vector2f dir = dest - owner->GetPosition();
		dir /= dist;
		owner->SetMoveDirection(dir);
		clockForAction.restart();
	}
	else
	{
		if (owner->Name() != "player") owner->SetMoveDirection({ 0,0 });
		if (clockForAction.getElapsedTime().asSeconds() >= config->timeForAction)
		{
			if(config->actionSprite != "") ShowSprite(AssetsPath() + "Visuals/Sprites/Actions/" +config->actionSprite+ ".png", _target->GetPosition(), Color::White, 3.0f);
			_target->TakeDamage(config->damage);
			if (owner->Name() == "player")
			{
				return true;
			}
			clockForAction.restart();
		}
	}
	return false;
}

bool cAction::Can(cEntity* _target)
{
	bool isPlayer = owner->Name() == "player";
	bool isTargetTree = _target->Name() == "tree";
	bool amITarget = _target == owner;
	bool isActionHeal = config->damage < 0;
	if (isActionHeal) return isPlayer && (isTargetTree || amITarget);
	if (config->teleport) return !amITarget;
	if (!isPlayer) return true;
	return !isTargetTree && !amITarget;
}

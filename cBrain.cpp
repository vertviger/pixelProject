#include "cAction.h"
#include "cBrain.h"
#include "cScene.h"
#include <map>
#include <fstream>
#include <iostream>


struct cBrain::cConfig
{
	static const cConfig* Get(const std::string& name);
	bool loaded = false;
	std::vector<cActionType> possibleActions;
	std::vector<std::string> possibleTargets;
};
const cBrain::cConfig* cBrain::cConfig::Get(const std::string& _name)
{
	static map<std::string, cBrain::cConfig> configStorage;
	cBrain::cConfig& config = configStorage[_name];
	if (config.loaded) return &config;

	config.loaded = true;
	std::string path = "../resources/brains/" +_name+ ".txt";
	auto file = std::fstream(path);
	if (file.is_open())
	{
		auto words = std::string();
		while (getline(file, words))
		{
			stringstream s(words);
			string str;
			s >> str;
			if (str == "possibleActions")
			{
				while (s >> str)
				{
					cActionType action;
					if (str == "attack_melee")
					{
						action = A_ATTACK_MELEE;
					}
					//to_do add new actions support
					config.possibleActions.push_back(action);
				}
			}
			else if(str == "possibleTargets")
			{
				while (s >> str)
				{
					config.possibleTargets.push_back(str);
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

float Distance(const Vector2f& p1, const Vector2f& p2)
{
	return (p2 - p1).length();
}
cBrain::cBrain(cEntity* _owner, const std::string& name) : owner(_owner)
{
	config = cConfig::Get(name);
	//to do load config by name
}
void cBrain::Think()
{
	std::srand(std::time({}));
	//@to_do: take a string from allowed targets and search for it
	if (!target)
	{
		int randIndx = std::rand() / RAND_MAX * config->possibleTargets.size();
		target = FindClosestTarget(config->possibleTargets[randIndx]);
	}
	float dist = Distance(owner->GetPosition(), target->GetPosition());
	const float maxDistanceToAttack = 0.5; // to do: calc by size of the target
	if (dist > maxDistanceToAttack)
	{
		Vector2f dir = target->GetPosition() - owner->GetPosition();
		dir /= dist;
		owner->SetMoveDirection(dir);
	}
	else
	{
		owner->SetMoveDirection({0,0});
	}
}

cEntity* cBrain::FindClosestTarget(const std::string& name) const
{
	auto& myPos = owner->GetPosition();
	float distMin = 100000;
	cEntity* target = NULL;
	for (auto* i : cScene::Get()->Entities())
	{
		if (i->Name() == name)
		{
			auto& treePos = i->GetPosition();
			float dist = Distance(treePos, myPos);
			if (dist < distMin)
			{
				distMin = dist;
				target = i;
			}
		}
	}
	return target;
}



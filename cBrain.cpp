#include "cAction.h"
#include "cBrain.h"
#include "cScene.h"
#include <map>
#include <fstream>
#include <iostream>

using namespace std;

const string& AssetsPath();

struct cBrain::cConfig
{
	static const cConfig* Get(const string& name);
	bool loaded = false;
	vector<string> possibleActions;
	vector<string> possibleTargets;
};
const cBrain::cConfig* cBrain::cConfig::Get(const string& _name)
{
	static map<string, cBrain::cConfig> configStorage;
	cBrain::cConfig& config = configStorage[_name];
	if (config.loaded) return &config;

	config.loaded = true;
	string path = AssetsPath() + "brains/" +_name+ ".txt";
	auto file = fstream(path);
	if (file.is_open())
	{
		auto words = string();
		while (getline(file, words))
		{
			stringstream s(words);
			string str;
			s >> str;
			if (str == "possibleActions")
			{
				while (s >> str) config.possibleActions.push_back(str);
			}
			else if(str == "possibleTargets")
			{
				while (s >> str) config.possibleTargets.push_back(str);
			}
		}
	}
	else
	{
		std::cout << "File not found: " << path << std::endl;
	}
	return &config;
}


cBrain::cBrain(cEntity* _owner, const std::string& name) : owner(_owner)
{
	config = cConfig::Get(name);
	//to do load config by name
}
cBrain::~cBrain()
{
	if (action) delete action;
}
void cBrain::Think()
{
	std::srand(std::time({}));
	//@to_do: take a string from allowed targets and search for it
	if (!target)
	{
		int randIndx = std::rand() / RAND_MAX * config->possibleTargets.size();
		target = FindClosestTarget(config->possibleTargets[randIndx]);
		if (!target) return;
	}
	if (!action)
	{
		int randIndx = std::rand() / RAND_MAX * config->possibleActions.size();
		action = new cAction(config->possibleActions[randIndx], owner);
	}
	if (action->Do(target)) //Do returns true when action is finished
	{
		target = NULL;
		delete action;
		action = NULL;
	}
	
}
float Distance(const Vector2f& p1, const Vector2f& p2)
{
	return (p2 - p1).length();
}
cEntity* cBrain::FindClosestTarget(const std::string& name) const
{
	auto& myPos = owner->GetPosition();
	float distMin = 100000;
	cEntity* target = NULL;
	for (auto* i : cScene::Get()->Entities())
	{
		if (i->Name() == name && i->Health() > 0)
		{
			auto& targetPos = i->GetPosition();
			float dist = Distance(targetPos, myPos);
			if (dist < distMin)
			{
				distMin = dist;
				target = i;
			}
		}
	}
	return target;
}



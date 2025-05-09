#include "cAction.h"
#include <set>

#pragma once

class cEntity;

class cBrain
{
public:
	cBrain(cEntity* _owner, const std::string& name);
	virtual void Think();
protected:
	cEntity* FindClosestTarget(const std::string& target) const;
	std::vector<cActionType> possibleActions;
	std::vector<std::string> possibleTargets;
	cEntity* owner = NULL;
	cEntity* target = NULL;
};



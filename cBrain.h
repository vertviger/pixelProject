#include "cAction.h"
#include <set>

#pragma once

class cEntity;

class cBrain
{
public:
	cBrain(cEntity* _owner, const std::string& name);
	~cBrain();
	virtual void Think();
protected:
	struct cConfig;
	cEntity* FindClosestTarget(const std::string& target) const;
	cEntity* owner = NULL;
	cEntity* target = NULL;
	const cConfig* config;
	cAction* action = NULL;
};



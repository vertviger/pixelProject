#include "cAction.h"
#include <set>

#pragma once

class cEntity;

class cBrain
{
public:
	cBrain(cEntity* _owner) : owner(_owner) {}

	void AllowAction(cActionType a) { allowedActions.insert(a); }
	void Think();

private:
	std::set<cActionType> allowedActions;
	cEntity* owner = NULL;
};
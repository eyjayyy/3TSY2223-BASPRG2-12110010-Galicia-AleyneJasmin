#pragma once
#include "Action.h"

class Heal : public Action
{
public:
	Heal(string actionName, string actionType, int mpCost, float damageCoefficient);
	Unit* getWeakestAlly(vector<Unit*> team);
	void act(Unit* attacker, vector<Unit*> targetTeam) override;
};


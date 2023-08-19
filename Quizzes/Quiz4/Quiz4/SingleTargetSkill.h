#pragma once
#include "Action.h"

class SingleTargetSkill : public Action
{
public:
	SingleTargetSkill(string actionName, string actionType, int mpCost, float damageCoefficient);
	Unit* getWeakestEnemy(vector<Unit*> targetTeam);
	void act(Unit* attacker, vector<Unit*> targetTeam) override;
};


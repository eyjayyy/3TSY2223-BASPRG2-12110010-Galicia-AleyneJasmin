#pragma once
#include "Action.h"

class MultiTargetSkill : public Action
{
public:
	MultiTargetSkill(string actionName, string actionType, int mpCost, float damageCoefficient);
	void act(Unit* attacker, vector<Unit*> targetTeam) override;
};


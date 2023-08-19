#pragma once
#include "Action.h"

class BasicAttack : public Action
{
public:
	BasicAttack(string actionName, string actionType, int mpCost, float damageCoefficient);
	bool checkIfHit(Unit* attacker, Unit* target);
	void act(Unit* attacker, vector<Unit*> targetTeam) override;

private:
	float mCritDmg;
};
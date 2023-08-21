#pragma once
#include <iostream>
#include <time.h>
#include "Unit.h"

using namespace std;

class Unit;
class Action
{
public:
	Action(string actionName, string actionType, int mpCost, float damageCoefficient);

	// getters
	string getActionName();
	string getActionType();
	int getMpCost();

	// other functions
	int calculateDamage(Unit* attacker, Unit* target);
	virtual void act(Unit* attacker, vector<Unit*> targetTeam);

private:
	string mActionName;
	string mActionType;
	int mMpCost;
	float mDamageCoefficient;
};
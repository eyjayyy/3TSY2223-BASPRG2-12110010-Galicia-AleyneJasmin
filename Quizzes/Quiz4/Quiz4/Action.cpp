#include "Action.h"

Action::Action(string actionName, string actionType, int mpCost, float damageCoefficient)
{
	mActionName = actionName;
	mActionType = actionType;
	mMpCost = mpCost;
	mDamageCoefficient = damageCoefficient;
}

// getters
string Action::getActionName()
{
	return mActionName;
}

string Action::getActionType()
{
	return mActionType;
}

int Action::getMpCost()
{
	return mMpCost;
}

// other functions
int Action::calculateDamage(Unit* attacker, Unit* target)
{
	int varPow = round((attacker->getPow() * 0.2));
	int randPow = rand() % varPow + attacker->getPow();
	int baseDmg = round(randPow * mDamageCoefficient);
	int damage = baseDmg - target->getVit();

	if (damage <= 0)
	{
		damage = 1;
	}

	return damage;
}

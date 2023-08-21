#include "Heal.h"

Heal::Heal(string actionName, string actionType, int mpCost, float damageCoefficient)
	:Action(actionName, actionType, mpCost, damageCoefficient)
{

}

Unit* Heal::getWeakestAlly(vector<Unit*> team)
{
	Unit* weakestAlly = team[0];

	for (int i = 1; i < team.size(); i++)
	{
		if (team[i]->getCurrentHp() < weakestAlly->getCurrentHp())
		{
			weakestAlly = team[i];
		}
	}

	return weakestAlly;
}

void Heal::act(Unit* attacker, vector<Unit*> targetTeam)
{
	Unit* target = getWeakestAlly(targetTeam);

	// deduct mp
	attacker->setCurrentMp(attacker->getCurrentMp() - getMpCost());

	// heal weakest ally
	int healVal = round(0.3 * target->getMaxHp());
	target->setCurrentHp(target->getMaxHp() + healVal);

	cout << attacker->getName() << " used " << getActionName() << " on " << target->getName() << ".\n"
		<< target->getName() << " was healed for " << healVal << " HP.\n" << endl;
}
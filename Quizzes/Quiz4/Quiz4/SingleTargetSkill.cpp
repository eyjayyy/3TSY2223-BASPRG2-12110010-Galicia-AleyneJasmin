#include "SingleTargetSkill.h"

SingleTargetSkill::SingleTargetSkill(string actionName, string actionType, int mpCost, float damageCoefficient)
	:Action(actionName, actionType, mpCost, damageCoefficient)
{

}

Unit* SingleTargetSkill::getWeakestEnemy(vector<Unit*> targetTeam)
{
	Unit* weakestEnemy = targetTeam[0];

	for (int i = 1; i < targetTeam.size(); i++)
	{
		if (targetTeam[i]->getCurrentHp() < weakestEnemy->getCurrentHp())
		{
			weakestEnemy = targetTeam[i];
		}
	}

	return weakestEnemy;
}

void SingleTargetSkill::act(Unit* attacker, vector<Unit*> targetTeam)
{
	Unit* target = getWeakestEnemy(targetTeam);

	// deduct mp
	attacker->setCurrentMp(attacker->getCurrentMp() - getMpCost());

	// deal damage to weakest enemy
	int dmg = calculateDamage(attacker, target);
	target->setCurrentHp(target->getCurrentHp() - dmg);

	cout << attacker->getName() << " used " << getActionName() << " against " << target->getName() << ".\n"
		<< getActionName() << " dealt " << dmg << " damage.\n" << endl;

	if (target->getCurrentHp() <= 0)
	{
		cout << target->getName() << " died.\n" << endl;
	}
}
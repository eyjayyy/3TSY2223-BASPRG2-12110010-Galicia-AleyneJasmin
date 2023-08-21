#include "BasicAttack.h"

BasicAttack::BasicAttack(string actionName, string actionType, int mpCost, float damageCoefficient)
	:Action(actionName, actionType, mpCost, damageCoefficient)
{
	mCritDmg = 1.2;
}

bool BasicAttack::checkIfHit(Unit* attacker, Unit* target)
{
	int hitRate = round(attacker->getDex() / target->getAgi() * 100);

	// clamp hitrate
	if (hitRate < 20)
	{
		hitRate = 20;
	}

	else if (hitRate > 80)
	{
		hitRate = 80;
	}

	// check if target is hit
	int hitChance = rand() % 100;

	if (hitChance > hitRate)
	{
		return false;
	}

	else
	{
		return true;
	}
}

void BasicAttack::act(Unit* attacker, vector<Unit*> targetTeam)
{
	int randTarget = rand() % targetTeam.size();

	// attack misses
	if (!checkIfHit(attacker, targetTeam[randTarget]))
	{
		cout << attacker->getName() << " used Basic Attack but missed!\n" << endl;
		return;
	}

	// attack lands
	int dmg = calculateDamage(attacker, targetTeam[randTarget]);

	// check for crit
	int critChance = rand() % 100;

	if (critChance < 20)
	{
		dmg *= mCritDmg;
		cout << "Crit! ";
	}

	targetTeam[randTarget]->setCurrentHp(targetTeam[randTarget]->getCurrentHp() - dmg);
	cout << attacker->getName() << " used " << getActionName() << " against " << targetTeam[randTarget]->getName() << ".\n"
		<< getActionName() << " dealt " << dmg << " damage.\n" << endl;

	if (targetTeam[randTarget]->getCurrentHp() <= 0)
	{
		cout << targetTeam[randTarget]->getName() << " died.\n" << endl;
	}
}

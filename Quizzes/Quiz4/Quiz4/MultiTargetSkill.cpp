#include "MultiTargetSkill.h"

MultiTargetSkill::MultiTargetSkill(string actionName, string actionType, int mpCost, float damageCoefficient)
	:Action(actionName, actionType, mpCost, damageCoefficient)
{

}

void MultiTargetSkill::act(Unit* attacker, vector<Unit*> targetTeam)
{
	// deduct mp
	attacker->setCurrentMp(attacker->getCurrentMp() - getMpCost());

	// deal damage to all
	cout << attacker->getName() << " is casting " << getActionName() << " against all his/her opponents." << endl;

	for (int i = 0; i < targetTeam.size(); i++)
	{
		int dmg = calculateDamage(attacker, targetTeam[i]);
		targetTeam[i]->setCurrentHp(targetTeam[i]->getCurrentHp() - dmg);
		cout << getActionName() << " dealt " << dmg << " damage against " << targetTeam[i]->getName() << endl;

		if (targetTeam[i]->getCurrentHp() <= 0)
		{
			cout << targetTeam[i]->getName() << " died" << endl;
		}
	}

	cout << endl;
}
#include "Spell.h"

void Spell::activate(Wizard* _caster, Wizard* _target)
{
	if (_caster->mMp >= 50)
	{
		int mDmg = (rand() % ((mMaxDmg - mMinDmg) + 1) + mMinDmg);
		_target->mHp -= mDmg;
		cout << _caster->mName << " casted " << this->mName << ", dealing " << mDmg << " damage to " << _target->mName << "!" << endl;

		_caster->mMp -= mMPCost;
		cout << _caster->mName << " consumed " << mMPCost << " MP!\n\n" << endl;
	}
}

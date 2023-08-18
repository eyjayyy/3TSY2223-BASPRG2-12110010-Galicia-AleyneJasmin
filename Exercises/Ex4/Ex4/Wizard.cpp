#include "Wizard.h"

void Wizard::attack(Wizard* _target)
{
	int mDmg = (rand() % ((mMaxDmg - mMinDmg) + 1) + mMinDmg);
	_target->mHp -= mDmg;
	cout << mName << " dealt " << mDmg << " damage to " << _target->mName << "!" << endl;

	int mMpRec = (rand() % 11) + 10;
	mMp += mMpRec;
	cout << "After attacking, " << mName << " gained " << mMpRec << " MP!\n\n" << endl;
}
#pragma once
#include <iostream>
#include <string>
#include "Wizard.h"

using namespace std;

class Spell
{
public:
	string mName;
	int mMaxDmg;
	int mMinDmg;
	int mMPCost;

	Spell(string _name, int _maxDmg, int _minDmg, int _mpCost)
	{
		mName = _name;
		mMaxDmg = _maxDmg;
		mMinDmg = _minDmg;
		mMPCost = _mpCost;
	}

	void activate(Wizard* _caster, Wizard* _target);
};


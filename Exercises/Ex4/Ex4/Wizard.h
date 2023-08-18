#pragma once
#include <iostream>
#include <string>
using namespace std;

class Wizard
{
public:
	string mName;
	int mHp;
	int mMp;
	int mMinDmg;
	int mMaxDmg;

	Wizard(string _name, int _hp, int _mp, int _minDmg, int _maxDmg)
	{
		mName = _name;
		mHp = _hp;
		mMp = _mp;
		mMinDmg = _minDmg;
		mMaxDmg = _maxDmg;
	}

	void attack(Wizard* _target);
};


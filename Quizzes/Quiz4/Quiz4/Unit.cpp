#include "Unit.h"

Unit::Unit(string name, string team)
{
	mName = name;
	mTeam = team;

	mMaxHp = rand() % 26 + 20;
	mCurrentHp = mMaxHp;
	mMaxMp = rand() % 11 + 10;
	mCurrentMp = mMaxMp;
	mPow = rand() % 6 + 10;
	mVit = rand() % 6 + 1;
	mAgi = rand() % 6 + 1;
	mDex = rand() % 6 + 10;
}

// getters
string Unit::getName()
{
	return mName;
}

string Unit::getTeam()
{
	return mTeam;
}

int Unit::getCurrentHp()
{

	return mCurrentHp;
}

int Unit::getCurrentMp()
{
	return mCurrentMp;
}

int Unit::getPow()
{
	return mPow;
}

int Unit::getVit()
{
	return mVit;
}

int Unit::getAgi()
{
	return mAgi;
}


int Unit::getDex()
{
	return mDex;
}

vector<Action*> Unit::getActions()
{
	return mActions;
}

// setters
void Unit::setCurrentHp(int hp)
{
	mCurrentHp = hp;

	if (mCurrentHp < 0)
	{
		mCurrentHp = 0;
	}

	else if (mCurrentHp > mMaxHp)
	{
		mCurrentHp = mMaxHp;
	}
}

void Unit::setCurrentMp(int mp)
{
	mCurrentMp = mp;
}

void Unit::setActions(Action* action)
{
	mActions.push_back(action);
}

// other functions
void Unit::displayStats()
{
	cout << "Name: " << mName
		<< "\nHP: " << mCurrentHp << "/" << mMaxHp
		<< "\nMP: " << mCurrentMp << "/" << mMaxMp
		<< "\nPow: " << mPow
		<< "\nVit: " << mVit
		<< "\nDex: " << mDex
		<< "\nAgi: " << mAgi
		<< "\n" << endl;
}

Unit::~Unit()
{
	for (int i = 0; i < mActions.size(); i++)
	{
		delete mActions[i];
	}

	mActions.clear();
}
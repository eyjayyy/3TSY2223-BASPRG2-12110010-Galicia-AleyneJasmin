#include "Unit.h"

using namespace std;

// getters
string Unit::getName()
{
	return mName;
}

string Unit::getClass()
{
	return mClass;
}

int Unit::getCurrentHp()
{
	return mCurrentHp;
}

int Unit::getPow()
{
	return mPow;
}

int Unit::getVit()
{
	return mVit;
}

int Unit::getDex()
{
	return mDex;
}

int Unit::getAgi()
{
	return mAgi;
}

// setters
void Unit::setName(string name)
{
	this->mName = name;
}

void Unit::setPlayerClass(int choice)
{
	switch (choice)
	{
		case 1:
			this->mClass = "Warrior";
			break;

		case 2:
			this->mClass = "Assassin";
			break;

		case 3:
			this->mClass = "Mage";
			break;
	}
}

void Unit::setPlayerStats()
{
	this->mMaxHp = rand() % 11 + 20;
	this->mCurrentHp = mMaxHp;
	this->mPow = rand() % 10 + 1;
	this->mVit = rand() % 3 + 1;
	this->mAgi = rand() % 10 + 1;
	this->mDex = rand() % 10 + 1;
}

void Unit::setEnemyClass()
{
	int classRand = rand() % 3;

	switch (classRand)
	{
		case 0:
			this->mClass = "Warrior";
			break;

		case 1:
			this->mClass = "Assassin";
			break;

		case 2:
			this->mClass = "Mage";
			break;
	}
}

void Unit::setEnemyStats(int stage)
{
	int difficultyIncrease = 0;

	if (stage != 1)
	{
		difficultyIncrease = stage * 2;
	}

	this->mName = "Enemy";
	this->mMaxHp = (rand() % 5 + 5) + difficultyIncrease;
	this->mCurrentHp = mMaxHp;
	this->mPow = (rand() % 3 + 3) + difficultyIncrease;
	this->mVit = (rand() % 3 + 1) + difficultyIncrease;
	this->mAgi = (rand() % 4 + 1) + difficultyIncrease;
	this->mDex = (rand() % 4 + 1) + difficultyIncrease;
}

// other functions
void Unit::displayStats(Unit* unit)
{
	cout << "Name: " << unit->mName
		<< "\nClass: " << unit->mClass
		<< "\nHP: " << unit->mCurrentHp << "/" << unit->mMaxHp
		<< "\nPow: " << unit->mPow
		<< "\nVit: " << unit->mVit
		<< "\nDex: " << unit->mDex
		<< "\nAgi: " << unit->mAgi 
		<< endl;
}

bool Unit::calculateHitRate(Unit* target)
{
	int hitRate = round((mDex / target->getAgi()) * 100);

	// clamp hit rate
	if (hitRate > 80)
	{
		hitRate = 80;
	}

	else if (hitRate < 20)
	{
		hitRate = 20;
	}

	int eHitChance = round(100 / hitRate);
	int hitChance = rand () % eHitChance + 1;

	// check if will land
	if (hitChance == 1)
	{
		return true;
	}

	else
	{
		return false;
	}
}

int Unit::calculateBonusDamage(Unit* target)
{
	float multiplier = 0;

	if (mClass == "Warrior")
	{		
		if (target->mClass == "Assassin")
		{
			multiplier = 1.5;
		}

		else
		{
			multiplier = 1;
		}
	}

	else if (mClass == "Assassin")
	{
		if (target->mClass == "Mage")
		{
			multiplier = 1.5;
		}

		else
		{
			multiplier = 1;
		}
	}

	else if (mClass == "Mage")
	{
		if (target->mClass == "Warrior")
		{
			multiplier = 1.5;
		}
		else
		{
			multiplier = 1;
		}
	}

	return multiplier;
}

void Unit::attack(Unit* target)
{
	int bonusDmg = calculateBonusDamage(target);
	int atkDmg = round((mPow - target->getVit()) * bonusDmg);

	if (atkDmg < 1)
	{
		atkDmg = 1;
	}

	target->takeDamage(atkDmg);
	cout << mName << " dealt " << atkDmg << " damage to " << target->getName() << "!" << endl;
}

void Unit::takeDamage(int damage)
{
	mCurrentHp -= damage;

	if (mCurrentHp < 0)
	{
		mCurrentHp = 0;
	}
}

// player only functions
void Unit::increasePlayerStats(Unit* enemy)
{
	cout << "[STAGE END]\n"
		<< "Increased stats by:"
		<< endl;

	if (enemy->getClass() == "Warrior")
	{
		mPow += 3;
		mVit += 3;
		cout << "Hp: 0\n" 
			<< "Pow: 3\n"
			<< "Vit: 3\n" 
			<< "Dex: 0\n" 
			"Agi: 0" 
			<< endl;
	}

	else if (enemy->getClass() == "Assassin")
	{
		mAgi += 3;
		mDex += 3;
		cout << "Hp: 0\n"
			<< "Pow: 0\n"
			<< "Vit: 0\n"
			<< "Dex: 3\n"
			"Agi: 3"
			<< endl;
	}

	else if (enemy->getClass() == "Mage")
	{
		mPow += 3;
		cout << "Hp: 0\n"
			<< "Pow: 3\n"
			<< "Vit: 0\n"
			<< "Dex: 0\n"
			"Agi: 0"
			<< endl;
	}
}

void Unit::heal()
{
	int healVal = mMaxHp * 0.3;
	mCurrentHp += healVal;

	if (mCurrentHp > mMaxHp)
	{
		mCurrentHp = mMaxHp;
	}

	cout << "\nYou are healed for " << healVal << "HP\n" << endl;
}

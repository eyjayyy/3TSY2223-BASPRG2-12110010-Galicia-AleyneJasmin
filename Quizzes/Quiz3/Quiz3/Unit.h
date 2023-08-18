#pragma once
#include <iostream>
#include <string>

using namespace std;

class Unit
{
public:
	// getters
	string getName();
	string getClass();
	int getCurrentHp();
	int getPow();
	int getVit();
	int getDex();
	int getAgi();

	// setters
	void setName(string name);
	void setPlayerClass(int choice);
	void setPlayerStats();
	void setEnemyClass();
	void setEnemyStats(int stage);

	// other functions
	void displayStats(Unit* unit);
	bool calculateHitRate(Unit* target);
	int calculateBonusDamage(Unit* target);
	void attack(Unit* target);
	void takeDamage(int damage);

	// player only
	void increasePlayerStats(Unit* enemy);
	void heal();

private:
	string mName;
	string mClass;
	int mMaxHp;
	int mCurrentHp;
	int mPow;
	int mVit;
	int mAgi;
	int mDex;
};


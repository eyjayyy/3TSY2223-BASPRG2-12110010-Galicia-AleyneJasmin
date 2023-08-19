#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Action.h"

using namespace std;

class Unit
{
public:
	Unit(string name, string team);

	// getters
	string getName();
	string getTeam();
	int getCurrentHp();
	int getCurrentMp();
	int getPow();
	int getVit();
	int getDex();
	int getAgi();
	vector<Action*> getActions();

	// setters
	void setCurrentHp(int hp);
	void setCurrentMp(int mp);
	void setActions(Action* action);

	// other functions
	void displayStats();

	~Unit();

private:
	string mName;
	string mTeam;
	int mMaxHp;
	int mCurrentHp;
	int mMaxMp;
	int mCurrentMp;
	int mPow;
	int mVit;
	int mAgi;
	int mDex;
	vector<Action*> mActions;
};
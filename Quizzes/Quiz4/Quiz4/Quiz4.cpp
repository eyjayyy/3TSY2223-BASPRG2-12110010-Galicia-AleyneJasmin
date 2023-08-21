#include <iostream>
#include <string>
#include<vector>
#include <time.h>
#include "Unit.h"
#include "Action.h"
#include "BasicAttack.h"
#include "SingleTargetSkill.h"
#include "MultiTargetSkill.h"
#include "Heal.h"

using namespace std;

void createCharacter(string name, string teamName, Action* action1, Action* action2, vector<Unit*> &team, vector<Unit*> &turnOrder)
{
    Unit* character = new Unit(name, teamName);
    character->setActions(action1);
    character->setActions(action2);
    team.push_back(character);
    turnOrder.push_back(character);
}

vector<Unit*> sortTurnOrder(vector<Unit*> initialTurnOrder)
{
    vector<Unit*> sortedTurnOrder;

	while (initialTurnOrder.size() != 0)
	{
		Unit* fastestChara = initialTurnOrder[0];

		// find current fastest in initial list
		for (int i = 1; i < initialTurnOrder.size(); i++)
		{
			if (initialTurnOrder[i]->getAgi() >= fastestChara->getAgi())
			{
				fastestChara = initialTurnOrder[i];
			}
		}

		sortedTurnOrder.push_back(fastestChara);

		// removes current fastest in initial list
		for (int i = 0; i < initialTurnOrder.size(); i++)
		{
			if (initialTurnOrder[i] == fastestChara)
			{
				initialTurnOrder.erase(initialTurnOrder.begin() + i);
				break;
			}
		}
	}

	return sortedTurnOrder;
}

void displayTeam(vector<Unit*> team)
{
	cout << "==================================\n"
		<< "Team: " << team[0]->getTeam() 
		<< "\n=================================="
		<< endl;

	for (int i = 0; i < team.size(); i++)
	{
		cout << team[i]->getName() << " [HP: " << team[i]->getCurrentHp() << "]" << endl;
	}

	cout << endl;
}

void displayTurnOrder(vector<Unit*> finalTurnOrder)
{
	cout << "=========== TURN ORDER ===========" << endl;

	for (int i = 0; i < finalTurnOrder.size(); i++)
	{
		cout << "#" << i + 1 << " [" << finalTurnOrder[i]->getTeam() << "] " << finalTurnOrder[i]->getName() << endl;
	}
}

bool isTeamAlive(vector<Unit*> team)
{
	for (int i = 0; i < team.size(); i++)
	{
		// atleast one is alive
		if (team[i]->getCurrentHp() > 0)
		{
			return true;
		}
	}

	// none is alive
	return false;
}

void playPlayerTurn(Unit* player, vector<Unit*> playerTeam, vector<Unit*> targetTeam)
{
	int choice;
	player->displayStats();

	cout << "Choose an action...\n"
		<< "===============================\n"
		<< "[1] " << player->getActions()[0]->getActionName()
		<< "\n[2] " << player->getActions()[1]->getActionName()
		<< "\nDo: ";
	cin >> choice;

	// handles invalid inputs
	while (choice <= 0 || choice > player->getActions().size() || player->getCurrentMp() < player->getActions()[1]->getMpCost())
	{
		if (choice <= 0 || choice > player->getActions().size())
		{
			cout << "Please choose from the actions above.\n"
				<< "Do: ";
			cin >> choice;
		}

		if (player->getCurrentMp() < player->getActions()[1]->getMpCost())
		{
			cout << "Not enough MP for this action.\n"
				<< "Do: ";
			cin >> choice;
		}
	}

	system("cls");

	// if skill is a heal
	if (player->getActions()[choice - 1]->getActionType() == "Heal")
	{
		player->getActions()[choice - 1]->act(player, playerTeam);
	}

	// if skill is an attack
	else
	{
		player->getActions()[choice - 1]->act(player, targetTeam);
	}
}

void playEnemyTurn(Unit* enemy, vector<Unit*> enemyTeam, vector<Unit*> targetTeam)
{
	int mpSkillChance = rand() % 2;

	// use mp skill
	if (mpSkillChance == 1 && enemy->getCurrentMp() >= enemy->getActions()[1]->getMpCost())
	{
		// if skill is a heal
		if (enemy->getActions()[1]->getActionType() == "Heal")
		{
			enemy->getActions()[1]->act(enemy, enemyTeam);
		}

		// if skill is an attack
		else
		{
			enemy->getActions()[1]->act(enemy, targetTeam);
		}
	}

	else
	{
		enemy->getActions()[0]->act(enemy, targetTeam);
	}
}

void removeDeadChara(vector<Unit*> &team, vector<Unit*> &turnOrder)
{
	for (int i = 0; i < team.size(); i++)
	{
		if (team[i]->getCurrentHp() <= 0)
		{
			team.erase(team.begin() + i);
		}
	}

	for (int i = 0; i < turnOrder.size(); i++)
	{
		if (turnOrder[i]->getCurrentHp() <= 0)
		{
			turnOrder.erase(turnOrder.begin() + i);
		}
	}
}

void destroyLists(vector<Unit*> list)
{
	for (int i = 0; i < list.size(); i++)
	{
		delete list[i];
	}

	list.clear();
}

int main()
{
	srand(time(0));
	vector<Unit*> playerTeam;
	vector<Unit*> enemyTeam;
	int turn = 0;

	// create all skills
	BasicAttack* basicAttack = new BasicAttack("Basic Attack", "BasicAttack", 0, 1.0f);
	
	SingleTargetSkill* theHunt = new SingleTargetSkill("The Hunt", "SingleTarget", 5, 2.2f);
	SingleTargetSkill* puncturingArrow = new SingleTargetSkill("Puncturing Arrow", "SingleTarget", 5, 2.2f);

	MultiTargetSkill* faceMelt = new MultiTargetSkill("Face Melt", "MultiTarget", 4, 0.9f);
	
	Heal* jugOfLife = new Heal("Jug of Life", "Heal", 3, 0);
	Heal* divinePalm = new Heal("Divine Palm", "Heal", 3, 0);

	// create all characters
	vector<Unit*> turnOrder;

	createCharacter("E.T.C", "Warcraft", basicAttack, faceMelt, playerTeam, turnOrder);
	createCharacter("Illidan", "Warcraft", basicAttack, theHunt, playerTeam, turnOrder);
	createCharacter("Lili", "Warcraft", basicAttack, jugOfLife, playerTeam, turnOrder);

	createCharacter("Johanna","Diablo", basicAttack, faceMelt, enemyTeam, turnOrder);
	createCharacter("Valla","Diablo", basicAttack, puncturingArrow, enemyTeam, turnOrder);
	createCharacter("Kharazim","Diablo", basicAttack, divinePalm, enemyTeam, turnOrder);

	// sort turn order
	turnOrder = sortTurnOrder(turnOrder);

	while (isTeamAlive(playerTeam) && isTeamAlive(enemyTeam))
	{
		if (turnOrder[turn]->getCurrentHp() <= 0)
		{
			turn++;
		}

		// teams information
		displayTeam(playerTeam);
		displayTeam(enemyTeam);
		displayTurnOrder(turnOrder);
		cout << "=========== TURN ORDER ===========\n\n"
			<< "Current Turn: [" << turnOrder[turn]->getTeam() << "] " << turnOrder[turn]->getName() << "\n"
			<< endl;

		system("pause");
		system("cls");

		// combat loop
		// player turn
		if (turnOrder[turn]->getTeam() == "Warcraft")
		{
			playPlayerTurn(turnOrder[turn], playerTeam, enemyTeam);
		}

		// enemy turn
		else if (turnOrder[turn]->getTeam() == "Diablo")
		{
			playEnemyTurn(turnOrder[turn], enemyTeam, playerTeam);
		}

		system("pause");
		system("cls");

		removeDeadChara(playerTeam, turnOrder);
		removeDeadChara(enemyTeam, turnOrder);

		turn++;

		if (turn == turnOrder.size())
		{
			turn = 0;
		}
	}

	// one team is already dead so proceed to ending
	if (isTeamAlive(playerTeam))
	{
		cout << "Warcraft wins!\n" << endl;
		displayTeam(playerTeam);
	}

	if (isTeamAlive(enemyTeam))
	{
		cout << "Diablo wins!\n" << endl;
		displayTeam(enemyTeam);
	}

	// destroy stuff
	destroyLists(turnOrder);
	destroyLists(playerTeam);
	destroyLists(enemyTeam);

	system("pause");
	return 0;
}
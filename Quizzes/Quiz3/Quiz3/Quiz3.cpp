#include <iostream>
#include <string>
#include <time.h>
#include "Unit.h"

using namespace std;

Unit* createCharacter()
{
	string name;
	int choice;
	Unit* newPlayer = new Unit();

	cout << "Input a name for your character: ";
	cin >> name;
	newPlayer->setName(name);

	cout << "\nChoose your class:\n" 
		<< "[1] Warrior\n" 
		<< "[2] Assassin\n"
		<< "[3] Mage\n" 
		<< "Choice: ";
	cin >> choice;

	while (choice != 1 && choice != 2 && choice != 3)
	{
		cout << "Invalid choice. Please pick from the above: ";
		cin >> choice;
	}

	newPlayer->setPlayerClass(choice);
	newPlayer->setPlayerStats();

	return newPlayer;
}

Unit* spawnEnemy(int stage)
{
	Unit* newEnemy = new Unit();
	newEnemy->setEnemyClass();
	newEnemy->setEnemyStats(stage);

	return newEnemy;
}

void playTurn(Unit* attacker, Unit* target)
{
	if (attacker->calculateHitRate(target))
	{
		attacker->attack(target);
	}

	else
	{
		cout << attacker->getName() << " missed!" << endl;
	}
}

void playStage(Unit* player, Unit* enemy)
{
	while (player->getCurrentHp() > 0 || enemy->getCurrentHp() > 0)
	{
		if (player->getAgi() > enemy->getAgi())
		{
			playTurn(player, enemy);

			if (enemy->getCurrentHp() == 0)
			{
				cout << "\n" << enemy->getName() << " died!" << endl;
				break;
			}

			system("pause");

			cout << endl;
			playTurn(enemy, player);

			if (player->getCurrentHp() == 0)
			{
				cout << "\n" << player->getName() << " died!" << endl;
				break;
			}

			system("pause");
			cout << endl;
		}

		else if (player->getAgi() < enemy->getAgi())
		{
			playTurn(enemy, player);

			if (player->getCurrentHp() == 0)
			{
				cout << "\n" << player->getName() << " died!" << endl;
				break;
			}

			system("pause");

			cout << endl;
			playTurn(player, enemy);

			if (enemy->getCurrentHp() == 0)
			{
				cout << "\n" << enemy->getName() << " died!" << endl;
				break;
			}

			system("pause");
			cout << endl;
		}
	}

	system("pause");
}

int main()
{
	srand(time(0));
	int stage = 1;

	Unit* player = createCharacter();
	system("cls");

	while (player->getCurrentHp() > 0)
	{
		// Stage start
		system("cls");
		Unit* enemy = spawnEnemy(stage);

		cout << "[STAGE " << stage << "]" << endl;
		player->displayStats(player);
		cout << "\nVS\n" << endl;
		enemy->displayStats(enemy);
		cout << "\n\nInitiating combat...\n" << endl;

		system("pause");
		system("cls");

		// Combat loop
		cout << "[COMBAT START]" << endl;
		playStage(player, enemy);

		// player wins stage
		if (player->getCurrentHp() > 0)
		{
			system("cls");
			player->increasePlayerStats(enemy);
			player->heal();
			system("pause");

			delete enemy;
			stage++;
		}

		else
		{
			delete enemy;
			break;
		}
	}

	// player loses; end game
	system("cls");
	cout << "[END]\n"
		<< "Round reached: " << stage 
		<< "\n\n[Player's Stats:]" << endl;
	player->displayStats(player);
	cout << endl;

	delete player;
	system("pause");
	return 0;
}
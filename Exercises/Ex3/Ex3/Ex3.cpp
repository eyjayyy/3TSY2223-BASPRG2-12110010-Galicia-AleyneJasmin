#include <iostream>
#include <time.h>
#include <string>
#include <vector>

using namespace std;

struct Item
{
    string name;
    int gold;
};

Item* loot1 = new Item{ "Mithril Ore", 100 };
Item* loot2 = new Item{ "Sharp Talon", 50 };
Item* loot3 = new Item{ "Thick Leather", 25 };
Item* loot4 = new Item{ "Jellopy", 5 };
Item* loot5 = new Item{ "Cursed Stone", 0 };

Item* generateRandomItem()
{
    int randIndex = rand() % 5;
    Item* randomItem = new Item;

    switch (randIndex)
    {
        case 0:
            randomItem = loot1;        
            break;

        case 1:
            randomItem = loot2;
            break;

        case 2:
            randomItem = loot3;
            break;

        case 3:
            randomItem = loot4;
            break;

        case 4:
            randomItem = loot5;
            break;

    }

    return randomItem;
}

void calculateGold(vector<Item*> &inventory, int &playerGold, int multiplier)
{
    int goldLooted = 0;

    for (int i = 0; i < inventory.size(); i++)
    {
        goldLooted += (inventory[i]->gold * multiplier);
    }

    playerGold += goldLooted;

    cout << "\n[Dungeon Stats]" << endl;
    cout << "Looted " << inventory.size() << " times" << endl;
    cout << "Gold Multiplier: " << multiplier << "x" << endl;
    cout << "Gold Looted: " << goldLooted << endl;
    cout << "Total Gold: " << playerGold << "\n" << endl;

    system("pause");
    system("cls");
}

void evaluateEnding(int playerGold)
{
    if (playerGold >= 500)
    {
        cout << "Congratulations, adventurer! The target of 500 gold has been satisfied. \nMay you spend that money wisely.\n[Win Ending]\n" << endl;
    }

    else
    {
        cout << "It seems like you're coming out unsatisfied. \nWelp, not my fault that your pockets are quite airy. May you plan better next time.\n[Lose Ending]\n" << endl;
    }
}

void enterDungeon(int &playerGold, vector<Item*> &inventory, int &multiplier)
{
    char choice = ' ';
    Item* loot = new Item;
    multiplier = 1;

    playerGold -= 25;
    cout << "=== [Paid 25 Gold to Enter the Dungeon] ===" << endl;
    cout << "Current Gold: " << playerGold << endl;

    while (loot != loot5 && choice != 'N')
    {    
        loot = generateRandomItem();
        inventory.push_back(loot);
        cout << "\nAquired " << loot->name << "!\n" << endl;

        if (loot != loot5)
        {
            cout << "Continue Looting?" << endl;
            cout << "[Y] Yes \n[N] No" << endl;
            cout << "Choice: ";
            cin >> choice;

            while (choice != 'Y' && choice != 'N')
            {
                cout << "Invalid answer. Please choose either [Y] ot [N]: ";
                cin >> choice;
            }

            if (choice == 'Y')
            {
                multiplier++;
            }

            else if (choice == 'N')
            {
                cout << "[Exited the Dungeon]\n" << endl;
                calculateGold(inventory, playerGold, multiplier);
            }
        }

        else if (loot == loot5)
        {
            cout << "A cursed stone appears! It's so menancing that you died looking at it.\n" << endl;
            system("pause");
            system("cls");
        }
    }

    inventory.clear();
}

int main()
{
    int playerGold = 50;
    int multiplier = 1;
    vector<Item*> inventory;

    cout << "Welcome to the dungeons, adventurer! To enter, you just have to pay 25 gold. \nI pray that Lady Luck will be on your side today.\n" << endl;

    while (playerGold >= 25 && playerGold < 500)
    {
        enterDungeon(playerGold, inventory, multiplier);
    }

    evaluateEnding(playerGold);

    system("pause");
    return 0;
}


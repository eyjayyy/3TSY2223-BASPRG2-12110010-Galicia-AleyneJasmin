#include <iostream>
#include <string>
#include "Wizard.h"
#include "Spell.h"

using namespace std;

int main()
{
    // Instantiate  wizards
    Wizard* wizard1 = new Wizard("Gojo", 250, 0, 10, 15);
    Wizard* wizard2 = new Wizard("Yuuji", 250, 0, 10, 15);

    // Instantiate spells
    Spell* spell1 = new Spell("Hollow Purple", 60, 40, 50);
    Spell* spell2 = new Spell("Black Flash", 60, 40, 50);

    int round = 1;

    while (wizard1->mHp > 0 && wizard2->mHp > 0)
    {
        cout << "=== ROUND " << round << " ===" << endl;
        cout << "[" << wizard1->mName << " Stats]\n"
            << "HP: " << wizard1->mHp
            << "\nMP: " << wizard1->mMp << endl;
        cout << "\n[" << wizard2->mName << " Stats]\n"
            << "HP: " << wizard2->mHp
            << "\nMP: " << wizard2->mMp << "\n" << endl;

        // Wizard 1 Turn
        if (wizard1->mMp >= 50)
        {
            spell1->activate(wizard1, wizard2);
        }

        else if (wizard1->mMp < 50)
        {
            wizard1->attack(wizard2);
        }

        // Check if Wizard 2 is dead
        if (wizard2->mHp <= 0)
        {
            cout << wizard2->mName << " was killed by " << wizard1->mName << "! \n[FIGHT ENDS]\n" << endl;
            break;
        }

        // Wizard 2 Turn
        if (wizard2->mMp >= 50)
        {
            spell2->activate(wizard2, wizard1);
        }

        else if (wizard2->mMp < 50)
        {
            wizard2->attack(wizard1);
        }

        // Check if Wizard 1 is dead
        if (wizard1->mHp <= 0)
        {
            cout << wizard1->mName << " was killed by " << wizard2->mName << "! \n[FIGHT ENDS]\n" << endl;
            break;
        }

        round++;
    }

    delete wizard1;
    delete wizard2;
    delete spell1;
    delete spell2;

    system("pause");
    return 0;
}
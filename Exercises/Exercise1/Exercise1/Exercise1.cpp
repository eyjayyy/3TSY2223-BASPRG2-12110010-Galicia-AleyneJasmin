#include <iostream>
#include <time.h>

using namespace std;

struct Stats
{
    int dice[2];
    int rollValue;
    int rollRank;
};

//EX 1-1 (BET)
int deductBet(int& currentGold)
{
    int currentBet;

    cout << "\nEnter your bet: ";
    cin >> currentBet;

    while (currentBet > currentGold || currentBet <= 0)
    {
        cout << "Invalid bet. Please enter again: ";
        cin >> currentBet;
    }

    currentGold -= currentBet;

    return currentBet;
}

void deductBetVoid(int& currentGold)
{
    int currentBet;

    cout << "Enter bet: ";
    cin >> currentBet;

    while (currentBet > currentGold || currentBet <= 0)
    {
        cout << "Invalid bet. Please enter again: ";
        cin >> currentBet;
    }

    currentGold -= currentBet;
}

//EX 1-2 (DICE ROLL)
void diceRoll(Stats& currentRoller)
{
    for (int i = 0; i < 2; i++)
    {
        currentRoller.dice[i] = rand() % 6 + 1;
    }

    if (currentRoller.dice[0] == 1 && currentRoller.dice[1] == 1) //Snake Eyes
    {
        currentRoller.rollRank = 1;
    }

    else //Other rolls
    {
        currentRoller.rollRank = 2;
        currentRoller.rollValue = currentRoller.dice[0] + currentRoller.dice[1];
    }
}

//EX 1-3 (PAYOUT)
void payout(Stats player, Stats ai, int currentBet, int& currentGold)
{
    if (player.rollRank == 1 && ai.rollRank == 2) //Player gets snake eyes
    {
        cout << "\nYou rolled snake eyes. You win 3x your original bet :0\n" << endl;
        currentGold += currentBet * 3;
    }

    else if (player.rollRank == 1 && ai.rollRank == 1) //Both get snake eyes
    {
        cout << "\nTwo snake eyes, it's a draw! Roll again...\n" << endl;
        currentGold += currentBet;
    }

    else if (player.rollRank == 2 && ai.rollRank == 1) //AI gets snake eyes
    {
        cout << "\nAI rolled snake eyes. You lose your " << currentBet << " gold!\n" << endl;
    }

    else //No snake eyes
    {
        if (player.rollValue > ai.rollValue)
        {
            cout << "\nYou rolled a higher value. You win your " << currentBet << " gold!\n" << endl;
            currentGold += currentBet;
        }

        else if (player.rollValue < ai.rollValue)
        {
            cout << "\nAI rolled a higher value. You lose your " << currentBet << " gold!\n" << endl;
        }

        else
        {
            cout << "\nSame values, it's a draw! Roll again...\n" << endl;
            currentGold += currentBet;
        }
    }
}

//EX 1-4 (PLAY ROUND)
void playRound(int& playerGold)
{
    int playerBet;
    Stats player;
    Stats ai;

    cout << "Current Gold: " << playerGold << endl;

    playerBet = deductBet(playerGold);
    cout << "Current bet (" << playerBet << ") is deducted from your gold, leaving you with " << playerGold << " gold" << endl;

    diceRoll(ai);
    diceRoll(player);

    cout << "\nAI's Dice Roll: " << ai.dice[0] << ", " << ai.dice[1] << endl;
    cout << "\nYour Dice Roll: " << player.dice[0] << ", " << player.dice[1] << endl;
    
    payout(player, ai, playerBet, playerGold);
    system("pause");
}

int main()
{
    srand(time(0));

    int gold = 1000;
    
    while (gold > 0)
    {
        playRound(gold);
        system("CLS");
    }

    cout << "No more gold to bet! Just go home already...\n" << endl;
    system("pause");
}
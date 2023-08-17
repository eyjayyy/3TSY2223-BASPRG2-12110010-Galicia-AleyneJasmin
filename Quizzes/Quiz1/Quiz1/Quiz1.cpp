#include <iostream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

struct stats
{
	string side;
	vector<string> hand;
	string chosenCard;
};

bool hasRoundEnded = false;

vector<string> createHand(stats& challenger)
{
	vector<string> currentHand;
	
	if (challenger.side == "Emperor")
	{
		currentHand.push_back("Emperor");
	}

	else if (challenger.side == "Slave")
	{
		currentHand.push_back("Slave");
	}

	for (int i = 0; i < 4; i++)
	{
		currentHand.push_back("Civilian");
	}

	return currentHand;
}

void checkRoundOrder(int round, stats& player, stats& bot)
{
	hasRoundEnded = false;

	if ((round >= 1 && round <= 3) || (round >= 7 && round <= 9))
	{
		player.side = "Emperor";
		bot.side = "Slave";
	}

	else if ((round >= 4 && round <= 6) || (round >= 10 && round <= 12))
	{
		player.side = "Slave";
		bot.side = "Emperor";
	}

	cout << "=== ROUND " << round << " ===" << endl;
	cout << "Kaiji [" << player.side << "] vs. Tonegawa [" << bot.side << "]\n" << endl;

}

int wager(int& mmLeft)
{
	int mmToBet = 0;

	cout << "How many mm do you want to wager: ";
	cin >> mmToBet;

	while (mmToBet <= 0 || mmToBet > mmLeft)
	{
		cout << "Invalid bet. It should be from 1 to how many you have left. Bet again: ";
		cin >> mmToBet;
	}

	return mmToBet;
}

void convertMMToYen(int currentBet, stats player, int& moneyEarned)
{
	int moneyToAdd = 0;

	if (player.side == "Emperor")
	{
		moneyToAdd = currentBet * 100000;
	}

	else if (player.side == "Slave")
	{
		moneyToAdd = currentBet * 500000;
	}

	moneyEarned += moneyToAdd;
	cout << "He wins " << moneyToAdd << " yen!" << endl;
	cout << "Current Money: " << moneyEarned << " yen\n" << endl;
}

void evaluateMatchup(stats player, stats bot, int& moneyEarned, int mmWager, int& mmLeft)
{
	cout << "Kaiji plays [" << player.chosenCard << "]" << endl;
	cout << "Tonegawa plays [" << bot.chosenCard << "]\n" << endl;

	if ((player.chosenCard == "Slave" && bot.chosenCard == "Emperor") || (player.chosenCard == "Civilian" && bot.chosenCard == "Slave") || (player.chosenCard == "Emperor" && bot.chosenCard == "Civilian"))
	{
		cout << "KAIJI WINS THE ROUND!" << endl;
		convertMMToYen(mmWager, player, moneyEarned);
		hasRoundEnded = true;
	}

	else if ((player.chosenCard == "Slave" && bot.chosenCard == "Civilian") || (player.chosenCard == "Civilian" && bot.chosenCard == "Emperor") || (player.chosenCard == "Emperor" && bot.chosenCard == "Slave"))
	{
		cout << "KAIJI LOSES THE ROUND!" << endl;
		cout << "The contraption moves closer to his ear by " << mmWager << "mm" << endl;
		mmLeft -= mmWager;
		cout << "Distance Left: " << mmLeft << "mm\n" << endl;
		hasRoundEnded = true;
	}

	else if (player.chosenCard == bot.chosenCard)
	{
		cout << "IT'S A DRAW!" << endl;

		if (player.chosenCard == "Civilian" && bot.chosenCard == "Civilian")
		{
			cout << "The round goes on..." << endl;
		}

		else
		{
			cout << "Moving on to the next round..." << endl;
			hasRoundEnded = true;
		}
	}
}

void removePlayerCard(vector<string>& playerHand, int cardToRemove)
{
	playerHand.erase(playerHand.begin() + (cardToRemove - 1));
}

string playerPlayCard(vector<string>& playerHand)
{
	int chosenCardIndex = 0;
	string cardPicked;

	cout << "\nCurrent Cards:" << endl;
	for (int i = 0; i < playerHand.size(); i++)
	{
		cout << "(" << i + 1 << ")" << playerHand[i] << endl;
	}

	cout << "Choose Card Number to Play: ";
	cin >> chosenCardIndex;

	while (chosenCardIndex >= playerHand.size() + 1 || chosenCardIndex <= 0)
	{
		cout << "Invalid card number. Please choose from available cards: ";
		cin >> chosenCardIndex;
	}

	cardPicked = playerHand[chosenCardIndex - 1];
	removePlayerCard(playerHand, chosenCardIndex);

	return cardPicked;
}

string botPlayCard(vector<string>& botHand)
{
	int randomCardIndex = 0;
	string cardPicked;

	randomCardIndex = rand() % botHand.size();
	cardPicked = botHand[randomCardIndex];
	botHand.erase(botHand.begin() + randomCardIndex);
	return cardPicked;
}

void evaluateEnding(int round, int mmLeft, int moneyEarned)
{
	if (round > 12 && mmLeft > 0)
	{
		cout << "After 12 straight rounds..." << endl;

		if (moneyEarned >= 20000000)
		{
			cout << "Congratulations! You managed to defeat the odds and earned enough money. Not to mention, your precious ear is safe!" << endl;
			cout << "[BEST ENDING]" << endl;
		}

		else
		{
			cout << "You didn't quite reach the money you needed but atleast your precious ear is still safe. Better luck next time!" << endl;
			cout << "[MEH ENDING]" << endl;
		}
	}

	else if (mmLeft <= 0)
	{
		cout << "OUCH! There goes your precious ear... Maybe you shouldn't bite off more than you can chew." << endl;
		cout << "[BAD ENDING]" << endl;
	}
}

void playRound(int round, int& money, int& mmLeft)
{
	srand(time(0));
	stats player;
	stats bot;
	int mmBet = 0;

	checkRoundOrder(round, player, bot);

	cout << "Current Money: " << money << " yen" << endl;
	cout << "Contraption Distance Left: " << mmLeft << "mm\n" << endl;

	mmBet = wager(mmLeft);

	// create deck
	player.hand = createHand(player);
	bot.hand = createHand(bot);

	while (!hasRoundEnded)
	{
		player.chosenCard = playerPlayCard(player.hand);
		bot.chosenCard = botPlayCard(bot.hand);
		evaluateMatchup(player, bot, money, mmBet, mmLeft);
		system("pause");
	}
}

int main()
{
	srand(time(0));

	// Initialize variables
	int round = 1;
	int mmLeft = 30;
	int moneyEarned = 20000000;

	// Continue playing until last round or if victoryConditions are met
	while (round <= 12 && mmLeft > 0)
	{
		// Play the round
		playRound(round, moneyEarned, mmLeft);

		// Round ended. Increment round
		round++;
		system("cls");
	}

	evaluateEnding(round, mmLeft, moneyEarned);
	cout << endl;
	system("pause");
	return 0;
}
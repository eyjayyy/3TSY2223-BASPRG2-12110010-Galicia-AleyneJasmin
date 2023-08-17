#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

vector<string> items = { "RedPotion", "Elixir", "EmptyBottle", "BluePotion" };

vector<string> fillInventory(vector<string>& _items)
{
    vector<string> inventory;

    for (int i = 0; i < 10; i++)
    {
        inventory.push_back(_items.at(rand() % _items.size()));
    }

    return inventory;
}

void displayInventory(const vector<string>& _myInventory)
{
    for (int i = 0; i < _myInventory.size(); i++)
    {
        cout << _myInventory[i] << endl;
    }
}

int countItem(const vector<string>& _myInventory, string _itemToFind)
{
    int count = 0;

    for (int i = 0; i < _myInventory.size(); i++)
    {
        if (_myInventory.at(i) == _itemToFind)
        {
            count++;
        }
    }

    return count;
}

void removeItem(vector<string>& _myInventory, string _itemToRemove)
{
    for (int i = 0; i < _myInventory.size(); i++)
    {
        if (_myInventory.at(i) == _itemToRemove)
        {
            _myInventory.erase(_myInventory.begin() + i);
        }
    }
}

int main()
{
    srand(time(0));

    // fill and display inventory
    cout << "Current Inventory" << endl;
    vector<string> currentInventory;
    currentInventory = fillInventory(items);
    displayInventory(currentInventory);

    // count items (elixirs)
    cout << "\nNumber of Elixirs: " << countItem(currentInventory, "Elixir") << endl;

    // remove items (red potions)
    cout << "\nRemoving Red Potions..." << endl;
    removeItem(currentInventory, "RedPotion");

    cout << "\nCurrent Inventory" << endl;
    displayInventory(currentInventory);

    system("pause");
}
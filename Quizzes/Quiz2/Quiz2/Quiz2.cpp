#include <iostream>
#include <string>
#include<time.h>
#include "Node.h"

using namespace std;

// Display remaining members
void printLinkedList(Node* head)
{
    Node* current = head;

    cout << "Remaining Members:\n" 
        << current->name << endl;
    current = current->next;

    while (current != head)
    {
        cout << current->name << endl;
        current = current->next;
    }
}

// Get soldier names and create list
Node* createCircularLinkedList(int memberCount)
{
    Node* head = nullptr;
    Node* current = nullptr;
    Node* previous = nullptr;

    // first soldier
    current = new Node;
    cout << "Enter soldier name: ";
    cin >> current->name;
    head = current;
    previous = current;

    // other soldiers
    for (int i = 0; i < memberCount - 1; i++)
    {
        current = new Node;
        cout << "Enter soldier name: ";
        cin >> current->name;
        previous->next = current;
        previous = current;
    }

    previous->next = head;

    return head;
}

// Randomize first cloak holder
Node* randomizeCloakHolder(Node* head, int memberCount)
{
    int cloakHolderIndex = rand() % memberCount;
    Node* current = head;

    // find cloak holder by traversing thru nodes
    for (int i = 0; i < cloakHolderIndex; i++)
    {
        current = current->next;
    }

    return current;
}

Node* removeCloakHolder(Node* head, int indexToRemove, int &memberCount)
{
    Node* toDelete = head;
    Node* previous = nullptr;

    // traverse nodes
    for (int i = 0; i < indexToRemove; i++)
    {
        previous = toDelete;
        toDelete = toDelete->next;
    }

    // reconnect link
    previous->next = toDelete->next;

    cout << toDelete->name << " has been eliminated.\n" << endl;
    memberCount--;
    return toDelete->next;

    // delete cloak holder node
    delete toDelete;
    toDelete = nullptr;
}

int main()
{
    srand(time(0));
    int round = 1;
    int memberCount = 5;
    Node* head = createCircularLinkedList(memberCount);
    Node* startingPerson = randomizeCloakHolder(head, memberCount);

    // gameplay loop
    while (memberCount > 1)
    {
        cout << "\n=== [ROUND " << round << "] ===" << endl;
        printLinkedList(startingPerson);

        int cloakNum = rand() % memberCount + 1;
        cout << "\nRESULTS:\n" 
            << startingPerson->name << " draws " << cloakNum << "." << endl;
        startingPerson = removeCloakHolder(startingPerson, cloakNum, memberCount);
        round++;
    }

    // ending
    cout << "=== [FINAL RESULT] ===\n" << startingPerson->name << " will go to seek for reinforcements.\n\n" << endl;
    system("pause");
    return 0;
}
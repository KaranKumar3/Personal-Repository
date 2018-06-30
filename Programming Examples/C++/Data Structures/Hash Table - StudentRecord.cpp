//
// Created by Karan Kumar on 6/16/2018. A hash table implemented specifically for a school record keeping system.
//
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class node //HashTable node contains information you would normally find in a student record
{
public:
    string name;
    double GPA;
    int AcademicLevel;
    int key;
    node* next; //pointer to the next student if a new student is hashed into the same bucket

    node(string name, double GPA, int AcademicLevel, int key) // node constructor
    {
        this->name = name;
        this->GPA = GPA;
        this->AcademicLevel = AcademicLevel;
        this->key = key;

        this->next = nullptr;
    }
};

class HashTable //Implemented using chaining to avoid collisions
{
public:
    int m = 1000; //Table size (m) set to 1000

    node** table;
    HashTable() //Constructor
    {
        table = new node* [m];

        for (int i = 0; i< m; i++) {
            table[i] = nullptr;
        }
    }
    int getHashKey(int x) {return (x % m);} //Creates index to hash the key into
    void INSERT(node**, node* );
    void SEARCH(node**, int);
    void DELETE(node**, int);
};

void HashTable::INSERT(node **T, node* x) { //Inserts a given node into a given hash table

    int hashKey = getHashKey(x->key);

    node* previous = nullptr;
    node* tableNode = T[hashKey]; //Table node at the hashed index
	
	//Check if node are already in the index, if so find the end of the linked list
    while (tableNode != nullptr) { 
        previous = tableNode;
        tableNode = tableNode->next;
    }

    tableNode = new node(x->name, x->GPA, x->AcademicLevel, x->key); //Creates node to be inserted

    if (previous == nullptr) { //If no node has been inserted at the index yet, previous is null
        T[hashKey] = tableNode; //Insert imediately, no problems
    }
    else { //We have a collision
        previous->next = tableNode; //Insert the node at the end of the linked list at the index
    }

    cout << "Key: " << x->key << " was successfully inserted at table index: " << hashKey << endl;
}

void HashTable::SEARCH(node **T, int x) { //Searches a given hashtable for a given key
	//this basically returns a yes or no as a normal hash table search would, but it can be modified to return the record itself if so desired
	
    int hashKey = getHashKey(x);

    node* tableNode = T[hashKey];

    while (tableNode != nullptr) {

        if (tableNode->key == x) { 

            cout << "Key: " << x << " was found in index: " << hashKey << endl; 
            return;
        }
        tableNode = tableNode->next;
    }

    if (tableNode == nullptr) {
        cout << "Key: " << x << " was not found "<< endl;
    }
}

void HashTable::DELETE(node **T, int x) { //Delete a node given a key from a given hash table

    int hashKey = getHashKey(x);

    node* previous = nullptr;
    node* tableNode = T[hashKey];

	//Find node with key x
    while (tableNode->next && tableNode->key != x) {
        previous = tableNode;
        tableNode = tableNode->next;
    }
    if (tableNode->key == x) { //The node exists in the table
        if (previous != nullptr) {
            previous->next = tableNode->next; //effectively removes pointer to the node we want to delete
        }
        else {
            tableNode = nullptr; //if only a single node, remove the pointer
        }
        delete tableNode; //Actually delete the node from memory
        cout << x <<" has been deleted" << endl;
    }
    else { //The node does not exist in the table
        cout<<"Key: "<< x << " does not exist in the record" << endl;
        return;
    }
}

int main()
{
    HashTable hashT;
    int choice;
	
	string name;
	double GPA;
    int AcademicLevel;
    int key;
    
    while (true)
    {
        cout << endl << endl;
        cout << " Hash Table Implementation " << endl;
        cout << " ========================== " << endl;
        cout << " 1. Insert a Record " << endl;
        cout << " 2. Search the table " << endl;
        cout << " 3. Delete a Record " << endl;
        cout << " 4. Exit " << endl;
        cout << " Enter your choice : ";
        cin >> choice;
        switch (choice)
        {
            case 1:{
                cout << " Enter Student Name : ";
                getline(cin, name);
                getline(cin, name);
                cout << " Enter their GPA : ";
                cin >> GPA;
                cout << " Enter their Academic Level (numeric): ";
                cin >> AcademicLevel;
                cout << " Enter a key value (between 0 - 65536): ";
                cin >>key;
                node *n = new node(name, GPA, AcademicLevel, key);
                hashT.INSERT(hashT.table, n);
                break;
            }
            case 2: {
                cout << endl;
                cout << " Enter a key value to search for: " << endl;
                cin >>key;
                hashT.SEARCH(hashT.table, key);
                break;
            }
            case 3: {
                cout << endl;
                cout << " Enter the key for the student you wish to delete: " << endl;
                cin >>key;
                hashT.DELETE(hashT.table, key);
                break;
            }

            case 4: {
                cout << endl;
                cout << " EXIT " << endl;
                return 0;
            }

            default: {
                cout << endl;
                cout << "Invalid choice";
                break;
            }

        }
    }
}
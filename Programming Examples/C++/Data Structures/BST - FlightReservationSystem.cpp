//
// Created by Karan Kumar on 6/11/2018.
//
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

class node
{
public:
    node* left;
    node* right;
    node* parent;
    int fTime; //flight time
    int fNum; // flight number
};

class BinarySearchTree
{
public:
    node* root;
    BinarySearchTree()
    {
        root = nullptr;
    }
    bool isEmpty() const { return root == nullptr; }
    void TREE_INSERT(int, int, int);
    node* FIND_MIN(node*);
    node* SUCCESSOR(node*);
    void DELETE_NODE(node*, int);
    void LIST_RESERVATIONS(node*);
};

void BinarySearchTree::TREE_INSERT(int time, int num, int limit)
{
    int k = limit;
    node* z = new node();
    z->fTime = time;
    z->fNum = num;
    z->left = nullptr;
    z->right = nullptr;

    node* y = nullptr;
    node* x = root;

    while (x != nullptr)
    {
        if(abs(z->fTime - x->fTime) < k) {
            cout << "We're sorry, that time is too close to a reservation. " <<endl;
            cout << "Please choose another. " <<endl;
            return;
        }
        y = x;
        if (z->fTime < x->fTime)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == nullptr)
        root = z;
    else if (z->fTime < y->fTime)
        y->left = z;
    else
        y->right = z;
}

node* BinarySearchTree::FIND_MIN(node* x)
{
    while (x->left != nullptr)
    {
        x = x->left;
    }
    return x;
}

node* BinarySearchTree::SUCCESSOR(node* x)
{
    while (x->right != nullptr)
    {
        return FIND_MIN(x->right);
    }

    node* y = x->parent;
    while (y != nullptr and x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

void BinarySearchTree::DELETE_NODE(node* T, int key) {

    node* x;
    node *y;
    node* z = T;

    if(z == nullptr) {
        cout<<"Reservation list is empty"<<endl;
        return;
    }
    bool is_inTree = false; //bool checks if the node is even in the tree

    while(z != nullptr) {
        if(z->fTime == key) {
            is_inTree = true;
            break;
        }
        else {
            if(key > z->fTime) {
                z = z->right;
            }
            else {
                z = z->left;
            }
        }
    }

    if(!is_inTree) {
        cout << z <<" has not been reserved." << endl;
        return;
    }

    if( (z->left == nullptr)||(z->right == nullptr)) {//z has only 0 or 1 child
        y = z;
    }
    else {
        y = SUCCESSOR(z); //z has 2 children, slice out successor y
    }

    if( y->left != nullptr) {
        x = y->left;
    }
    else {
        x = y->right;
    }

    if (x != nullptr){
        x->parent = y->parent;
    }

    if(y->parent == nullptr){
        x = T;
    }

    else if (y == (y->parent)->left){
        (y->parent)->left = x;
    }
    else {
        (y->parent)->right = x;
    }

    if (y != z)
        z->fTime = y->fTime;
}

void BinarySearchTree::LIST_RESERVATIONS(node* x)
{
    if (x != nullptr)
    {
        if (x->left) LIST_RESERVATIONS(x->left);
        cout << "Flight Time: " << x->fTime << " Flight Number: " << x->fNum <<endl;
        if (x->right) LIST_RESERVATIONS(x->right);
    }
}

int main()
{
    BinarySearchTree bst;
    int choice, fTime, fNum, limit; // Limit or "k" acts as buffer between reservations
    cout << " Please enter a k : ";
    cin >> limit;

    while (true)
    {
        cout << endl;
        cout << " Landing Times BST " << endl;
        cout << " ----------------------------- " << endl;
        cout << " 1. Request Landing " << endl;
        cout << " 2. Withdraw Landing Request " << endl;
        cout << " 3. List Landing Times and Flight #'s " << endl;
        cout << " 4. Exit " << endl;
        cout << " Enter your choice : ";
        cin >> choice;
        switch (choice)
        {
            case 1: cout << " What time would you like to request? : ";
                cin >> fTime;
                cout << " What is the flight number? : ";
                cin >> fNum;
                bst.TREE_INSERT(fTime, fNum, limit);
                break;

            case 2: cout << " What time would you like to withdraw? : ";
                cin >> fTime;
                bst.DELETE_NODE(bst.root, fTime);
                break;
            case 3: cout << endl;
                cout << " Current Reservations " << endl;
                cout << " -------------------" << endl;
                bst.LIST_RESERVATIONS(bst.root);
                break;
            case 4: cout << " EXIT " << endl;
                return 0;
            default:
                cout << "Invalid choice";
        }
    }
}
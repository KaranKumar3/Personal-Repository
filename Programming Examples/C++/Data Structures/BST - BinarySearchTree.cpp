//
// Created by Karan Kumar on 6/7/2018.
//
#include <iostream>
#include <cstdlib>
using namespace std;

class node
{
public:
    node* left;
    node* right;
    node* parent;
    int key;
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
    void TREE_INSERT(int );
    void PREORDER_TREE_WALK(node*);
    void POSTORDER_TREE_WALK(node*);
    void INORDER_TREE_WALK(node*);
    int FIND_MAX(node*);
    void REMOVE_MAX(node*);
    node* FIND_MIN(node*);
    node* SUCCESSOR(node*);
    void DELETE_NODE(node*, int);
};

void BinarySearchTree::TREE_INSERT(int d)
{
    node* z = new node();
    z->key = d;
    z->left = nullptr;
    z->right = nullptr;

    node* y = nullptr;
    node* x = root;

    while (x != nullptr)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == nullptr)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
}

void BinarySearchTree::PREORDER_TREE_WALK(node* x)
{
    if (x != nullptr)
    {
        cout << " " << x->key << " ";
        if (x->left) PREORDER_TREE_WALK(x->left);
        if (x->right) PREORDER_TREE_WALK(x->right);
    }
}

void BinarySearchTree::POSTORDER_TREE_WALK(node* x)
{
    if (x != nullptr)
    {
        if (x->left) POSTORDER_TREE_WALK(x->left);
        if (x->right) POSTORDER_TREE_WALK(x->right);
        cout << " " << x->key << " ";
    }
}

void BinarySearchTree::INORDER_TREE_WALK(node* x)
{
    if (x != nullptr)
    {
        if (x->left) INORDER_TREE_WALK(x->left);
        cout << " " << x->key << " ";
        if (x->right) INORDER_TREE_WALK(x->right);
    }
}

int BinarySearchTree::FIND_MAX(node* x)
{
    while (x->right != nullptr)
    {
        x = x->right;
    }
    return x->key;
}

void BinarySearchTree::REMOVE_MAX(node* x)
{
    node *y = x;
    node *z = nullptr;
    while (y->right != nullptr) {
        z = y;
        y = y->right;
    }
    if (z == nullptr) {
        x = x->left;
    }
    else {
        z->right = nullptr;
    }
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
        cout<<"Tree is empty"<<endl;
        return;
    }
    bool is_inTree = false; //bool checks if the node is even in the tree

    while(z != nullptr) {
        if(z->key == key) {
            is_inTree = true;
            break;
        }
        else {
            if(key > z->key) {
                z = z->right;
            }
            else {
                z = z->left;
            }
        }
    }

    if(!is_inTree) {
        cout << z <<" is not in the tree." << endl;
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
        z->key = y->key;
}


int main()
{
    BinarySearchTree bst;
    int choice, key;
    while (true)
    {
        cout << endl << endl;
        cout << " Binary Search Tree Example " << endl;
        cout << " ----------------------------- " << endl;
        cout << " 1. Insert a Node " << endl;
        cout << " 2. Pre-Order Traversal " << endl;
        cout << " 3. Post-Order Traversal " << endl;
        cout << " 4. In-Order Traversal " << endl;
        cout << " 5. Find Max " << endl;
        cout << " 6. Remove Max " << endl;
        cout << " 7. Successor " << endl;
        cout << " 8. Delete a Node " << endl;
        cout << " 9. Exit " << endl;
        cout << " Enter your choice : ";
        cin >> choice;
        switch (choice)
        {
            case 1: cout << " Enter key (int value) to be inserted : ";
                cin >> key;
                bst.TREE_INSERT(key);
                break;
            case 2: cout << endl;
                cout << " Pre-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.PREORDER_TREE_WALK(bst.root);
                break;
            case 3: cout << endl;
                cout << " Post-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.POSTORDER_TREE_WALK(bst.root);
                break;
            case 4: cout << endl;
                cout << " In-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.INORDER_TREE_WALK(bst.root);
                break;
            case 5: cout << endl;
                cout << " MAX is : " << bst.FIND_MAX(bst.root) << endl;
                break;
            case 6: cout << endl;
                cout << " REMOVED MAX " << endl;
                bst.REMOVE_MAX(bst.root);
                break;
            case 7: cout << " Enter key (int value) to find successor of : ";
                cin >> key;
                cout << " The successor of " << key << " is: " << bst.SUCCESSOR(bst.root) << endl;
                break;
            case 8: cout << " Enter key value to delete : ";
                cin >> key;
                bst.DELETE_NODE(bst.root, key);
                cout << " Deleted : " << key << endl;
                break;
            case 9: cout << " EXIT " << endl;
                return 0;
            default:
                cout << "Invalid choice";
        }
    }
}
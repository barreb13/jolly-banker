// accounttree.cpp
// Created by Brent and James on 3/8/2020
//

#include "accounttree.h"
#include <fstream>

// constructor sets root to null
AccountTree::AccountTree() { root = nullptr; }

// Delete all nodes in BST
AccountTree::~AccountTree() {
    // Call clear method to clear tree
    clear(root);
}

// Insert new account
bool AccountTree::insert(Account* account) {
    // Call recursive helper
    return insertHelper(root, account);
}

// Insert Helper - Recursive and Boolean!
bool AccountTree::insertHelper(Node* node, Account* newAccount) {
    // Base case or if empty
    if (node == nullptr) {
        root = new Node(newAccount);
        return true;
    }

    // If newAccount < node then start going down left side
    if (newAccount->getAccountNum() < node->AccountPtr->getAccountNum()) {
        if (node->Left == nullptr) {
            node->Left = new Node(newAccount);
            return true;
        }
        return insertHelper(node->Left, newAccount);
    }

    // Else if newAccount > node then start going down right side
    if (newAccount->getAccountNum() > node->AccountPtr->getAccountNum()) {
        if (node->Right == nullptr) {
            node->Right = new Node(newAccount);
            return true;
        }
        return insertHelper(node->Right, newAccount);
    }
    return false;
}

// Retrieve account
// returns true if successful, points account to found account
bool AccountTree::retrieve(const int& accountNumber, Account*& account) const {
    // call to recursive retrieve helper
    return (retrieveHelper(root, accountNumber, account));
}

// recursive Retrieve Helper, points account to found account
bool AccountTree::retrieveHelper(Node* node, int accountNumber,
                                 Account*& accountPtr) const {
    if (node == nullptr) {
        return false;
    }

    if (node->AccountPtr->getAccountNum() == accountNumber) {
        accountPtr = node->AccountPtr;
        return true;
    }

    if (accountNumber < node->AccountPtr->getAccountNum()) {
        return retrieveHelper(node->Left, accountNumber, accountPtr);
    }

    return retrieveHelper(node->Right, accountNumber, accountPtr);
}

// Display information on all accounts
void AccountTree::display() {
    // Call inOrderPrint
    inOrderPrint(root);
}

// Display helper - traverses inorder
void AccountTree::inOrderPrint(Node* current) {
    if (current != nullptr) {
        inOrderPrint(current->Left);

        std::ofstream outfile;
        outfile.open("BankTransOut.txt", std::ios_base::app);

        outfile << current->AccountPtr->getLastName() << " ";
        outfile << current->AccountPtr->getFirstName();
        outfile << " Account ID: ";
        outfile << current->AccountPtr->getAccountNum() << endl;

        for (int i = 0; i < 10; i++) {
            outfile << "        " << current->AccountPtr->getSubAccName(i)
                    << ": $" << current->AccountPtr->getSubAccBalance(i)
                    << endl;
        }
        outfile << endl;
        inOrderPrint(current->Right);
        outfile.close();
    }
}

// delete all information in AccountTree
void AccountTree::clear(Node* node) {
    if (node != nullptr) {
        clear(node->Left);
        clear(node->Right);
        // delete accounts and nodes
        delete node->AccountPtr;
        delete node;
    }
}

// check if tree is empty
bool AccountTree::isEmpty() const { return root == nullptr; }
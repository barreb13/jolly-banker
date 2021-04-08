// accounttree.h
// Created by Brent and James on 3/8/2020
//

#pragma once

#include "account.h"
#include <iostream>

using namespace std;

class AccountTree {
  public:
    // Create BST
    AccountTree();

    // Delete all nodes in BST
    ~AccountTree();

    // Insert new account
    bool insert(Account* account);

    // Retrieve account
    // returns true if successful AND *Account points to account
    // NOLINTNEXTLINE
    bool retrieve(const int& accountNumber, Account*& account) const;

    // Display information on all accounts
    void display();

    // check if tree is empty
    bool isEmpty() const;

  private:
    class Node {
      public:
        explicit Node(Account* account)
            : AccountPtr{account}, Right{nullptr}, Left{nullptr} {}

        Account* AccountPtr;
        Node* Right;
        Node* Left;
    };

    Node* root;

    // Insert recursive helper - has to be AFTER Node has been declared
    bool insertHelper(Node* node, Account* newAccount);

    // delete all information in AccountTree
    void clear(Node* node);

    // Retrieve Helper
    // NOLINTNEXTLINE
    bool retrieveHelper(Node* node, int accountNumber,
                        // NOLINTNEXTLINE
                        Account*& accountPtr) const;

    // inOrderPrint
    void inOrderPrint(Node* current);
};

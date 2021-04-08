// bank.h
// Created by Brent and James on 3/8/2020
//

#pragma once

#include "accounttree.h"
#include <fstream>
#include <queue>
#include <string>

using namespace std;

class Bank {
  public:
    Bank();
    ~Bank();

    // process transactions in given file
    void processTransactions(const string& fileName);
    // display all accounts and balances
    void displayAllBankBalances();

    // Transaction Types
    bool deposit(const string& transaction);
    bool withdraw(const string& transaction);
    bool open(const string& transaction);
    bool transfer(const string& transaction);
    bool history(const string& transaction);

  private:
    AccountTree accountBST;
    // queue to hold transactions for processing
    queue<string> transactionQueue;
};

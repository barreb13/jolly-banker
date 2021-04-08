// bank.cpp
// Created by Brent and James on 3/8/2020
//

// Input.txt is read into bank class

#include "bank.h"
#include <queue>
#include <sstream>

// constructors/destructors
Bank::Bank() = default;
Bank::~Bank() = default;

// reads a file then process transactions by calling associated methods
void Bank::processTransactions(const string& fileName) {

    ifstream input(fileName);
    string line;

    // store line by line into queue
    while (getline(input, line)) {
        transactionQueue.push(line);
    }
    // Everything is in queue at this point

    string transaction;

    // output and pop line by line
    while (!transactionQueue.empty()) {
        transaction = transactionQueue.front();
        transactionQueue.pop();

        // parse first character and call appropriate function
        if (transaction[0] == 'O') {
            open(transaction);
        }

        if (transaction[0] == 'D') {
            deposit(transaction);
        }

        if (transaction[0] == 'W') {
            withdraw(transaction);
        }

        if (transaction[0] == 'T') {
            transfer(transaction);
        }

        if (transaction[0] == 'H') {
            history(transaction);
        }
    }
    // Everything is out of the queue at this point
}

// display all accounts and balances
void Bank::displayAllBankBalances() {
    std::ofstream outfile;
    outfile.open("BankTransOut.txt", std::ios_base::app);
    outfile << "\nProcessing Done. Final Balances" << endl;

    // Display the BST
    accountBST.display();
}

// open an account, insert it into the BSTtree
// return true if successful
bool Bank::open(const string& transaction) {
    string firstName;
    string lastName;
    int accountNum = 0;
    string word;
    queue<string> tempQueue;

    std::ofstream outfile;
    outfile.open("BankTransOut.txt", std::ios_base::app);

    istringstream iss(transaction, istringstream::in);

    while (iss >> word) {
        tempQueue.push(word);
    }

    // parse given string
    tempQueue.pop();
    lastName = tempQueue.front();
    tempQueue.pop();
    firstName = tempQueue.front();
    tempQueue.pop();
    accountNum = stoi(tempQueue.front());
    tempQueue.pop();

    Account* current = nullptr;
    if (accountBST.retrieve(accountNum, current)) {
        // Output Error Message
        outfile << "ERROR: Account " << accountNum
                << " is already open. Transaction refused." << endl;
        return false;
    }

    // making a new account
    auto* newAccount = new Account(firstName, lastName, accountNum);

    // Add account to BST
    accountBST.insert(newAccount);

    return false;
}

// deposit into fund of an account
bool Bank::deposit(const string& transaction) {
    int fund = 0;
    int accountNum = 0;
    int amount = 0;
    string word;
    queue<string> tempQueue;

    std::ofstream outfile;
    outfile.open("BankTransOut.txt", std::ios_base::app);

    istringstream iss(transaction, istringstream::in);

    while (iss >> word) {
        tempQueue.push(word);
    }

    // parse given string
    tempQueue.pop();
    word = tempQueue.front();
    fund = stoi(word.substr(4, 1));
    word.pop_back();
    accountNum = stoi(word);
    tempQueue.pop();
    amount = stoi(tempQueue.front());
    tempQueue.pop();

    Account* current = nullptr;
    if (!accountBST.retrieve(accountNum, current)) {
        // Output Error Message
        outfile << "Can't deposit, this account does not exist" << endl;
        return false;
    }

    // deposit into account and log
    current->subAccDeposit(fund, amount);
    current->writeAccountRecord(transaction, fund);
    return false;
}

// withdraw from fund in account
bool Bank::withdraw(const string& transaction) {
    int fund = 0;
    int accountNum = 0;
    int amount = 0;
    string word;
    queue<string> tempQueue;

    std::ofstream outfile;
    outfile.open("BankTransOut.txt", std::ios_base::app);

    istringstream iss(transaction, istringstream::in);

    while (iss >> word) {
        tempQueue.push(word);
    }

    // parse given string
    tempQueue.pop();
    word = tempQueue.front();
    fund = stoi(word.substr(4, 1));
    word.pop_back();
    accountNum = stoi(word);
    tempQueue.pop();
    amount = stoi(tempQueue.front());
    tempQueue.pop();
    // All variables are set

    // return false if account does not exist
    Account* current = nullptr;
    if (!accountBST.retrieve(accountNum, current)) {
        // Output Error Message
        outfile << "ERROR: Can't withdraw, this account does not exist" << endl;
        return false;
    }

    // return false if insufficient funds
    if (!current->subAccWithdraw(fund, amount)) {
        current->writeAccountRecord(transaction + " (Failed)", fund);
        return false;
    }

    // log to account record
    current->writeAccountRecord(transaction, fund);
    return true;
}

// transfer between two funds
bool Bank::transfer(const string& transaction) {
    int fromFund = 0;
    int toFund = 0;
    int fromAccountNum = 0;
    int toAccountNum = 0;
    int amount = 0;
    string word;
    queue<string> tempQueue;

    std::ofstream outfile;
    outfile.open("BankTransOut.txt", std::ios_base::app);

    istringstream iss(transaction, istringstream::in);

    while (iss >> word) {
        tempQueue.push(word);
    }

    tempQueue.pop();

    // parse given string starting with "fromAccount"
    word = tempQueue.front();
    fromFund = stoi(word.substr(4, 1));
    word.pop_back();
    fromAccountNum = stoi(word);
    tempQueue.pop();
    // Get the amount
    amount = stoi(tempQueue.front());
    tempQueue.pop();
    // Getting "toAccount" fund info
    word = tempQueue.front();
    toFund = stoi(word.substr(4, 1));
    word.pop_back();
    toAccountNum = stoi(word);
    tempQueue.pop();

    // Get pointer to fromAccount
    Account* fromAccountPtr = nullptr;
    if (!accountBST.retrieve(fromAccountNum, fromAccountPtr)) {
        // Output Error Message
        outfile << "ERROR: Could not find Account " << fromAccountNum
                << " Transfer cancelled." << endl;
        return false;
    }

    // Get pointer to toAccount
    Account* toAccountPtr = nullptr;
    if (!accountBST.retrieve(toAccountNum, toAccountPtr)) {
        // Output Error Message
        outfile << "ERROR: Could not find Account " << toAccountNum
                << " Transfer cancelled." << endl;
        return false;
    }

    // try to withdraw, deposit if successful
    if (fromAccountPtr->subAccWithdraw(fromFund, amount)) {
        toAccountPtr->subAccDeposit(toFund, amount);
        fromAccountPtr->writeAccountRecord(transaction, fromFund);
        return true;
    }

    return false;
}

// display account history for 1 fund or all funds
bool Bank::history(const string& transaction) {

    int fund = -1;
    int accountNum = 0;
    string word;
    queue<string> tempQueue;

    std::ofstream outfile;
    outfile.open("BankTransOut.txt", std::ios_base::app);

    istringstream iss(transaction, istringstream::in);

    while (iss >> word) {
        tempQueue.push(word);
    }

    // parse given string
    tempQueue.pop();
    word = tempQueue.front();
    // if length is 5, we are showing history for 1 fund only, get fund#
    if (word.length() == 5) {
        fund = stoi(word.substr(4, 1));
        word.pop_back();
    }
    accountNum = stoi(word);
    tempQueue.pop();

    // get pointer to account
    Account* current = nullptr;
    if (!accountBST.retrieve(accountNum, current)) {
        // Output Error Message
        outfile << "Can't display, this account does not exist" << endl;
        return false;
    }

    // call function to display all funds or 1 fund
    if (fund == -1) {
        // Display everything
        current->displayAccountRecord();
    } else {
        outfile << "Displaying Transaction History for "
                << current->getLastName() << " " << current->getFirstName()
                << "'s ";
        outfile.close();
        current->displaySubAccountRecord(fund);
    }
    return true;
}

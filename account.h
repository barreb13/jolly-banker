// account.h
// Created by Brent and James on 3/8/2020
//
// Each client account contains assets held in up to ten funds
#pragma once
#include "fund.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Account {

  public:
    // Account constructor w/ parameters
    Account(string first, string last, int account);

    // Account destructor
    ~Account();

    // Getters
    int getAccountNum();

    // returns name of a subaccount
    string getSubAccName(int fundNum);

    // returns balance of a subaccount
    int getSubAccBalance(int fundNum);

    // returns firstName
    string getFirstName();

    // returns lastName
    string getLastName();

    // deposit amount into a subaccount
    bool subAccDeposit(int fundNum, int amount);

    // withdraw amount from a subaccount
    bool subAccWithdraw(int fundNum, int amount);

    // write record to a subaccount
    void writeAccountRecord(const string& record, int fundNum);

    // display records for a single subaccount
    void displaySubAccountRecord(int fundNum);

    // display records for all subaccounts
    void displayAccountRecord();

  private:
    int accountNum{};
    string firstName;
    string lastName;

    // array of 10 funds representing a subaccount
    Fund fundsArray[10];
};

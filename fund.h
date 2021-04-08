// fund.h
// Created by Brent and James on 3/8/2020
//

#pragma once

#include <iostream>
#include <string>

using namespace std;

class Fund {
  public:
    Fund();
    ~Fund();

    // returns fundBalance
    int getFundBalance() const;

    // returns fundName
    string getFundName() const;

    // sets fundName
    void setFundName(string name);

    // sets fundBalance
    void setFundBalance(int balance);

    // deposit into fund
    void fundDeposit(int amount);

    // withdraw from fund
    void fundWithdraw(int amount);

    // add record
    void addFundRecord(const string& record);

    // display fundRecord
    void displayFundRecord();

  private:
    int fundBalance = 0;
    string fundName;
    string fundRecord;
};

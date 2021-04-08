// fund.cpp
// Created by Brent and James on 3/8/2020
//

#include "fund.h"
#include <fstream>
#include <string>
#include <utility>
using namespace std;
// constructor/destructor
Fund::Fund() = default;
Fund::~Fund() = default;

// returns fundBalance
int Fund::getFundBalance() const { return fundBalance; }

// returns fundName
string Fund::getFundName() const { return fundName; }

// sets fundName
void Fund::setFundName(string name) { fundName = std::move(name); }

// sets fundBalance
void Fund::setFundBalance(int balance) { fundBalance = balance; }

// deposit into fund
void Fund::fundDeposit(int amount) { fundBalance += amount; }

// withdraw from fund
void Fund::fundWithdraw(int amount) { fundBalance -= amount; }

// add record
void Fund::addFundRecord(const string& record) {
    fundRecord += (record + '\n');
}

// display fundRecord
void Fund::displayFundRecord() {
    std::ofstream outfile;
    outfile.open("BankTransOut.txt", std::ios_base::app);
    outfile << fundName << ": $" << fundBalance << endl;
    outfile << fundRecord;
}

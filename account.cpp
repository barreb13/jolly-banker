// account.cpp
// Created by Brent and James on 3/8/2020
//

// Each client account contains assets held in up to ten funds

#include "account.h"
#include <fstream>
#include <utility>

// constructor
Account::Account(string first, string last, int account) {
    firstName = std::move(first);
    lastName = std::move(last);
    accountNum = account;

    // Name funds in array
    fundsArray[0].setFundName("Money Market");
    fundsArray[1].setFundName("Prime Money Market");
    fundsArray[2].setFundName("Long-Term Bond");
    fundsArray[3].setFundName("Short-Term Bond");
    fundsArray[4].setFundName("500 Index Fund");
    fundsArray[5].setFundName("Capital Value Fund");
    fundsArray[6].setFundName("Growth Equity Fund");
    fundsArray[7].setFundName("Growth Index Fund");
    fundsArray[8].setFundName("Value Fund");
    fundsArray[9].setFundName("Value Stock Index");

    // Initialize funds to 0
    for (auto& i : fundsArray) {
        i.setFundBalance(0);
    }
}

// Destructor(s)
Account::~Account() = default;

// Getters
int Account::getAccountNum() { return accountNum; }

// returns name of a subaccount
string Account::getSubAccName(int fundNum) {
    return fundsArray[fundNum].getFundName();
}

// returns balance of a subaccount
int Account::getSubAccBalance(int fundNum) {
    return fundsArray[fundNum].getFundBalance();
}

// returns firstName
string Account::getFirstName() { return firstName; }

// returns lastName
string Account::getLastName() { return lastName; }

// deposit amount into a subaccount
bool Account::subAccDeposit(int fundNum, int amount) {
    fundsArray[fundNum].fundDeposit(amount);
    return true;
}

// withdraw amount from a subaccount
bool Account::subAccWithdraw(int fundNum, int amount) {
    // handles fund 0-3 for linked
    if (fundNum >= 0 && fundNum <= 3) {
        // only enters if fund is between 0 and 3
        // Fund 0 linked with fund 1
        if (fundNum == 0) {
            if (amount <= getSubAccBalance(fundNum)) {
                fundsArray[fundNum].fundWithdraw(amount);
                return true;
            }
            if (amount <= (getSubAccBalance(fundNum) + getSubAccBalance(1))) {
                int remainder = amount - getSubAccBalance(fundNum);
                fundsArray[fundNum].fundWithdraw(getSubAccBalance(fundNum));
                fundsArray[1].fundWithdraw(remainder);
                return true;
            }
            return false;
        }
        // Fund 1 linked with fund 0
        if (fundNum == 1) {
            if (amount <= getSubAccBalance(fundNum)) {
                fundsArray[fundNum].fundWithdraw(amount);
                return true;
            }
            if (amount <= getSubAccBalance(fundNum) + getSubAccBalance(0)) {
                int remainder = amount - getSubAccBalance(fundNum);
                fundsArray[fundNum].fundWithdraw(getSubAccBalance(fundNum));
                fundsArray[0].fundWithdraw(remainder);
                return true;
            }
            return false;
        }
        // Fund 2 linked with fund 3
        if (fundNum == 2) {
            if (amount <= getSubAccBalance(fundNum)) {
                fundsArray[fundNum].fundWithdraw(amount);
                return true;
            }
            if (amount <= getSubAccBalance(fundNum) + getSubAccBalance(3)) {
                int remainder = amount - getSubAccBalance(fundNum);
                fundsArray[fundNum].fundWithdraw(getSubAccBalance(fundNum));
                fundsArray[3].fundWithdraw(remainder);
                return true;
            }
            return false;
        }
        // Fund 3 linked with fund 2
        if (fundNum == 3) {
            if (amount <= getSubAccBalance(fundNum)) {
                fundsArray[fundNum].fundWithdraw(amount);
                return true;
            }
            if (amount <= getSubAccBalance(fundNum) + getSubAccBalance(2)) {
                int remainder = amount - getSubAccBalance(fundNum);
                fundsArray[fundNum].fundWithdraw(getSubAccBalance(fundNum));
                fundsArray[2].fundWithdraw(remainder);
                return true;
            }
            return false;
        }
    }

    // funds 4-9
    if (amount > fundsArray[fundNum].getFundBalance()) {
        // if (amount > getSubAccBalance(fundNum)){
        return false;
    }

    fundsArray[fundNum].fundWithdraw(amount);
    // subAccWithdraw(fundNum, amount);
    return true;
}

// write record to a subaccount
void Account::writeAccountRecord(const string& record, int fundNum) {
    fundsArray[fundNum].addFundRecord("        " + record);
}

// display records for a single subaccount
void Account::displaySubAccountRecord(int fundNum) {
    fundsArray[fundNum].displayFundRecord();
}

// display records for all subaccounts
void Account::displayAccountRecord() {
    std::ofstream outfile;
    outfile.open("BankTransOut.txt", std::ios_base::app);
    outfile << "Displaying Transaction History for " << lastName << " "
            << firstName << " by fund." << endl;
    for (int i = 0; i < 10; i++) {
        displaySubAccountRecord(i);
    }
}

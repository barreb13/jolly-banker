// Created by Brent and James on 3/8/2020
//

#include "bank.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    Bank bank;

    // Note that tests were done in BankTransIn.txt
    for (int i = 1; i < argc; i++) {
        std::ofstream output;
        output.open("BankTransOut.txt", std::ios_base::app);
        output << "The command line argument(s) was " << argv[i] << endl;
        string fileName = argv[i];
        bank.processTransactions(fileName);
    }

    // Call bank.display to print message and tree
    bank.displayAllBankBalances();

    // Test clear..

    return 0;
}
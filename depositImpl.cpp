#include "BankOperations.h"
#include "AccountUtils.h" // For accountExists function
#include <fstream>
#include <iostream>

void depositImpl(const std::string& accountId, int amount, TransactionResult& result) {
    // Initialize result to default values
    result.success = false;
    result.balance = 0;
    result.message = "";

    // Check if account exists
    if (!AccountUtils::accountExists(accountId)) {
        result.message = "Account does not exist.";
        return;
    }

    // File path for the account
    std::string filename = accountId + ".txt";

    // Open the account file
    std::fstream accountFile(filename, std::fstream::in | std::fstream::out);

    // Read the current balance
    int currentBalance = 0;
    if (accountFile >> currentBalance) {
        // Calculate the new balance
        currentBalance += amount;

        // Move the file pointer to the beginning to overwrite the balance
        accountFile.seekp(0, std::ios::beg);
        accountFile << currentBalance;

        // Update the TransactionResult object
        result.success = true;
        result.balance = currentBalance;
        result.message = "Deposit successful.";
    }
    else {
        // In case reading the file fails
        result.message = "Failed to read account balance.";
    }

    accountFile.close();
}

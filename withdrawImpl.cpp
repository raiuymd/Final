#include "BankOperations.h"
#include "AccountUtils.h" // For accountExists function
#include <fstream>
#include <iostream>

void withdrawImpl(const std::string& accountId, int amount, TransactionResult& result) {
    result.success = false; // Default to failure until proven otherwise
    result.balance = 0; // Default balance in case of failure
    result.message = ""; // Clear any previous message

    // Check if the account exists
    if (!AccountUtils::accountExists(accountId)) {
        result.message = "Account does not exist.";
        return;
    }

    std::string filename = accountId + ".txt";
    std::fstream accountFile(filename, std::fstream::in | std::fstream::out);

    // Ensure the file was opened successfully
    if (!accountFile.is_open()) {
        result.message = "Failed to open account file.";
        return;
    }

    // Read the current balance
    int currentBalance = 0;
    if (!(accountFile >> currentBalance)) {
        result.message = "Failed to read current balance.";
        accountFile.close();
        return;
    }

    // Check if there are sufficient funds
    if (amount > currentBalance) {
        result.message = "Insufficient funds for withdrawal.";
        accountFile.close();
        return;
    }

    // Calculate the new balance and write it back
    currentBalance -= amount;
    accountFile.seekp(0, std::ios::beg); // Move back to start to overwrite balance
    accountFile << currentBalance;
    accountFile.close();

    // Update result object
    result.success = true;
    result.balance = currentBalance;
    result.message = "Withdrawal successful.";

    // Additional logic for handling withdrawal can be added here (e.g., logging)
}

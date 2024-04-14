#include "BankOperations.h"
#include "AccountUtils.h" // For accountExists function
#include <fstream>
#include <iostream>

void inquiryImpl(const std::string& accountId, TransactionResult& result) {
    result.success = false; // Default to failure until proven otherwise
    result.message = ""; // Clear any previous message

    // Check if the account exists
    if (!AccountUtils::accountExists(accountId)) {
        result.message = "Account does not exist.";
        return;
    }

    std::string filename = accountId + ".txt";
    std::ifstream accountFile(filename);

    // Ensure the file was opened successfully
    if (!accountFile.is_open()) {
        result.message = "Failed to open account file.";
        return;
    }

    // Read the current balance
    int currentBalance = 0;
    if (accountFile >> currentBalance) {
        result.success = true;
        result.balance = currentBalance;
        result.message = "Inquiry successful.";
    }
    else {
        result.message = "Failed to read account balance.";
    }

    accountFile.close();
}

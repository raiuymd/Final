#include "BankOperations.h"
#include "AccountUtils.h" // For accountExists function
#include <filesystem> // For file operations
#include <iostream>
#include <fstream> // For std::ifstream
#include <filesystem> // For std::filesystem::remove


void closeAccountImpl(const std::string& accountId, TransactionResult& result) {
    result.success = false; // Default to failure until proven otherwise
    result.message = ""; // Clear any previous message

    // Check if the account exists
    if (!AccountUtils::accountExists(accountId)) {
        result.message = "Account does not exist.";
        return;
    }

    // Construct the file name for the account
    std::string filename = accountId + ".txt";

    // Optional: Check for zero balance before closing
    // This step depends on your business logic; you might want to enforce that accounts must have a zero balance before they can be closed.
    std::ifstream accountFile(filename);
    int balance = 0;
    if (accountFile >> balance && balance != 0) {
        result.message = "Account balance must be zero to close.";
        return;
    }
    accountFile.close();

    // Attempt to delete the account file
    if (std::filesystem::remove(filename)) {
        result.success = true;
        result.message = "Account closed successfully.";
    }
    else {
        result.message = "Failed to close account.";
    }
}

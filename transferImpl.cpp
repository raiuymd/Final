#include "BankOperations.h"
#include "AccountUtils.h" // For accountExists function
#include <fstream>
#include <iostream>

void transferImpl(const std::string& fromAccountId, const std::string& toAccountId, int amount, TransactionResult& result) {
    result.success = false; // Default to failure until operations prove otherwise
    result.message = ""; // Clear any previous message

    // Check if both accounts exist
    if (!AccountUtils::accountExists(fromAccountId)) {
        result.message = "Source account does not exist.";
        return;
    }
    if (!AccountUtils::accountExists(toAccountId)) {
        result.message = "Destination account does not exist.";
        return;
    }

    // Process the withdrawal from the source account
    int fromBalance = 0;
    {
        std::fstream fromAccountFile(fromAccountId + ".txt", std::fstream::in | std::fstream::out);
        if (!fromAccountFile.is_open() || !(fromAccountFile >> fromBalance)) {
            result.message = "Failed to process source account.";
            return;
        }
        if (amount > fromBalance) {
            result.message = "Insufficient funds in source account.";
            return;
        }
        int newFromBalance = fromBalance - amount;
        fromAccountFile.seekp(0, std::ios::beg);
        fromAccountFile << newFromBalance;
        fromAccountFile.close();
    }

    // Process the deposit to the destination account
    {
        std::fstream toAccountFile(toAccountId + ".txt", std::fstream::in | std::fstream::out);
        int toBalance = 0;
        if (!toAccountFile.is_open() || !(toAccountFile >> toBalance)) {
            result.message = "Failed to process destination account.";
            return;
        }
        int newToBalance = toBalance + amount;
        toAccountFile.seekp(0, std::ios::beg);
        toAccountFile << newToBalance;
        toAccountFile.close();
    }

    // If both operations succeeded, update the result accordingly
    result.success = true;
    result.message = "Transfer successful.";
    // Note: In a real-world scenario, consider adding transaction logging here.
}

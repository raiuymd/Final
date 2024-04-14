#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "BankMonitor.h" // Assuming this is where the BankMonitor class is defined.

// Utility function to perform a withdrawal from a withdrawal file.

void processWithdrawalFile(const std::string& withdrawalFileName) {
    std::ifstream withdrawalFile(withdrawalFileName);
    if (!withdrawalFile) {
        std::cerr << "Error: Unable to open withdrawal file " << withdrawalFileName << std::endl;
        return;
    }

    // Extracting account ID from the file name
    // Assuming the format is "withdrawal_ACCOUNTID.txt"
    std::string accountId = withdrawalFileName.substr(11, withdrawalFileName.find('.') - 11);

    int withdrawalAmount = 0;
    withdrawalFile >> withdrawalAmount;

    if (withdrawalAmount <= 0) {
        std::cerr << "Error: Invalid withdrawal amount in " << withdrawalFileName << std::endl;
        return;
    }

    BankMonitor bankMonitor; // Assuming an instance is needed to access the withdrawal method.
    bankMonitor.withdraw(accountId, withdrawalAmount);

    // Optionally, delete the withdrawal file after processing to avoid re-processing.
    std::filesystem::remove(withdrawalFileName);
}

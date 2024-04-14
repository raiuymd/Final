#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "BankMonitor.h" // Assuming this is where the BankMonitor class is defined.

// Utility function to perform a deposit from a deposit file.

void processDepositFile(const std::string& depositFileName) {
    std::ifstream depositFile(depositFileName);
    if (!depositFile) {
        std::cerr << "Error: Unable to open deposit file " << depositFileName << std::endl;
        return;
    }

    // Extracting account ID from the file name
    // Assuming the format is "deposit_ACCOUNTID.txt"
    std::string accountId = depositFileName.substr(8, depositFileName.find('.') - 8);

    int depositAmount = 0;
    depositFile >> depositAmount;

    if (depositAmount <= 0) {
        std::cerr << "Error: Invalid deposit amount in " << depositFileName << std::endl;
        return;
    }

    BankMonitor bankMonitor;
    bankMonitor.deposit(accountId, depositAmount);

    std::filesystem::remove(depositFileName);
}
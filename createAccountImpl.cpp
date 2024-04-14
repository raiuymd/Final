#include "TransactionResult.h" // Ensure this includes the definition of the TransactionResult struct
#include "AccountUtils.h"
#include <fstream>
#include <iostream>
#include "BankOperations.h"

void createAccountImpl(const std::string& accountId, int initialDeposit, TransactionResult& result) {
    if (AccountUtils::accountExists(accountId)) {
        std::cerr << "Error: Account " << accountId << " already exists." << std::endl;
        result.success = false;
        result.message = "Account already exists.";
        return;
    }

    std::ofstream accountFile(accountId + ".txt");
    if (accountFile) {
        accountFile << initialDeposit;
        std::cout << "Account " << accountId << " created with initial deposit of $" << initialDeposit << std::endl;
        result.success = true;
        result.balance = initialDeposit; // Assuming you want to return the initial balance as part of the result
        result.message = "Account created successfully.";
    }
    else {
        std::cerr << "Failed to create account " << accountId << std::endl;
        result.success = false;
        result.message = "Failed to create account.";
    }
}

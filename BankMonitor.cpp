#include "BankMonitor.h"
#include "BankOperations.h"
#include "AccountUtils.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include "TransactionResult.h"

void BankMonitor::createAccount(const std::string& accountId, int initialDeposit) {
    std::lock_guard<std::mutex> lock(mtx);
    TransactionResult result; // Create a TransactionResult object
    createAccountImpl(accountId, initialDeposit, result); // Pass the result object
    // Consider what to do with `result` here, e.g., logging
}

void BankMonitor::deposit(const std::string& accountId, int amount) {
    std::lock_guard<std::mutex> lock(mtx);
    TransactionResult result; // Create a TransactionResult object
    depositImpl(accountId, amount, result); // Pass the result object
    // Handle `result`
}

void BankMonitor::withdraw(const std::string& accountId, int amount) {
    std::lock_guard<std::mutex> lock(mtx);
    TransactionResult result; // Create a TransactionResult object
    withdrawImpl(accountId, amount, result); // Pass the result object
    // Handle `result`
}

void BankMonitor::transfer(const std::string& fromAccountId, const std::string& toAccountId, int amount) {
    std::lock_guard<std::mutex> lock(mtx);
    TransactionResult result; // Create a TransactionResult object
    transferImpl(fromAccountId, toAccountId, amount, result); // Pass the result object
    // Handle `result`
}

int BankMonitor::inquiry(const std::string& accountId) {
    std::lock_guard<std::mutex> lock(mtx);
    TransactionResult result; // Create a TransactionResult object
    inquiryImpl(accountId, result); // Pass the result object
    return result.balance; // Assuming the balance is what you want to return here
}

void BankMonitor::closeAccount(const std::string& accountId) {
    std::lock_guard<std::mutex> lock(mtx);
    TransactionResult result; // Create a TransactionResult object
    closeAccountImpl(accountId, result); // Pass the result object
    // Consider what to do with `result` here, e.g., logging
}

void BankMonitor::processTransaction(const Transaction& transaction, TransactionResult& result)
{
    // Implementation depends on transaction.type and should delegate to the appropriate Impl function
}




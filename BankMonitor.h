#pragma once
#ifndef BANKMONITOR_H
#define BANKMONITOR_H

#include <mutex>
#include <string>
#include "Transaction.h"
#include "TransactionResult.h"


class BankMonitor {
private:
    std::mutex mtx; // Mutex for synchronizing access to shared resources

public:
    BankMonitor() = default; // Default constructor
    ~BankMonitor() = default; // Default destructor

    // Creates a new account with an initial deposit amount
    void createAccount(const std::string& accountId, int initialDeposit);

    // Deposits a specified amount into an existing account
    void deposit(const std::string& accountId, int amount);

    // Withdraws a specified amount from an existing account
    void withdraw(const std::string& accountId, int amount);

    // Transfers a specified amount from one account to another
    void transfer(const std::string& fromAccountId, const std::string& toAccountId, int amount);

    // Inquires about the balance of a specified account
    int inquiry(const std::string& accountId);

    // Closes an existing account
    void closeAccount(const std::string& accountId);

    static void processTransaction(const Transaction& transaction, TransactionResult& result);
};

#endif // BANKMONITOR_H

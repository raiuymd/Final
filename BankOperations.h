#pragma once
#ifndef BANK_OPERATIONS_H
#define BANK_OPERATIONS_H

#include <string>
#include "Transaction.h" // Assuming Transaction struct is defined here
#include "TransactionResult.h" // Assuming TransactionResult struct is defined here

void createAccountImpl(const std::string& accountId, int initialDeposit, TransactionResult& result);
void depositImpl(const std::string& accountId, int amount, TransactionResult& result);
void withdrawImpl(const std::string& accountId, int amount, TransactionResult& result);
void transferImpl(const std::string& fromAccountId, const std::string& toAccountId, int amount, TransactionResult& result);
void inquiryImpl(const std::string& accountId, TransactionResult& result);
void closeAccountImpl(const std::string& accountId, TransactionResult& result);

#endif // BANK_OPERATIONS_H

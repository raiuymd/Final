#pragma once
#ifndef TRANSACTION_UTILS_H
#define TRANSACTION_UTILS_H

#include <map>
#include <vector>
#include <string>
#include "Transaction.h"
#include "TransactionResult.h"// Include the path to your Transaction struct definition

// Groups transactions by account ID.
std::map<std::string, std::vector<Transaction>> groupTransactionsByAccount(const std::vector<Transaction>& transactions);
void processAccountTransactions(const std::vector<Transaction>& transactions, TransactionResult* results, int startIndex);

#endif // TRANSACTION_UTILS_H

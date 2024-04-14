#include "TransactionUtils.h"
#include <map>
#include <vector>
#include "Transaction.h"
#include "BankOperations.h"
#include "TransactionResult.h"// Make sure this includes the definition of the Transaction struct

std::map<std::string, std::vector<Transaction>> groupTransactionsByAccount(const std::vector<Transaction>& transactions) {
    std::map<std::string, std::vector<Transaction>> groupedTransactions;
    for (const auto& transaction : transactions) {
        groupedTransactions[transaction.accountId].push_back(transaction);
    }
    return groupedTransactions;
}


void processAccountTransactions(const std::vector<Transaction>& transactions, TransactionResult* resultsArray, int startIndex) {
    for (size_t i = 0; i < transactions.size(); ++i) {
        const Transaction& tx = transactions[i];
        TransactionResult result;

        if (tx.action == "Create") {
            createAccountImpl(tx.accountId, tx.amount, result);
        }
        else if (tx.action == "Deposit") {
            depositImpl(tx.accountId, tx.amount, result);
        }
        else if (tx.action == "Withdraw") {
            withdrawImpl(tx.accountId, tx.amount, result);
        }
        else if (tx.action == "Transfer") {
            transferImpl(tx.accountId, tx.toAccountId, tx.amount, result);
        }
        else if (tx.action == "Inquiry") {
            inquiryImpl(tx.accountId, result);
        }
        else if (tx.action == "Close") {
            closeAccountImpl(tx.accountId, result);
        }
        else {
            result.success = false;
            result.message = "Unknown transaction type";
        }

        resultsArray[startIndex + i] = result; // Store the result in the corresponding position
    }
}
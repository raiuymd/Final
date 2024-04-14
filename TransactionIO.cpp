#include "TransactionIO.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "Transaction.h" // Make sure this includes the definition of the Transaction struct

std::vector<Transaction> readTransactions(const std::string& filename) {
    std::vector<Transaction> transactions;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return transactions; // Return an empty vector if file opening fails
    }

    // Skip the first line which contains the number of transactions
    std::getline(file, line);

    // Read and parse each subsequent line
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Transaction transaction;
        if (iss >> transaction.accountId >> transaction.action) {
            // Depending on the action, additional fields may be required
            if (transaction.action == "Create" || transaction.action == "Deposit" || transaction.action == "Withdraw") {
                if (!(iss >> transaction.amount)) {
                    std::cerr << "Failed to parse amount for transaction." << std::endl;
                    continue; // Skip this transaction if parsing fails
                }
            }
            if (transaction.action == "Transfer") {
                if (!(iss >> transaction.amount >> transaction.toAccountId)) {
                    std::cerr << "Failed to parse transfer details." << std::endl;
                    continue; // Skip this transaction if parsing fails
                }
            }
            // Add the transaction to the vector
            transactions.push_back(transaction);
        }
    }

    return transactions;
}

#ifndef TRANSACTION_IO_H
#define TRANSACTION_IO_H

#include <vector>
#include <string>
#include "Transaction.h" // Include the path to your Transaction struct definition

// Reads transactions from a specified file and returns them in a vector.
std::vector<Transaction> readTransactions(const std::string& filename);

#endif // TRANSACTION_IO_H
#pragma once

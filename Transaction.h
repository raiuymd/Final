#pragma once
// Transaction.h
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

struct Transaction {
    std::string accountId;
    std::string action;
    int amount;
    std::string toAccountId; // Optional: used for transfer actions
};

#endif // TRANSACTION_H

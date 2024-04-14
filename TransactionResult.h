#pragma once
#ifndef TRANSACTIONRESULT_H
#define TRANSACTIONRESULT_H

#include <cstring> // For strncpy

struct TransactionResult {
    bool success; // Indicates if the transaction was successful
    int balance; // The balance after the transaction, relevant for some operations
    char message[256]; // Fixed-size array for the message

    // Default constructor
    TransactionResult() : success(false), balance(0) {
        message[0] = '\0'; // Ensure the message is initially an empty string
    }

    // Constructor for initializing all members
    TransactionResult(bool success, int balance, const char* msg)
        : success(success), balance(balance) {
        // Safely copy the message into the fixed-size array
        // Ensure not to overflow the buffer, and null-terminate the string
        std::strncpy(message, msg, sizeof(message) - 1);
        message[sizeof(message) - 1] = '\0'; // Explicit null-termination
    }

    // Utility function to update the message
    void setMessage(const char* msg) {
        std::strncpy(message, msg, sizeof(message) - 1);
        message[sizeof(message) - 1] = '\0';
    }
};

#endif // TRANSACTIONRESULT_H


#include "SharedMemoryManager.h"
#include "Transaction.h"
#include "TransactionResult.h"
#include "TransactionIO.h"
#include "TransactionUtils.h"
#include <iostream>
#include <vector>
#include <map>
#include <unistd.h>
#include <sys/wait.h>

constexpr size_t MAX_TRANSACTIONS = 1000; // Assuming this is defined here or in a config header

int main() {
    const std::string shm_name = "/bank_transactions_shm";
    SharedMemoryManager shmManager(shm_name, sizeof(TransactionResult) * MAX_TRANSACTIONS);

    // Attempt to attach to the shared memory segment
    auto* results = static_cast<TransactionResult*>(shmManager.attach());
    if (results == nullptr) {
        std::cerr << "Failed to attach shared memory, exiting." << std::endl;
        return 1;
    }

    std::vector<Transaction> transactions = readTransactions("input.txt");
    auto groupedTransactions = groupTransactionsByAccount(transactions);

    size_t startIndex = 0; // This example assumes a linear allocation of results based on transaction order
    for (const auto& [accountId, accountTransactions] : groupedTransactions) {
        pid_t pid = fork();

        if (pid == 0) { // Child process
            processAccountTransactions(accountTransactions, results, startIndex);
            _exit(0); // Use _exit in child processes to prevent flushing buffers twice
        }
        else if (pid < 0) {
            std::cerr << "Failed to fork for account " << accountId << std::endl;
        }
        else {
            // In the parent process, calculate the next start index
            startIndex += accountTransactions.size();
        }
    }

    // In the parent process, wait for all child processes to finish
    while (wait(nullptr) > 0);

    // Assuming each transaction corresponds to a unique result
    // This part may need adjustment based on your actual indexing logic
    for (size_t i = 0; i < startIndex; i++) {
        std::cout << "Transaction Result " << i + 1 << ": "
            << (results[i].success ? "Success" : "Failure")
            << ", Message: " << results[i].message
            << ", Balance: " << results[i].balance << std::endl;
    }

    // Detach and clean up shared memory
    shmManager.detach();
    shmManager.remove(); // Ensure this is called only here in the parent process to clean up shared memory

    return 0;
}

#ifndef CCTS_TRANSACTION_H
#define CCTS_TRANSACTION_H

#include <vector>
#include <set>
#include <mutex>
#include <map>
#include <chrono>
#include <atomic>

enum TransactionStatus {
    aborted, committed, ongoing
};

class Transaction {
public:
    int id;
    std::atomic<TransactionStatus> status;
    std::map<int, int> localSharedMemory;

    Transaction(int i) {
        id = i;
        status.store(ongoing);
        localSharedMemory = std::map<int, int>();
    }
};


#endif //CCTS_TRANSACTION_H
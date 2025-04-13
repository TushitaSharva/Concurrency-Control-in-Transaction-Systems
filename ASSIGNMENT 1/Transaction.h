#ifndef CCTS_TRANSACTION_H
#define CCTS_TRANSACTION_H

#include <vector>
#include <set>
#include <mutex>
#include <map>
#include <chrono>
#include <atomic>

enum TransactionStatus {
    aborted, commited
};

class Transaction {
public:
    int id;
    std::atomic<TransactionStatus> status;
    std::set<int> writeSet;
    std::set<int> readSet;

    std::map<int, int> localWrites;

    // For BOCC, we will assign lamport clock values
    int start_time;
    int end_time;


    Transaction(int i);
    Transaction(int i, int timeStamp);
    void write(int data_item, int value);
    void read(int data_item);
};


#endif //CCTS_TRANSACTION_H
#include "Transaction.h"

Transaction::Transaction(int i) {
    id = i;
    status.store(commited); // default is committed, but will be accuratedly set in try commit
    writeSet = std::set<int>();
    readSet = std::set<int>();
    localWrites = std::map<int, int>();
}

Transaction::Transaction(int i, int timeStamp) {
    id = i;
    start_time = timeStamp;

    writeSet = std::set<int>();
    readSet = std::set<int>();
    localWrites = std::map<int, int>();
}

void Transaction::read(int index) {
    readSet.insert(index);
}

void Transaction::write(int index, int value) {
    localWrites[index] = value;
    writeSet.insert(index);
}
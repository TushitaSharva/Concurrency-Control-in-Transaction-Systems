#ifndef DATAITEM_H
#define DATAITEM_H

#include <set>
#include <mutex>
#include <chrono>
#include "Transaction.h"

class DataItem {
public:
    int value;
    
    // Custom comparator for sorting transactions by ID
    struct TransactionComparator {
        bool operator()(const Transaction* a, const Transaction* b) const {
            return a->id < b->id; // Sort by transaction ID in ascending order
        }
    };

    std::set<Transaction*, TransactionComparator> readList;  // Ordered by transaction ID
    std::set<int> writeList;
    mutable std::mutex lock;
    int highest_endTime;  // For BOCC

    // Default Constructor
    DataItem() : value(0), highest_endTime(0) {}

    // Parameterized Constructor
    DataItem(int val) : value(val), highest_endTime(0) {}

    // Copy Constructor
    DataItem(const DataItem& other) {
        std::lock_guard<std::mutex> guard(other.lock);
        value = other.value;
        readList = other.readList;  // Uses custom comparator
        writeList = other.writeList;
        highest_endTime = other.highest_endTime;
    }

    // Move Constructor
    DataItem(DataItem&& other) noexcept {
        std::lock_guard<std::mutex> guard(other.lock);
        value = other.value;
        readList = std::move(other.readList);
        writeList = std::move(other.writeList);
        highest_endTime = other.highest_endTime;
    }

    // Copy Assignment Operator
    DataItem& operator=(const DataItem& other) {
        if (this != &other) {
            std::lock_guard<std::mutex> guard(lock);
            value = other.value;
            readList = other.readList;  // Uses custom comparator
            writeList = other.writeList;
            highest_endTime = other.highest_endTime;
        }
        return *this;
    }

    // Move Assignment Operator
    DataItem& operator=(DataItem&& other) noexcept {
        if (this != &other) {
            std::lock_guard<std::mutex> guard(lock);
            value = other.value;
            readList = std::move(other.readList);
            writeList = std::move(other.writeList);
            highest_endTime = other.highest_endTime;
        }
        return *this;
    }

    void printSet() {
        for(auto i : readList) {
            std::cout << i->id << " ";
        }
        std::cout << "\n";
    }

    // Destructor (Optional, ensures no memory leaks if used properly)
    ~DataItem() = default;
};

#endif // DATAITEM_H

#ifndef DATAITEM_H
#define DATAITEM_H

#include <set>
#include <mutex>
#include <chrono>
#include "Transaction.h"

class DataItem {
public:
    int value;
    std::set<int> readList;
    std::set<int> writeList;
    mutable std::mutex lock;
    int highest_endTime; // For BOCC

    // Default Constructor
    DataItem() : value(0), highest_endTime(0) {}

    // Parameterized Constructor
    DataItem(int val) : value(val), highest_endTime(0) {}

    // Copy Constructor
    DataItem(const DataItem& other) 
        : value(other.value), readList(other.readList), writeList(other.writeList), 
          highest_endTime(other.highest_endTime) {}

    // Move Constructor
    DataItem(DataItem&& other) noexcept 
        : value(other.value), readList(std::move(other.readList)), 
          writeList(std::move(other.writeList)), highest_endTime(other.highest_endTime) {}

    // Copy Assignment Operator
    DataItem& operator=(const DataItem& other) {
        if (this != &other) {
            std::lock_guard<std::mutex> guard(lock); // Ensure thread safety
            value = other.value;
            readList = other.readList;
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
};

#endif // DATAITEM_H
